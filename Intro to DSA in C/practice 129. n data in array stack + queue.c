#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50   // Maximum total size for array A
#define STACK_SIZE 5  // Maximum size for each stack
#define QUEUE_SIZE 5  // Maximum size for each queue
#define N 4           // Total data objects (2 stacks and 2 queues for example)

int A[MAX_SIZE];           // Unified array to hold both stacks and queues
int top[2] = {-1, -1};     // Top pointers for 2 stacks
int front[2] = {-1, -1};   // Front pointers for 2 queues
int rear[2] = {-1, -1};    // Rear pointers for 2 queues

// Check if space is full for the whole array
int SPACE_FULL() {
    int used = 0;
    for (int i = 0; i < 2; i++) {
        used += (top[i] + 1); // Count used spaces for stacks
        used += (rear[i] - front[i] + QUEUE_SIZE) % QUEUE_SIZE; // Used spaces for queues
    }
    return used >= MAX_SIZE;
}

// Stack Push operation
void PUSH(int stackNum, int value) {
    if (SPACE_FULL()) {
        printf("No space to add to stack %d.\n", stackNum + 1);
        return;
    }
    if (top[stackNum] < STACK_SIZE - 1) {
        top[stackNum]++;
        A[stackNum * STACK_SIZE + top[stackNum]] = value;
        printf("Pushed %d to Stack %d.\n", value, stackNum + 1);
    } else {
        printf("Stack %d is full.\n", stackNum + 1);
    }
}

// Stack Pop operation
void POP(int stackNum) {
    if (top[stackNum] == -1) {
        printf("Stack %d is empty.\n", stackNum + 1);
    } else {
        int value = A[stackNum * STACK_SIZE + top[stackNum]];
        top[stackNum]--;
        printf("Popped %d from Stack %d.\n", value, stackNum + 1);
    }
}

// Queue Enqueue operation
void ENQUEUE(int queueNum, int value) {
    if (SPACE_FULL()) {
        printf("No space to add to Queue %d.\n", queueNum + 1);
        return;
    }
    int base = 2 * STACK_SIZE + queueNum * QUEUE_SIZE;
    if ((rear[queueNum] + 1) % QUEUE_SIZE == front[queueNum]) {
        printf("Queue %d is full.\n", queueNum + 1);
    } else {
        if (front[queueNum] == -1) front[queueNum] = 0;
        rear[queueNum] = (rear[queueNum] + 1) % QUEUE_SIZE;
        A[base + rear[queueNum]] = value;
        printf("Enqueued %d to Queue %d.\n", value, queueNum + 1);
    }
}

// Queue Dequeue operation
void DEQUEUE(int queueNum) {
    if (front[queueNum] == -1) {
        printf("Queue %d is empty.\n", queueNum + 1);
    } else {
        int base = 2 * STACK_SIZE + queueNum * QUEUE_SIZE;
        int value = A[base + front[queueNum]];
        if (front[queueNum] == rear[queueNum]) {
            front[queueNum] = rear[queueNum] = -1;
        } else {
            front[queueNum] = (front[queueNum] + 1) % QUEUE_SIZE;
        }
        printf("Dequeued %d from Queue %d.\n", value, queueNum + 1);
    }
}

// Display all elements of a stack
void displayStack(int stackNum) {
    if (top[stackNum] == -1) {
        printf("Stack %d is empty.\n", stackNum + 1);
        return;
    }
    printf("Stack %d: ", stackNum + 1);
    for (int i = 0; i <= top[stackNum]; i++) {
        printf("%d ", A[stackNum * STACK_SIZE + i]);
    }
    printf("\n");
}

// Display all elements of a queue
void displayQueue(int queueNum) {
    if (front[queueNum] == -1) {
        printf("Queue %d is empty.\n", queueNum + 1);
        return;
    }
    printf("Queue %d: ", queueNum + 1);
    int i = front[queueNum];
    do {
        printf("%d ", A[2 * STACK_SIZE + queueNum * QUEUE_SIZE + i]);
        i = (i + 1) % QUEUE_SIZE;
    } while (i != (rear[queueNum] + 1) % QUEUE_SIZE);
    printf("\n");
}

int main() {
    int choice, dataObj, value;

    do {
        printf("\nMenu:\n");
        printf("1. Push to Stack\n");
        printf("2. Pop from Stack\n");
        printf("3. Enqueue to Queue\n");
        printf("4. Dequeue from Queue\n");
        printf("5. Display Stack\n");
        printf("6. Display Queue\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &dataObj);
                printf("Enter value to push: ");
                scanf("%d", &value);
                PUSH(dataObj - 1, value);
                break;
            case 2:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &dataObj);
                POP(dataObj - 1);
                break;
            case 3:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &dataObj);
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                ENQUEUE(dataObj - 1, value);
                break;
            case 4:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &dataObj);
                DEQUEUE(dataObj - 1);
                break;
            case 5:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &dataObj);
                displayStack(dataObj - 1);
                break;
            case 6:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &dataObj);
                displayQueue(dataObj - 1);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);

    return 0;
}
