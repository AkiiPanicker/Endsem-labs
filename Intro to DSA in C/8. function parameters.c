#include <stdio.h>
#include <stdlib.h>

int main(){

    sayHi("Aki", 25);    /* calling the function*/
    sayHi("Seri", 35);  
    return 0;
}

void sayHi(char name[], int age){
    /* now we take parameter we can pass different values*/
    printf("Hello %s, you are %d \n", name, age);
}