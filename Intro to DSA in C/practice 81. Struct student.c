#include <stdio.h>
#include <string.h>

// Structure to represent a student
struct Student {
    char name[50];
    int rollno;
    float m1, m2, m3;
    float average; // to store average marks
};

// Function to input details of a student
void inputStudent(struct Student s[], int i) {
    printf("Enter name for student %d: ", i + 1);
    scanf("%s", s[i].name);
    printf("Enter roll number for student %d: ", i + 1);
    scanf("%d", &s[i].rollno);
    printf("Enter marks for three subjects (m1 m2 m3) for student %d: ", i + 1);
    scanf("%f %f %f", &s[i].m1, &s[i].m2, &s[i].m3);
}

// Function to compute average marks of a student
void computeAverage(struct Student s[], int i) {
    s[i].average = (s[i].m1 + s[i].m2 + s[i].m3) / 3.0;
}

// Function to display details of a student
void displayStudent(struct Student s[], int i) {
    printf("%-20s %5d %8.2f %8.2f %8.2f %8.2f\n", s[i].name, s[i].rollno, s[i].m1, s[i].m2, s[i].m3, s[i].average);
}

// Function to swap two students
void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n; // number of students
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student students[n];

    // Input details for each student
    for (int i = 0; i < n; ++i) {
        inputStudent(students, i);
        computeAverage(students, i);
    }

    // Bubble sort to sort students based on average marks in ascending order
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (students[j].average > students[j + 1].average) {
                swap(&students[j], &students[j + 1]);
            }
        }
    }

    // Display the sorted list of students
    printf("\nStudent details in ascending order of average marks:\n");
    printf("%-20s %5s %8s %8s %8s %8s\n", "Name", "Roll No", "M1", "M2", "M3", "Average");
    for (int i = 0; i < n; ++i) {
        displayStudent(students, i);
    }

    return 0;
}
