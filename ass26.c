#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct connection {
    pid_t pid;
    int stdout[2];
    int stderr[2];
    char addr[INET6_ADDRSTRLEN];
    struct connection *next;
} connection_t;

connection_t *find_connection(connection_t *list, pid_t pid)
{
    while(list) {
        if(list->pid == pid)
            return list;

        list = list->next;
    }

    return NULL;
}

connection_t *dequeue_connection(connection_t **list, pid_t pid)
{
    for(connection_t *cur = *list, *last = NULL; cur; last = cur, cur = cur->next) {
        if(cur->pid == pid) {
            if(last)
                last->next = cur->next;
            else
                *list = cur->next;

            cur->next = NULL;
            return cur;
        }
    }

    return NULL;
}

connection_t *connections;

void queue_connection(connection_t **list, connection_t *conn)
{
    conn->next = *list;
    *list = conn;
}

void sigchld_handler(int s)
{
    pid_t pid;

    char buf[0x100];

    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) {
        connection_t *cur = dequeue_connection(&connections, pid);
        if(!cur) {
            fprintf(stderr, "Failed to find connection for pid %d!!!", pid);
        } else {
            int bytesRead;

            while((bytesRead = read(cur->stdout[0], &buf, sizeof(buf))) >= 0)
                write(STDOUT_FILENO, &buf, bytesRead);

            close(cur->stdout[0]);

            while((bytesRead = read(cur->stderr[0], &buf, sizeof(buf))) >= 0)
                write(STDERR_FILENO, &buf, bytesRead);

            close(cur->stderr[0]);

            printf("Connection from %s closed ...\n", cur->addr);
            free(cur);
        }
    }
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int err = 0;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s <port>.\n", argv[0]);
        return 1;
    }

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_PASSIVE;

    struct addrinfo *serverInfo;

    if((err = getaddrinfo(NULL, argv[1], &hints, &serverInfo)) != 0) {
        fprintf(stderr, "Failed to fetch address info: %s\n", gai_strerror(err));
        return err;
    }

    int sock;
    struct addrinfo *ap;

    /* Loop threw addresses returned by getaddrinfo() and stop on successful bind */
    for(ap = serverInfo; ap; ap = ap->ai_next) {
        sock = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
        if(sock == -1) {
            perror("Failed to open tcp socket: ");
            continue;
        }

        if(bind(sock, ap->ai_addr, ap->ai_addrlen) == 0)
            break;

        perror("Failed to bind to socket: ");

        close(sock);
    }

    /* Check if bind was successful */
    if(!ap) {
        fprintf(stderr, "Failed to bind to %s\n", argv[0]);
        err = 1;
        goto exit;
    }

    freeaddrinfo(serverInfo);

    // Allow up to 8 pending connections
    if(listen(sock, 8) == -1) {
        perror("Failed to listen on sock: ");
        err = errno;
        goto sock_err;
    }

    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("Failed to register signal handler: ");
        err = errno;
        goto sock_err;
    }

    printf("Waiting for connections ...\n");

    int conn;

    struct sockaddr_storage clientAddr;
    socklen_t sinSize = sizeof(clientAddr);
    char clientAddrBuf[INET6_ADDRSTRLEN];

    int clientStdout[2];
    int clientStderr[2];

    while((conn = accept(sock, (struct sockaddr *)&clientAddr, &sinSize)) > 0) {
        if(pipe(clientStdout) == -1)
            fprintf(stderr, "Failed to open output pipe: %s\n", strerror(errno));

        if(pipe(clientStderr) == -1)
            fprintf(stderr, "Failed to open error pipe: %s\n", strerror(errno));

        pid_t pid = fork();
        if(pid > 0) {
            // This is the parent process
            pid_t ret;
            int status;

            // Close writing ends of pipes
            close(clientStdout[1]);
            close(clientStderr[1]);

            inet_ntop(clientAddr.ss_family,
                get_in_addr((struct sockaddr *)&clientAddr),
                clientAddrBuf, sizeof(clientAddrBuf));

            printf("Got connection from %s ...\n", clientAddrBuf);

            connection_t *newConn = malloc(sizeof(connection_t));
            if(!newConn) {
                fprintf(stderr, "Failed to allocate connection memory.\n");
                goto accept_err;
            }

            memset(newConn, 0, sizeof(connection_t));

            newConn->pid = pid;
            strncpy(newConn->addr, clientAddrBuf, sizeof(clientAddrBuf));
            memcpy(&newConn->stdout[0], &stdout[0], 2 * sizeof(int));
            memcpy(&newConn->stderr[0], &stderr[0], 2 * sizeof(int));

            queue_connection(&connections, newConn);
        } else if(pid == 0) {
            // This is the child process
            // Close reading ends of pipe
            close(clientStdout[0]);
            close(clientStderr[0]);

            if((err = dup2(clientStdout[1], STDOUT_FILENO)) == -1) {
                perror("Failed to pipe stdin: ");
                err = errno;
                goto accept_err;
            }

            if((err = dup2(clientStderr[1], STDERR_FILENO)) == -1) {
                perror("Failed to pipe stderr: ");
                err = errno;
                goto accept_err;
            }

            if((err = dup2(conn, STDIN_FILENO)) == -1) {
                perror("Failed to create copy of stdin: ");
                err = errno;
                goto accept_err;
            }

            if((err = dup2(conn, STDOUT_FILENO)) == -1) {
                perror("Failed to create copy of stdout: ");
                err = errno;
                goto accept_err;
            }

            if((err = dup2(conn, STDERR_FILENO)) == -1) {
                perror("Failed to create copy of stderr: ");
                err = errno;
                goto accept_err;
            }

            char *args[] = { NULL };
            char *env[] = { NULL };

            if(execve("/bin/sh", args, env) == -1) {
                perror("Failed to start shell: ");
                err = errno;
                goto accept_err;
            }
        } else {
            // Error
            perror("Accept failed:");
        }
    }

    if(conn == -1) {
        perror("Failed to accept connections:");
        err = errno;
        goto sock_err;
    }

accept_err:
    close(conn);

sock_err:
    close(sock);

exit:
    return err;
}
