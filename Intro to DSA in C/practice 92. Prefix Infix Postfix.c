#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack for characters
char stack[MAX];
int top = -1;

// Stack for integers (used in evaluations)
int intStack[MAX];
int intTop = -1;

// Stack operations for characters
void push(char x) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = x;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

char peek() {
    return stack[top];
}

int isEmpty() {
    return top == -1;
}

// Stack operations for integers
void pushInt(int x) {
    if (intTop == MAX - 1) {
        printf("Integer stack overflow\n");
        return;
    }
    intStack[++intTop] = x;
}

int popInt() {
    if (intTop == -1) {
        printf("Integer stack underflow\n");
        return -1;
    }
    return intStack[intTop--];
}

// Helper functions
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int isOperand(char c) {
    return (isdigit(c) || isalpha(c));
}

void reverse(char *exp) {
    int len = strlen(exp);
    for (int i = 0; i < len / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[len - i - 1];
        exp[len - i - 1] = temp;
    }
}

// 1. Convert Infix to Prefix
void infixToPrefix(char *infix, char *prefix) {
    reverse(infix);
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isOperand(infix[i])) {
            prefix[j++] = infix[i];
        } else if (infix[i] == ')') {
            push(infix[i]);
        } else if (infix[i] == '(') {
            while (!isEmpty() && peek() != ')') {
                prefix[j++] = pop();
            }
            pop(); // Remove the closing bracket ')'
        } else if (isOperator(infix[i])) {
            while (!isEmpty() && precedence(peek()) >= precedence(infix[i])) {
                prefix[j++] = pop();
            }
            push(infix[i]);
        }
    }
    while (!isEmpty()) {
        prefix[j++] = pop();
    }
    prefix[j] = '\0';
    reverse(prefix);
}

// 2. Convert Infix to Postfix
void infixToPostfix(char *infix, char *postfix) {
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isOperand(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            pop(); // Remove '('
        } else if (isOperator(infix[i])) {
            while (!isEmpty() && precedence(peek()) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
    }
    while (!isEmpty()) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

// 3. Convert Prefix to Postfix
void prefixToPostfix(char *prefix, char *postfix) {
    reverse(prefix);
    char stack[MAX][MAX];
    int top = -1;
    for (int i = 0; prefix[i] != '\0'; i++) {
        if (isOperand(prefix[i])) {
            char operand[2] = {prefix[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            char temp[MAX];
            snprintf(temp, sizeof(temp), "%s%s%c", op1, op2, prefix[i]);
            strcpy(stack[++top], temp);
        }
    }
    strcpy(postfix, stack[top]);
    reverse(postfix);
}

// 4. Convert Postfix to Prefix
void postfixToPrefix(char *postfix, char *prefix) {
    char stack[MAX][MAX];
    int top = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isOperand(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);
            char temp[MAX];
            snprintf(temp, sizeof(temp), "%c%s%s", postfix[i], op1, op2);
            strcpy(stack[++top], temp);
        }
    }
    strcpy(prefix, stack[top]);
}

// 5. Convert Prefix to Infix
void prefixToInfix(char *prefix, char *infix) {
    reverse(prefix);
    char stack[MAX][MAX];
    int top = -1;
    for (int i = 0; prefix[i] != '\0'; i++) {
        if (isOperand(prefix[i])) {
            char operand[2] = {prefix[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            char temp[MAX];
            snprintf(temp, sizeof(temp), "(%s%c%s)", op1, prefix[i], op2);
            strcpy(stack[++top], temp);
        }
    }
    strcpy(infix, stack[top]);
    reverse(infix);
}

// 6. Convert Postfix to Infix
void postfixToInfix(char *postfix, char *infix) {
    char stack[MAX][MAX];
    int top = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isOperand(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);
            char temp[MAX];
            snprintf(temp, sizeof(temp), "(%s%c%s)", op1, postfix[i], op2);
            strcpy(stack[++top], temp);
        }
    }
    strcpy(infix, stack[top]);
}

// 7. Evaluate Infix Expression (to be handled by converting to postfix and evaluating)
// Use the postfix evaluation method after converting infix to postfix

// 8. Evaluate Postfix Expression
int evaluatePostfix(char *postfix) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            pushInt(postfix[i] - '0');
        } else {
            int val1 = popInt();
            int val2 = popInt();
            switch (postfix[i]) {
                case '+': pushInt(val2 + val1); break;
                case '-': pushInt(val2 - val1); break;
                case '*': pushInt(val2 * val1); break;
                case '/': pushInt(val2 / val1); break;
            }
        }
    }
    return popInt();
}

// 9. Evaluate Prefix Expression
int evaluatePrefix(char *prefix) {
    reverse(prefix);
    for (int i = 0; prefix[i] != '\0'; i++) {
        if (isdigit(prefix[i])) {
            pushInt(prefix[i] - '0');
        } else {
            int val1 = popInt();
            int val2 = popInt();
            switch (prefix[i]) {
                case '+': pushInt(val1 + val2); break;
                case '-': pushInt(val1 - val2); break;
                case '*': pushInt(val1 * val2); break;
                case '/': pushInt(val1 / val2); break;
            }
        }
    }
    return popInt();
}

int main() {
    char infix[MAX], prefix[MAX], postfix[MAX];
    int choice, result;

    do {
        printf("\nChoose an operation:\n");
        printf("1. Infix to Prefix\n");
        printf("2. Infix to Postfix\n");
        printf("3. Prefix to Postfix\n");
        printf("4. Postfix to Prefix\n");
        printf("5. Prefix to Infix\n");
        printf("6. Postfix to Infix\n");
        printf("7. Evaluate Infix Expression\n");
        printf("8. Evaluate Postfix Expression\n");
        printf("9. Evaluate Prefix Expression\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Infix expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Prefix: %s\n", prefix);
                break;

            case 2:
                printf("Enter Infix expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix: %s\n", postfix);
                break;

            case 3:
                printf("Enter Prefix expression: ");
                scanf("%s", prefix);
                prefixToPostfix(prefix, postfix);
                printf("Postfix: %s\n", postfix);
                break;

            case 4:
                printf("Enter Postfix expression: ");
                scanf("%s", postfix);
                postfixToPrefix(postfix, prefix);
                printf("Prefix: %s\n", prefix);
                break;

            case 5:
                printf("Enter Prefix expression: ");
                scanf("%s", prefix);
                prefixToInfix(prefix, infix);
                printf("Infix: %s\n", infix);
                break;

            case 6:
                printf("Enter Postfix expression: ");
                scanf("%s", postfix);
                postfixToInfix(postfix, infix);
                printf("Infix: %s\n", infix);
                break;

            case 7:
                printf("Enter Infix expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                result = evaluatePostfix(postfix);
                printf("Result: %d\n", result);
                break;

            case 8:
                printf("Enter Postfix expression: ");
                scanf("%s", postfix);
                result = evaluatePostfix(postfix);
                printf("Result: %d\n", result);
                break;

            case 9:
                printf("Enter Prefix expression: ");
                scanf("%s", prefix);
                result = evaluatePrefix(prefix);
                printf("Result: %d\n", result);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
