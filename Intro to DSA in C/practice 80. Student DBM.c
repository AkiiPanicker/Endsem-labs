#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct students {
    int stuID;
    char sname[30];
    char div[5];
    char grade;
    float marks[5];
    float totalmarks;
};

void add_stu(struct students stu[], int *count);
void modify_stu(struct students stu[], int count);
void del_stu(struct students stu[], int *count);
void stu_details(struct students stu[], int count);
float calc_totalmarks(float marks[]);
char grade(float totalmarks);
void write_data_to_file(struct students stu[], int count);
void read_data_from_file(struct students stu[], int *count);
void display_all_records(struct students stu[], int count);
void sort_students(struct students stu[], int count, int sortCriteria);

int main() {
    struct students stu[50];
    int choice, count = 0;

    read_data_from_file(stu, &count);

    do {
        printf("1. Add student record\n");
        printf("2. Modify student record\n");
        printf("3. Delete student record\n");
        printf("4. View student details\n");
        printf("5. Display All Records\n");
        printf("6. Sort Students\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
    

        switch (choice) {
            case 1: {
                add_stu(stu, &count);
                write_data_to_file(stu, count);
                break;
            }
            case 2: {
                if (!count) {
                    printf("Student Record empty!\n");
                    break;
                }
                modify_stu(stu, count);
                write_data_to_file(stu, count);
                break;
            }
            case 3: {
                if (!count) {
                    printf("Student Record empty!\n");
                    break;
                }
                del_stu(stu, &count);
                write_data_to_file(stu, count);
                break;
            }
            case 4: {
                if (!count) {
                    printf("Student Record empty!\n");
                    break;
                }
                stu_details(stu, count);
                break;
            }
            case 5: {
                display_all_records(stu, count);
                break;
            }
            case 6: {
                int sortCriteria;
                printf("Sort students by:\n");
                printf("1. Name\n");
                printf("2. Marks\n");
                printf("3. ID\n");
                printf("4. Grade\n");
                printf("5. Division\n");
                printf("Enter your choice: ");
                scanf("%d", &sortCriteria);

                sort_students(stu, count, sortCriteria);
                display_all_records(stu, count);
                break;
            }
            case 7: {
                printf("Exit code\n");
                break;
            }
            default: {
                printf("Invalid Choice!\n");
            }
        }
    } while (choice != 7);

    return 0;
}

void add_stu(struct students stu[], int *count) {
    if (*count < 20) {
        if (*count) {
            stu[*count].stuID = stu[(*count) - 1].stuID + 1;
        } else {
            stu[*count].stuID = 1;
        }

        printf("Enter details for student ID %d:\n", stu[*count].stuID);

        printf("Enter name: ");
        fgets(stu[*count].sname, 30, stdin);
        stu[*count].sname[strcspn(stu[*count].sname, "\n")] = '\0';

        printf("Enter Division: ");
        fgets(stu[*count].div, 5, stdin);
        stu[*count].div[strcspn(stu[*count].div, "\n")] = '\0';

        for (int i = 0; i < 5; i++) {
            printf("Enter marks for subject %d: ", i + 1);
            scanf("%f", &stu[*count].marks[i]);
        }

        stu[*count].totalmarks = calc_totalmarks(stu[*count].marks);
        stu[*count].grade = grade(stu[*count].totalmarks);
        (*count)++;
    } else {
        printf("Max value reached!\n");
    }
}

void modify_stu(struct students stu[], int count) {
    char sname[30];

    printf("Enter Student Name: ");
    getchar();  
    fgets(sname, 30, stdin);
    sname[strcspn(sname, "\n")] = '\0';

    for (int i = 0; i < count; i++) {
        if (strcmp(sname, stu[i].sname) == 0) {
            printf("Enter new name: ");
            getchar();  
            fgets(stu[i].sname, 30, stdin);
            stu[i].sname[strcspn(stu[i].sname, "\n")] = '\0';

            printf("Enter new division: ");
            fgets(stu[i].div, 5, stdin);
            stu[i].div[strcspn(stu[i].div, "\n")] = '\0';

            printf("Enter updated marks for:\n");
            for (int j = 0; j < 5; j++) {
                printf("Enter marks for subject %d: ", j + 1);
                scanf("%f", &stu[i].marks[j]);
            }

            stu[i].totalmarks = calc_totalmarks(stu[i].marks);
            stu[i].grade = grade(stu[i].totalmarks);
            return;
        }
    }

    printf("Student Name not found!\n");
}
void del_stu(struct students stu[], int *count) {
    char sname[30];

    printf("Enter Student Name: ");
    getchar();  
    fgets(sname, 30, stdin);
    sname[strcspn(sname, "\n")] = '\0';

    for (int i = 0; i < *count; i++) {
        if (strcmp(sname, stu[i].sname) == 0) {
            for (int j = i; j < *count - 1; j++) {
                stu[j] = stu[j + 1];
            }
            printf("Student record deleted successfully!\n");
            (*count)--;
            return;
        }
    }

    printf("Student Name not found!\n");
}

void stu_details(struct students stu[], int count) {
    char sname[30];

    printf("Enter Student Name: ");
    getchar();  
    fgets(sname, 30, stdin);
    sname[strcspn(sname, "\n")] = '\0';


    for (int i = 0; i < count; i++) {
        if (strcmp(sname, stu[i].sname) == 0) {
            printf("Student ID: %d\n", stu[i].stuID);
            printf("Student Name: %s\n", stu[i].sname);
            printf("Student Division: %s\n", stu[i].div);
            printf("Student average marks: %.2f\n", stu[i].totalmarks);
            printf("Student Grade: %c\n", stu[i].grade);
            printf("Student marks in individual subjects:\n");
            for (int j = 0; j < 5; j++) {
                printf("Subject %d: %.2f\n", j + 1, stu[i].marks[j]);
            }
            return;
        }
    }

    printf("Student Name not found!\n");
}

float calc_totalmarks(float marks[]) {
    float sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += marks[i];
    }
    return (sum / 5.0);
}

char grade(float totalmarks) {
    if (totalmarks >= 90) {
        return 'A';
    } else if (totalmarks >= 80) {
        return 'B';
    } else if (totalmarks >= 70) {
        return 'C';
    } else if (totalmarks >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

void write_data_to_file(struct students stu[], int count) {
    FILE *file = fopen("student_data.txt", "w");
    if (file == NULL) {
        printf("Error opening the file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", stu[i].stuID);

        for (int j = 0; j < strlen(stu[i].sname); j++) {
            fputc(stu[i].sname[j], file);
        }
        fprintf(file, "\n");  

        fprintf(file, "%s\n", stu[i].div);

        fprintf(file, "%.0f %.0f %.0f %.0f %.0f\n", stu[i].marks[0], stu[i].marks[1],
                stu[i].marks[2], stu[i].marks[3], stu[i].marks[4]);

        fprintf(file, "%.0f\n%c\n", stu[i].totalmarks, stu[i].grade);


        fprintf(file, "\n");
    }

    fclose(file);
}

void read_data_from_file(struct students stu[], int *count) {
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("No existing data file found.\n");
        return;
    }

    while (fscanf(file, "%d", &stu[*count].stuID) == 1) {
        fgetc(file);  // Consume newline character
        fgets(stu[*count].sname, 30, file);
        stu[*count].sname[strcspn(stu[*count].sname, "\n")] = '\0';
        fgets(stu[*count].div, 5, file);
        stu[*count].div[strcspn(stu[*count].div, "\n")] = '\0';
        fscanf(file, "%f %f %f %f %f",
                &stu[*count].marks[0], &stu[*count].marks[1],
                &stu[*count].marks[2], &stu[*count].marks[3],
                &stu[*count].marks[4]);
        fscanf(file, "%f", &stu[*count].totalmarks);
        fscanf(file, " %c", &stu[*count].grade);

        (*count)++;
    }

    fclose(file);
}

void display_all_records(struct students stu[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Student ID: %d\n", stu[i].stuID);
        printf("Student Name: %s\n", stu[i].sname);
        printf("Student Division: %s\n", stu[i].div);
        printf("Student total marks: %.2f\n", stu[i].totalmarks);
        printf("Student Grade: %c\n", stu[i].grade);
        printf("Student marks in individual subjects:\n");
        for (int j = 0; j < 5; j++) {
            printf("Subject %d: %.2f\n", j + 1, stu[i].marks[j]);
        }
        printf("\n");
    }
}

void sort_students(struct students stu[], int count, int sortCriteria) {
    switch (sortCriteria) {
        case 1: {
            
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (strcmp(stu[i].sname, stu[j].sname) > 0) {
                        struct students temp = stu[i];
                        stu[i] = stu[j];
                        stu[j] = temp;
                    }
                }
            }
            break;
        }
        case 2: {
            
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (stu[i].totalmarks < stu[j].totalmarks) {
                        struct students temp = stu[i];
                        stu[i] = stu[j];
                        stu[j] = temp;
                    }
                }
            }
            break;
        }
        case 3: {
            
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (stu[i].stuID > stu[j].stuID) {
                        struct students temp = stu[i];
                        stu[i] = stu[j];
                        stu[j] = temp;
                    }
                }
            }
            break;
        }
        case 4: {
            
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (stu[i].grade > stu[j].grade) {
                        struct students temp = stu[i];
                        stu[i] = stu[j];
                        stu[j] = temp;
                    }
                }
            }
            break;
        }
        case 5: {
            
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (strcmp(stu[i].div, stu[j].div) > 0) {
                        struct students temp = stu[i];
                        stu[i] = stu[j];
                        stu[j] = temp;
                    }
                }
            }
            break;
        }
        default: {
            printf("Invalid sort criteria!\n");
        }
    }
}

