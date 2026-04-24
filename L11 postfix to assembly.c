#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char stack[100][10];
int top = -1;

void push(char *item){
    strcpy(stack[++top],item);
}

void pop(char *item){
    strcpy(item, stack[top--]);

}

int main(){
    char postfix[100], op1[10], op2[10], res[10];
    int reg_count = 0;

    printf("Enter postfix expression (e.g., ab+cd/*): ");
    scanf("%s", postfix);

    printf("\nGenerated Assembly Code:\n");

    for(int i=0;postfix[i]!='\0';i++){
        char symbol = postfix[i];
        if(isalnum(symbol)){
            char temp[2] = {symbol,'\0'};
            push(temp);
        }
        else{
            pop(op2);
            pop(op1);

            printf("LOAD R%d, %s\n",reg_count,op1);

            switch(symbol){
                case '+': printf("ADD R%d, %s\n",reg_count,op2); break;
                case '-': printf("SUB R%d, %s\n",reg_count,op2); break;
                case '*': printf("MUL R%d, %s\n",reg_count,op2); break;
                case '/': printf("DIV R%d, %s\n",reg_count,op2); break;
            }
            sprintf(res,"R%d", reg_count);
            push(res);
            reg_count++;
        }
    }
    return 0;
}