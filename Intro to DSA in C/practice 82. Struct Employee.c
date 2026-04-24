#include <stdio.h>
#include <string.h>

// Structure to represent an employee
struct Employee {
    int empNo;
    char name[50];
    int age;
    int joiningYear;
    float salary;
};

// Function to input details of an employee
void inputEmployee(struct Employee e[], int i) {
    printf("Enter details for employee %d:\n", i + 1);
    printf("Enter employee number: ");
    scanf("%d", &e[i].empNo);
    printf("Enter name: ");
    scanf("%s", e[i].name);
    printf("Enter age: ");
    scanf("%d", &e[i].age);
    printf("Enter date of joining (year): ");
    scanf("%d", &e[i].joiningYear);
    printf("Enter salary: ");
    scanf("%f", &e[i].salary);
}

// Function to compute retirement year and salary at that time
void computeRetirement(struct Employee e[], int i) {
    int yearsToRetirement = 55 - e[i].age;
    int retirementYear = e[i].joiningYear + yearsToRetirement;
    float updatedSalary = e[i].salary;
    
    // Calculate salary with a 20% hike per annum
    for (int j = e[i].joiningYear; j < retirementYear; ++j) {
        updatedSalary += 0.2 * updatedSalary;
    }

    printf("Retirement details for employee %d:\n", i + 1);
    printf("Retirement Year: %d\n", retirementYear);
    printf("Salary at Retirement: %.2f\n", updatedSalary);
}

int main() {
    int n; // number of employees
    printf("Enter the number of employees: ");
    scanf("%d", &n);

    struct Employee employees[n];

    // Input details for each employee
    for (int i = 0; i < n; ++i) {
        inputEmployee(employees, i);
    }

    // Compute retirement details for each employee
    for (int i = 0; i < n; ++i) {
        computeRetirement(employees, i);
    }

    return 0;
}
