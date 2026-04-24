#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Structure definition for the deque
struct Deque {
    int items[MAX];
    int front, rear;
};

// Function to initialize the deque
void initialize(struct Deque* dq) {
    dq->front = -1;
    dq->rear = -1;
}

// Check if the deque is empty
int isEmpty(struct Deque* dq) {
    return dq->front == -1;
}

// Check if the deque is full
int isFull(struct Deque* dq) {
    return (dq->front == 0 && dq->rear == MAX - 1) || (dq->front == dq->rear + 1);
}

// Function to insert an element at the front of the deque
void addFront(struct Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque is full\n");
        return;
    }
    if (isEmpty(dq)) { // First element insertion
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = MAX - 1; // Wrap around to the end
    } else {
        dq->front = dq->front - 1;
    }
    dq->items[dq->front] = value;
}

// Function to delete an element from the front of the deque
int deleteFront(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        exit(1);
    }
    int data = dq->items[dq->front];
    if (dq->front == dq->rear) { // Only one element
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->front == MAX - 1) {
        dq->front = 0; // Wrap around
    } else {
        dq->front = dq->front + 1;
    }
    return data;
}

// Function to delete an element from the rear of the deque
int deleteRear(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        exit(1);
    }
    int data = dq->items[dq->rear];
    if (dq->front == dq->rear) { // Only one element
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = MAX - 1; // Wrap around
    } else {
        dq->rear = dq->rear - 1;
    }
    return data;
}

// Display function to show the current elements in the deque
void display(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque elements: ");
    int i = dq->front;
    while (1) {
        printf("%d ", dq->items[i]);
        if (i == dq->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    struct Deque dq;
    initialize(&dq);

    addFront(&dq, 10);
    addFront(&dq, 20);
    addFront(&dq, 30);

    printf("After adding elements to front:\n");
    display(&dq);

    printf("Deleting from front: %d\n", deleteFront(&dq));
    display(&dq);

    printf("Deleting from rear: %d\n", deleteRear(&dq));
    display(&dq);

    return 0;
}
