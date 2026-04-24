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

// Function to convert postfix to prefix
void postfixToPrefix(char* postfix, char* prefix) {
    int i;

    // Read the postfix expression from left to right
    for (i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            // If the character is an operand, push it to the stack
            char operand[2] = {postfix[i], '\0'};
            push(operand);
        } else if (isOperator(postfix[i])) {
            // Pop two operands from the stack
            char op2[MAX], op1[MAX];
            strcpy(op2, pop()); // First popped is second operand
            strcpy(op1, pop()); // Second popped is first operand
            
            // Form the new prefix expression and push it back to the stack
            char newExpr[MAX];
            sprintf(newExpr, "%c%s%s", postfix[i], op1, op2);
            push(newExpr);
        }
    }
    
    // The result is the remaining element in the stack
    strcpy(prefix, pop());
}

int main() {
    char postfix[MAX], prefix[MAX];
    
    printf("Enter a postfix expression: ");
    fgets(postfix, MAX, stdin);
    postfix[strcspn(postfix, "\n")] = 0; // Remove newline character

    postfixToPrefix(postfix, prefix);
    printf("The prefix expression is: %s\n", prefix);

    return 0;
}
