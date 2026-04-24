#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for integers (operands)
int operands[MAX];
int topOperands = -1;

// Stack for characters (operators)
char operators[MAX];
int topOperators = -1;

// Function to push an integer operand onto the operand stack
void pushOperand(int value) {
    if (topOperands < MAX - 1) {
        operands[++topOperands] = value;
    } else {
        printf("Operand stack overflow.\n");
    }
}

// Function to push an operator onto the operator stack
void pushOperator(char op) {
    if (topOperators < MAX - 1) {
        operators[++topOperators] = op;
    } else {
        printf("Operator stack overflow.\n");
    }
}

// Function to pop an operand from the operand stack
int popOperand() {
    if (topOperands >= 0) {
        return operands[topOperands--];
    } else {
        printf("Operand stack underflow.\n");
        return 0;
    }
}

// Function to pop an operator from the operator stack
char popOperator() {
    if (topOperators >= 0) {
        return operators[topOperators--];
    } else {
        printf("Operator stack underflow.\n");
        return '\0';
    }
}

// Function to get the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to apply an operator to two operands
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// Function to evaluate an infix expression
int evaluate(char* expression) {
    int i;
    for (i = 0; i < strlen(expression); i++) {
        // If the character is whitespace, skip it
        if (expression[i] == ' ') continue;

        // If the character is a number, push it to the operand stack
        if (isdigit(expression[i])) {
            int val = 0;

            // Handle multi-digit numbers
            while (i < strlen(expression) && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            i--; // Correct for the extra increment in the loop
            pushOperand(val);
        }
        // If the character is an open parenthesis, push it to the operator stack
        else if (expression[i] == '(') {
            pushOperator(expression[i]);
        }
        // If the character is a closing parenthesis, solve the entire parenthesis
        else if (expression[i] == ')') {
            while (topOperators != -1 && operators[topOperators] != '(') {
                int b = popOperand();
                int a = popOperand();
                char op = popOperator();
                pushOperand(applyOp(a, b, op));
            }
            popOperator(); // Pop the '(' from the stack
        }
        // If the character is an operator
        else {
            while (topOperators != -1 && precedence(operators[topOperators]) >= precedence(expression[i])) {
                int b = popOperand();
                int a = popOperand();
                char op = popOperator();
                pushOperand(applyOp(a, b, op));
            }
            pushOperator(expression[i]);
        }
    }

    // Entire expression has been parsed at this point, apply remaining operators
    while (topOperators != -1) {
        int b = popOperand();
        int a = popOperand();
        char op = popOperator();
        pushOperand(applyOp(a, b, op));
    }

    // The result is on the top of the operand stack
    return popOperand();
}

int main() {
    char expression[MAX];
    printf("Enter an infix expression: ");
    fgets(expression, MAX, stdin);
    expression[strcspn(expression, "\n")] = 0; // Remove newline character

    int result = evaluate(expression);
    printf("The result is: %d\n", result);

    return 0;
}
