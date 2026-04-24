#include <stdio.h>

int main() {
    int mark;
    char grade;

    printf("Enter your mark: ");
    scanf("%d", &mark);

    switch (mark) {
        case 100:
        case 90:
        case 80:
            grade = 'A';
            break;

        case 70:
        case 60:
            grade = 'B';
            break;

        case 50:
            grade = 'C';
            break;

        case 40:
            grade = 'D';
            break;

        default:
            grade = 'F';
            break;
    }

    printf("Grade: %c\n", grade);

    return 0;
}
