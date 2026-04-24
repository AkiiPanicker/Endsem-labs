#include <stdio.h>
#include <stdlib.h>

struct Student{
    char name[50];
    char major[50];
    int age;
    double gpa;

};

int main(){

    struct Student student1;
    student1.age = 22;
    student1.gpa = 32;
    strcpy(student1.name, "Aki");
    strcpy(student1.major, "CSE");
    printf("%f \n", student1.gpa);
    printf("%s", student1.name);

    return 0;

}