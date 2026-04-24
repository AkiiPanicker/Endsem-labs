#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Function to push an operator onto the stack
void push(char operator) {
    if (top < MAX - 1) {
        stack[++top] = operator;
    }
}

// Function to pop an operator from the stack
char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0'; // Return null character if stack is empty
}

// Function to check the precedence of operators
int precedence(char operator) {
    switch (operator) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Function to check if the character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop(); // pop '('
        } else if (isOperator(infix[i])) {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
        i++;
    }
    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0'; // Null terminate the postfix string
}

// Function to convert infix to prefix
void infixToPrefix(char* infix, char* prefix) {
    // Step 1: Reverse the infix expression
    int len = strlen(infix);
    char reversedInfix[MAX];
    for (int i = 0; i < len; i++) {
        if (infix[len - 1 - i] == '(') {
            reversedInfix[i] = ')';
        } else if (infix[len - 1 - i] == ')') {
            reversedInfix[i] = '(';
        } else {
            reversedInfix[i] = infix[len - 1 - i];
        }
    }
    reversedInfix[len] = '\0';

    // Step 2: Convert reversed infix to postfix
    char postfix[MAX];
    infixToPostfix(reversedInfix, postfix);

    // Step 3: Reverse the postfix expression to get prefix
    for (int i = 0; i < strlen(postfix); i++) {
        prefix[i] = postfix[strlen(postfix) - 1 - i];
    }
    prefix[strlen(postfix)] = '\0'; // Null terminate the prefix string
}

int main() {
    char infix[MAX], prefix[MAX];
    
    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = 0; // Remove newline character

    infixToPrefix(infix, prefix);
    printf("The prefix expression is: %s\n", prefix);

    return 0;
}
