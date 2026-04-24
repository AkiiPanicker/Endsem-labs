#include <stdio.h>
#include <stdlib.h>
int main(){
    int number;
    printf("Enter number whose factorial is needed:");
    scanf("%d", &number);
    int i = 1;
    int fact = 1;
    while(i<=number){
        fact = fact*i;
        i++;
    }
    printf("factorial of %d is: %d", number,  fact);
    return 0;
}