#include <stdio.h>
#include <stdlib.h>
int main() {
    int a; // Declare the variable 'a' to store the input value
    printf("Enter Value: "); 
    scanf("%d", &a); //taking input from user %d is used as heads up to tell the system its an int and & is to declare input
    printf("%d", a); //here %d will tell the system where to insert the variable output value
    return 0;
}
