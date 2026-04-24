#include <stdio.h>

void towerofHanoi(int n, char fromrod, char auxrod, char torod){
    if (n==1){
        printf("Move disk 1 from %c to %c \n", fromrod, torod);
        return;
    }
    towerofHanoi(n-1, fromrod, torod, auxrod);
    printf("Move disk %d from %c to %c \n", n, fromrod, torod);
    towerofHanoi(n-1, auxrod, fromrod, torod);
}

int main(){
    int n;
    printf("Number of Disks:");
    scanf("%d", &n);
    printf("Steps Tower of Hanoi with %d disks: \n", n);
    towerofHanoi(n, 'A', 'B', 'C');
    return 0;
}