#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    char name[50];
    int code;
    char department[50];
    float basicSalary;
    float DA;
    float HRA;
    float IT;
    float PT;
};

void saveToFile(struct Employee employees[], int count);
void loadFromFile(struct Employee employees[], int *count);
void addEmployee(struct Employee employees[], int *count);
void deleteEmployee(struct Employee employees[], int *count, int codeToDelete);
void modifyEmployee(struct Employee employees[], int count, int codeToModify);
void displayEmployee(struct Employee employees[], int count, int codeToDisplay);
void displayNetSalary(struct Employee employees[], int count, int codeToCalculate);

int main() {
    struct Employee employees[100];
    int count = 0;
    loadFromFile(employees, &count);
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Modify Employee Details\n");
        printf("4. Display Employee Details\n");
        printf("5. Display Net Salary\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &count);
                break;
            case 2: {
                int codeToDelete;
                printf("Enter employee code to delete: ");
                scanf("%d", &codeToDelete);
                deleteEmployee(employees, &count, codeToDelete);
                break;
            }
            case 3: {
                int codeToModify;
                printf("Enter employee code to modify: ");
                scanf("%d", &codeToModify);
                modifyEmployee(employees, count, codeToModify);
                break;
            }
            case 4: {
                int codeToDisplay;
  
  
  
               printf("Enter employee code to display: ");
                scanf("%d", &codeToDisplay);
                displayEmployee(employees, count, codeToDisplay);
                break;
            }
            case 5: {
                int codeToCalculate;
                printf("Enter employee code to calculate net salary: ");
                scanf("%d", &codeToCalculate);
                displayNetSalary(employees, count, codeToCalculate);
                break;
            }
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}

void saveToFile(struct Employee employees[], int count) {
    FILE *file = fopen("employee_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %s %.2f %.2f %.2f %.2f %.2f\n",
                employees[i].name, employees[i].code, employees[i].department,
                employees[i].basicSalary, employees[i].DA, employees[i].HRA,
                employees[i].IT, employees[i].PT);
    }

    fclose(file);
}

void loadFromFile(struct Employee employees[], int *count) {
    FILE *file = fopen("employee_data.txt", "r");
    if (file == NULL) {
        printf("No existing data found.\n");
        return;
    }

    while (fscanf(file, "%s %d %s %f %f %f %f %f\n",
                  employees[*count].name, &employees[*count].code, employees[*count].department,
                  &employees[*count].basicSalary, &employees[*count].DA, &employees[*count].HRA,
                  &employees[*count].IT, &employees[*count].PT) != EOF) {
        (*count)++;
    }

    fclose(file);
}

void addEmployee(struct Employee employees[], int *count) {
    printf("Enter Employee Details:\n");
    printf("Name: ");
    scanf("%s", employees[*count].name);
    printf("Code: ");
    scanf("%d", &employees[*count].code);
    printf("Department: ");
    scanf("%s", employees[*count].department);
    printf("Basic Salary: ");
    scanf("%f", &employees[*count].basicSalary);
    printf("DA: ");
    scanf("%f", &employees[*count].DA);
    printf("HRA: ");
    scanf("%f", &employees[*count].HRA);
    printf("IT: ");
    scanf("%f", &employees[*count].IT);
    printf("PT: ");
    scanf("%f", &employees[*count].PT);

    (*count)++;

    saveToFile(employees, *count);
}

void deleteEmployee(struct Employee employees[], int *count, int codeToDelete) {
    for (int i = 0; i < *count; i++) {
        if (employees[i].code == codeToDelete) {
            for (int j = i; j < (*count) - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*count)--;
            printf("Employee with code %d deleted.\n", codeToDelete);
            saveToFile(employees, *count);
            return;
        }
    }
    printf("Employee code %d not found \n", codeToDelete);


}

void modifyEmployee(struct Employee employees[], int count, int codeToModify) {
    for (int i = 0; i < count; i++) {
        if (employees[i].code == codeToModify) {
            printf("Enter new details for employee with code %d:\n", codeToModify);
            printf("Name: ");
            scanf("%s", employees[i].name);
            printf("Department: ");
            scanf("%s", employees[i].department);
            printf("Basic Salary: ");
            scanf("%f", &employees[i].basicSalary);
            printf("DA: ");
            scanf("%f", &employees[i].DA);
            printf("HRA: ");
            scanf("%f", &employees[i].HRA);
            printf("IT: ");
            scanf("%f", &employees[i].IT);
            printf("PT: ");
            scanf("%f", &employees[i].PT);
            printf("Employee details modified.\n");
            saveToFile(employees, count);
            return;
        }
    }
    printf("Employee code %d not found \n", codeToModify);

}

void displayEmployee(struct Employee employees[], int count, int codeToDisplay) {
    for (int i = 0; i<count; i++){
        if (employees[i].code == codeToDisplay){
            printf("Employees Details : \n");
            printf("Name: %s\n", employees[i].name);
            printf("Code: %d\n", employees[i].code);
            printf("Department: %s\n", employees[i].department);
            printf("Basic Salary: %.2f\n", employees[i].basicSalary);
            printf("DA: %.2f\n", employees[i].DA);
            printf("HRA: %.2f\n", employees[i].HRA);
            printf("IT: %.2f\n", employees[i].IT);
            printf("PT: %.2f\n", employees[i].PT);
            return;
        }
    }
    printf("Employee code %d not found \n", codeToDisplay);
}

void displayNetSalary(struct Employee employees[], int count, int codeToCalculate) {
    for (int i = 0; i < count; i++) {
        if (employees[i].code == codeToCalculate) {
            float grossSalary = employees[i].basicSalary + employees[i].DA + employees[i].HRA - employees[i].PT;
            float netSalary = grossSalary - (0.10 * grossSalary);

            printf("Net Salary Details:\n");
            printf("Gross Salary: %.2f\n", grossSalary);
            printf("Net Salary: %.2f\n", netSalary);
            return;
        }
    }
    printf("Employee with code %d not found.\n", codeToCalculate);
}




