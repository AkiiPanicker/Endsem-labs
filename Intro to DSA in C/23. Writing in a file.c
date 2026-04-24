#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * fpointer = fopen("employees.txt", "w");
    fprintf(fpointer, "Jim, Salesman \n Pam, Receptionist \n Oscar, Accountant");
    fclose(fpointer);
    return 0;
}