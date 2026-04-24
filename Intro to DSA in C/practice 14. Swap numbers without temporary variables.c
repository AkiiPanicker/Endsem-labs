#include <stdio.h>
#include <stdlib.h>

void swap(int a, int b){
    a = a+b;
    b = a-b;
    a = a-b;
    printf("After swapping first number = %d, second number = %d", a, b);

}

int main(){
    int num1 , num2;
    printf("Enter fist number:");
    scanf("%d", &num1);
    printf("Enter second number:");
    scanf("%d", &num2);
    swap(num1,num2);
    return 0;
}