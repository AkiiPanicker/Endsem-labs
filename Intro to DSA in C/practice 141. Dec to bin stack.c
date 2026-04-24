#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 32 // Maximum size for binary representation

typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Function to initialize the stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(Stack* stack, int value) {
    if (stack->top < MAX - 1) {
        stack->arr[++stack->top] = value;
    } else {
        printf("Stack Overflow: Unable to push %d\n", value);
    }
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->top--];
    } else {
        printf("Stack Underflow: Unable to pop\n");
        return -1; // Stack is empty
    }
}

// Function to convert decimal to binary using stack
void decimalToBinary(int number) {
    Stack stack;
    initStack(&stack);

    // Edge case for 0
    if (number == 0) {
        printf("Binary representation: 0\n");
        return;
    }

    // Divide the number by 2 and push the remainder to the stack
    while (number > 0) {
        push(&stack, number % 2); // Push remainder
        number /= 2; // Update number
    }

    // Pop all elements from the stack to get the binary representation
    printf("Binary representation: ");
    while (!isEmpty(&stack)) {
        printf("%d", pop(&stack));
    }
    printf("\n");
}

// Main function
int main() {
    int number;

    // Input decimal number
    printf("Enter a decimal number: ");
    scanf("%d", &number);

    // Convert and display binary representation
    decimalToBinary(number);

    return 0;
}
