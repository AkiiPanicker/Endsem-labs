#include <stdio.h>
#include <stdlib.h>

int main() {
    int no_stu;
    printf("Enter number of students:");
    scanf("%d", &no_stu);

    int age[no_stu];

    for (int i = 0; i < no_stu; i++) {
        printf("Enter age of student %d: ", i+1);
        scanf("%d", &age[i]);
    }

    printf("Ages of students are:\n");
    for (int i = 0; i < no_stu; i++) {
        printf("%d\n", age[i]);
    }

    return 0;
}
