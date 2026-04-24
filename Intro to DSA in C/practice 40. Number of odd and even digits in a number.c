#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    int count_odd = 0;
    int count_even = 0;
    printf("Enter a number:");
    scanf("%d", &n); 
    while (n > 0){
        int dgt = n % 10;
        n = n / 10;
        if(dgt % 2 == 0){
            count_even = count_even + 1;
        }
        else{
            count_odd = count_odd + 1;
        }
    }
    printf("Number of even digits : %d\n", count_even); 
    printf("Number of odd digits : %d\n", count_odd); 
    return 0;
}
