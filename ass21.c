#include <stdio.h>
#include <stdlib.h>

typedef struct employee {
    char *lastname;
    char *firstname;
    int id;
    int ssn;
    char *title;
} employee_t;

typedef struct employees {
    employee_t employee_1;
    employee_t employee_2;
} employees_t;

void free_employee(employee_t *e)
{
    free(e->firstname);
    free(e->lastname);
    free(e->title);
}

int main(int argc, char *argv[])
{
    employees_t engineering_dept;

    for(int i = 0; i < 2; i++) {
        employee_t *e = &engineering_dept.employee_1;
        if(i > 0)
            e = &engineering_dept.employee_2;

        printf("Enter the employee's first name: ");
        scanf("%ms", &e->firstname);
        printf("Enter the employee's last name: ");
        scanf("%ms", &e->lastname);
        printf("Enter the employee's ID number: ");
        scanf("%d", &e->id);
        printf("Enter the last four digits of the employee's SSN: ");
        scanf("%d", &e->ssn);
        printf("Enter the employee's job title (do not include the word 'Engineer'): ");
        scanf("%ms", &e->title);

        puts("");
    }

    for(int i = 0; i < 2; i++) {
        employee_t *e = &engineering_dept.employee_1;
        if(i > 0)
            e = &engineering_dept.employee_2;

        printf("\nEmployee information for %s %s:", e->firstname, e->lastname);
        printf("\nID: %d", e->id);
        printf("\nSSN: %d", e->ssn);
        printf("\nTitle: %s Engineer\n", e->title);
    }

    free_employee(&engineering_dept.employee_1);
    free_employee(&engineering_dept.employee_2);

    return 0;
}
