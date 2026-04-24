#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX][MAX]; // Stack to hold the expressions
int top = -1;

// Function to push an expression onto the stack
void push(char* expression) {
    if (top < MAX - 1) {
        top++;
        strcpy(stack[top], expression);
    }
}

// Function to pop an expression from the stack
char* pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return NULL; // Return NULL if stack is empty
}

// Function to check if the character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to convert prefix to infix
void prefixToInfix(char* prefix, char* infix) {
    int i;
    
    // Read the prefix expression from right to left
    for (i = strlen(prefix) - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            // If the character is an operand, push it to the stack
            char operand[2] = {prefix[i], '\0'};
            push(operand);
        } else if (isOperator(prefix[i])) {
            // Pop two operands from the stack
            char op1[MAX], op2[MAX];
            strcpy(op1, pop());
            strcpy(op2, pop());
            
            // Form the new infix expression and push it back to the stack
            char newExpr[MAX];
            sprintf(newExpr, "(%s %c %s)", op1, prefix[i], op2);
            push(newExpr);
        }
    }
    
    // The result is the remaining element in the stack
    strcpy(infix, pop());
}

int main() {
    char prefix[MAX], infix[MAX];
    
    printf("Enter a prefix expression: ");
    fgets(prefix, MAX, stdin);
    prefix[strcspn(prefix, "\n")] = 0; // Remove newline character

    prefixToInfix(prefix, infix);
    printf("The infix expression is: %s\n", infix);

    return 0;
}
