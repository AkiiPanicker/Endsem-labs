#include <stdio.h>
#include <stdlib.h>
int fact(int n);
int main(){
    printf("factorial is: %d", fact(5));
    return 0;
}

int fact(int n){
    if (n==0){
        return 1;
    }
    int factNM = fact(n-1);
    int factN = factNM * n;
    return factN;
}