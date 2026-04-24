#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100 // Maximum size of the stack

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

// Function to insert an element at the bottom of the stack
void insertAtBottom(Stack* stack, int value) {
    if (isEmpty(stack)) {
        push(stack, value);
    } else {
        int topElement = pop(stack); // Remove the top element
        insertAtBottom(stack, value); // Recursively call for the next elements
        push(stack, topElement); // Push the top element back onto the stack
    }
}

// Function to reverse the stack using recursion
void reverseStack(Stack* stack) {
    if (!isEmpty(stack)) {
        int topElement = pop(stack); // Remove the top element
        reverseStack(stack); // Recursively reverse the remaining stack
        insertAtBottom(stack, topElement); // Insert the popped element at the bottom
    }
}

// Function to print the stack
void printStack(Stack* stack) {
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    Stack stack;
    initStack(&stack); // Initialize the stack

    // Push elements onto the stack
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 4);
    push(&stack, 5);

    printf("Original Stack: ");
    printStack(&stack);

    // Reverse the stack
    reverseStack(&stack);

    printf("Reversed Stack: ");
    printStack(&stack);

    return 0;
}
