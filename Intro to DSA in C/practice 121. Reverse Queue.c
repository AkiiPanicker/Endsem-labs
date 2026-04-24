#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Define a structure for the queue
struct Queue {
    int items[MAX];
    int front, rear;
};

// Function to initialize the queue
void initialize(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int empty(struct Queue* q) {
    return q->front == -1;
}

// Function to check if the queue is full
int full(struct Queue* q) {
    return q->rear == MAX - 1;
}

// Function to enqueue an element to the queue
void enqueue(struct Queue* q, int value) {
    if (full(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* q) {
    if (empty(q)) {
        printf("Queue is empty\n");
        exit(1);
    }
    int item = q->items[q->front];
    if (q->front >= q->rear) { // Queue is now empty
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

// Recursive function to reverse the queue
void reverseQueue(struct Queue* q) {
    if (empty(q)) {
        return;
    }

    // Dequeue the front element
    int item = dequeue(q);

    // Recursively reverse the remaining queue
    reverseQueue(q);

    // Enqueue the dequeued element at the end
    enqueue(q, item);
}

// Function to display the queue
void display(struct Queue* q) {
    if (empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

int main() {
    struct Queue q;
    initialize(&q);

    // Enqueue some elements
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    printf("Original Queue: ");
    display(&q);

    // Reverse the queue
    reverseQueue(&q);

    printf("Reversed Queue: ");
    display(&q);

    return 0;
}
