#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for integers
int stack[MAX];
int top = -1;

// Function to push an integer onto the stack
void push(int value) {
    if (top < MAX - 1) {
        stack[++top] = value;
    } else {
        printf("Stack overflow.\n");
    }
}

// Function to pop an integer from the stack
int pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack underflow.\n");
        return 0;
    }
}

// Function to evaluate the prefix expression
int evaluatePrefix(char* expression) {
    int i;
    for (i = strlen(expression) - 1; i >= 0; i--) {
        // If the character is a whitespace, skip it
        if (expression[i] == ' ') continue;

        // If the character is a number, push it to the stack
        if (isdigit(expression[i])) {
            int val = 0;
            int base = 1;

            // Handle multi-digit numbers (process left-to-right)
            while (i >= 0 && isdigit(expression[i])) {
                val += (expression[i] - '0') * base;
                base *= 10;
                i--;
            }
            i++; // Correct for the extra decrement in the loop
            push(val);
        }
        // If the character is an operator
        else {
            int a = pop();
            int b = pop();
            switch (expression[i]) {
                case '+':
                    push(a + b);
                    break;
                case '-':
                    push(a - b);
                    break;
                case '*':
                    push(a * b);
                    break;
                case '/':
                    if (b != 0) {
                        push(a / b);
                    } else {
                        printf("Division by zero is not allowed.\n");
                        return 0;
                    }
                    break;
            }
        }
    }

    // The final result is on the top of the stack
    return pop();
}

int main() {
    char expression[MAX];
    printf("Enter a prefix expression: ");
    fgets(expression, MAX, stdin);
    expression[strcspn(expression, "\n")] = 0; // Remove newline character

    int result = evaluatePrefix(expression);
    printf("The result is: %d\n", result);

    return 0;
}
