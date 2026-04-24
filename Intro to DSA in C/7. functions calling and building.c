#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Top"); /*the flow of the function takes place in a particular order from first written first executed basis*/
    sayHi();    /* calling the function*/
    printf("Bottom");
    return 0;
}

void sayHi(){
    printf("Helo Aki");
}