#include <stdio.h>
#include <string.h>

int main(){
    char op[5];
    printf("Enter Operator:");
    scanf("%s",op);
    if(!strcmp(op,"+")||!strcmp(op,"-")||!strcmp(op,"*")||!strcmp(op,"/")||!strcmp(op,"%"))
        printf("Arithematic Operator\n");
    else if(!strcmp(op,"==")||!strcmp(op,"!=")||!strcmp(op,">")||!strcmp(op,"<")||!strcmp(op,">=")||!strcmp(op,"<="))
        printf("Relational Operator\n");
    else if(!strcmp(op,"&&")||!strcmp(op,"||")||!strcmp(op,"!"))
        printf("Logical Operator\n");
    else
        printf("Invalid Operator\n");

}