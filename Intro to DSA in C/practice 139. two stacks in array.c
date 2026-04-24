#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100 // Maximum size of the array

typedef struct {
    int top1; // Top index for Stack 1
    int top2; // Top index for Stack 2
    int arr[MAX]; // Array to hold both stacks
} TwoStacks;

// Function to initialize the two stacks
void initTwoStacks(TwoStacks* ts) {
    ts->top1 = -1; // Stack 1 starts from index 0
    ts->top2 = MAX; // Stack 2 starts from the end of the array
}

// Function to push an element onto Stack 1
bool pushStack1(TwoStacks* ts, int value) {
    if (ts->top1 + 1 < ts->top2) { // Check for space
        ts->arr[++ts->top1] = value; // Increment top1 and add value
        return true;
    }
    printf("Stack Overflow: Unable to push %d onto Stack 1\n", value);
    return false; // Stack 1 is full
}

// Function to push an element onto Stack 2
bool pushStack2(TwoStacks* ts, int value) {
    if (ts->top2 - 1 > ts->top1) { // Check for space
        ts->arr[--ts->top2] = value; // Decrement top2 and add value
        return true;
    }
    printf("Stack Overflow: Unable to push %d onto Stack 2\n", value);
    return false; // Stack 2 is full
}

// Function to pop an element from Stack 1
int popStack1(TwoStacks* ts) {
    if (ts->top1 >= 0) { // Check if Stack 1 is not empty
        return ts->arr[ts->top1--]; // Return the top value and decrement top1
    }
    printf("Stack Underflow: Unable to pop from Stack 1\n");
    return -1; // Stack 1 is empty
}

// Function to pop an element from Stack 2
int popStack2(TwoStacks* ts) {
    if (ts->top2 < MAX) { // Check if Stack 2 is not empty
        return ts->arr[ts->top2++]; // Return the top value and increment top2
    }
    printf("Stack Underflow: Unable to pop from Stack 2\n");
    return -1; // Stack 2 is empty
}

// Function to print both stacks
void printStacks(TwoStacks* ts) {
    printf("Stack 1: ");
    for (int i = 0; i <= ts->top1; i++) {
        printf("%d ", ts->arr[i]);
    }
    printf("\n");

    printf("Stack 2: ");
    for (int i = MAX - 1; i >= ts->top2; i--) {
        printf("%d ", ts->arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    TwoStacks ts;
    initTwoStacks(&ts); // Initialize the stacks

    // Push elements onto Stack 1
    pushStack1(&ts, 10);
    pushStack1(&ts, 20);
    pushStack1(&ts, 30);
    
    // Push elements onto Stack 2
    pushStack2(&ts, 40);
    pushStack2(&ts, 50);
    pushStack2(&ts, 60);

    // Print both stacks
    printStacks(&ts);

    // Pop elements from Stack 1
    printf("Popped from Stack 1: %d\n", popStack1(&ts));
    
    // Pop elements from Stack 2
    printf("Popped from Stack 2: %d\n", popStack2(&ts));

    // Print both stacks again
    printStacks(&ts);

    return 0;
}
