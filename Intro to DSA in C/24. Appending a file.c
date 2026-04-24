#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE * fpointer = fopen("employees.txt", "a");
    fprintf(fpointer, "\n Kelly, Customer Service");
    fclose(fpointer);
    return 0;
}

