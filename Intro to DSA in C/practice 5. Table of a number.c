#include <stdio.h>
#include <stdlib.h>

int main(){
    int num;
    printf("Enter number for its table:");
    scanf("%d", &num);
    int i =1;
    while(i<=10){
        int result = num*i;
        printf("%d X %d = %d \n", num, i, result);
        i++;
    }
    return 0;
}