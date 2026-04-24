#include <stdio.h>
#include <stdlib.h>

int main(){
    int numbers[] = {4, 8, 15, 16, 23, 42};
    numbers[2] = 100;
    printf("%d", numbers[2]);
    return 0;
}