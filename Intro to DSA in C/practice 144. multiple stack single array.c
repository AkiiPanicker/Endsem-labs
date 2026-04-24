#include <stdio.h>
#include <stdlib.h>

#define MAX_STACKS 10
#define MAX_SIZE 100

typedef struct {
    int *arr;      // Array to hold stack elements
    int *top;      // Array to hold the top index for each stack
    int stackSize; // Size of each stack
    int n;         // Number of stacks
} MultiStack;

// Function to create a MultiStack
MultiStack* createMultiStack(int n, int stackSize) {
    MultiStack *ms = (MultiStack *)malloc(sizeof(MultiStack));
    ms->n = n;
    ms->stackSize = stackSize;
    ms->arr = (int *)malloc(n * stackSize * sizeof(int));
    ms->top = (int *)malloc(n * sizeof(int));

    // Initialize top indices
    for (int i = 0; i < n; i++) {
        ms->top[i] = -1; // Stack is initially empty
    }

    return ms;
}

// Function to add an element to stack i
void ADD(MultiStack *ms, int i, int x) {
    if (i < 1 || i > ms->n) {
        printf("Invalid stack number %d\n", i);
        return;
    }
    int stackIndex = i - 1; // Adjust index for 0-based array
    if (ms->top[stackIndex] >= ms->stackSize - 1) {
        printf("Stack %d is full\n", i);
        return;
    }
    // Push element
    ms->arr[stackIndex * ms->stackSize + ++ms->top[stackIndex]] = x;
    printf("Added %d to stack %d\n", x, i);
}

// Function to delete an element from stack i
void DELETE(MultiStack *ms, int i) {
    if (i < 1 || i > ms->n) {
        printf("Invalid stack number %d\n", i);
        return;
    }
    int stackIndex = i - 1; // Adjust index for 0-based array
    if (ms->top[stackIndex] < 0) {
        printf("Stack %d is empty\n", i);
        return;
    }
    // Pop element
    int value = ms->arr[stackIndex * ms->stackSize + ms->top[stackIndex]--];
    printf("Deleted %d from stack %d\n", value, i);
}

// Function to free allocated memory
void freeMultiStack(MultiStack *ms) {
    free(ms->arr);
    free(ms->top);
    free(ms);
}

// Main function
int main() {
    int n, stackSize;
    printf("Enter number of stacks: ");
    scanf("%d", &n);
    printf("Enter size of each stack: ");
    scanf("%d", &stackSize);

    MultiStack *ms = createMultiStack(n, stackSize);
    
    int choice, stackNumber, value;

    do {
        printf("\nMenu:\n1. ADD(i, X)\n2. DELETE(i)\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter stack number (1-%d) and value: ", n);
                scanf("%d %d", &stackNumber, &value);
                ADD(ms, stackNumber, value);
                break;
            case 2:
                printf("Enter stack number (1-%d) to delete from: ", n);
                scanf("%d", &stackNumber);
                DELETE(ms, stackNumber);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 3);

    // Free allocated memory
    freeMultiStack(ms);
    
    return 0;
}
