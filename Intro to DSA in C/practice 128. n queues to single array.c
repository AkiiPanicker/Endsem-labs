#include <stdio.h>
#include <stdlib.h>

#define SIZE 5            // Max number of elements per queue
#define N 3               // Number of queues

int A[SIZE * N];          // Single array representing multiple queues
int front[N], rear[N];    // Front and rear pointers for each queue

void initializeQueues() {
    for (int i = 0; i < N; i++) {
        front[i] = rear[i] = -1;
    }
}

// Check if a particular queue is full
int QUEUE_FULL(int q) {
    return (rear[q] + 1) % SIZE == front[q];
}

// Check if a particular queue is empty
int QUEUE_EMPTY(int q) {
    return front[q] == -1;
}

// Add an element to queue `q`
void ADDQ(int q, int value) {
    if (QUEUE_FULL(q)) {
        printf("Queue %d is full.\n", q + 1);
        return;
    }
    if (QUEUE_EMPTY(q)) {
        front[q] = rear[q] = 0;
    } else {
        rear[q] = (rear[q] + 1) % SIZE;
    }
    A[q * SIZE + rear[q]] = value;
    printf("Added %d to Queue %d.\n", value, q + 1);
}

// Delete an element from queue `q`
void DELETEQ(int q) {
    if (QUEUE_EMPTY(q)) {
        printf("Queue %d is empty.\n", q + 1);
        return;
    }
    int value = A[q * SIZE + front[q]];
    if (front[q] == rear[q]) {
        front[q] = rear[q] = -1;  // Reset if the queue becomes empty
    } else {
        front[q] = (front[q] + 1) % SIZE;
    }
    printf("Deleted %d from Queue %d.\n", value, q + 1);
}

// Display contents of a specific queue
void displayQueue(int q) {
    if (QUEUE_EMPTY(q)) {
        printf("Queue %d is empty.\n", q + 1);
        return;
    }
    printf("Queue %d: ", q + 1);
    int i = front[q];
    while (1) {
        printf("%d ", A[q * SIZE + i]);
        if (i == rear[q]) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    initializeQueues();
    int choice, queueNum, value;

    do {
        printf("\nMenu:\n");
        printf("1. Add to Queue\n");
        printf("2. Delete from Queue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter queue number (1-%d): ", N);
                scanf("%d", &queueNum);
                if (queueNum < 1 || queueNum > N) {
                    printf("Invalid queue number.\n");
                    break;
                }
                printf("Enter value to add: ");
                scanf("%d", &value);
                ADDQ(queueNum - 1, value);
                break;

            case 2:
                printf("Enter queue number (1-%d): ", N);
                scanf("%d", &queueNum);
                if (queueNum < 1 || queueNum > N) {
                    printf("Invalid queue number.\n");
                    break;
                }
                DELETEQ(queueNum - 1);
                break;

            case 3:
                printf("Enter queue number (1-%d): ", N);
                scanf("%d", &queueNum);
                if (queueNum < 1 || queueNum > N) {
                    printf("Invalid queue number.\n");
                    break;
                }
                displayQueue(queueNum - 1);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
