#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Initialize the queue
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Check if the queue is empty
int isEmpty(Queue* q) {
    return (q->front == NULL);
}

// Enqueue operation to add an element at the rear of the queue
void enqueue(Queue* q, int value) {
    // Create a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    // If the queue is empty, both front and rear will point to the new node
    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        // Link the new node at the end of the queue and update the rear
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued %d\n", value);
}

// Dequeue operation to remove an element from the front of the queue
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    // Store the front node's data to return it later
    int data = q->front->data;
    Node* temp = q->front;
    
    // Move the front pointer to the next node
    q->front = q->front->next;
    
    // If the queue becomes empty after dequeue, update rear to NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    // Free the dequeued node
    free(temp);
    printf("Dequeued %d\n", data);
    return data;
}

// Display the elements in the queue
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    Node* temp = q->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    display(&q);

    dequeue(&q);
    display(&q);

    dequeue(&q);
    dequeue(&q);
    display(&q);

    return 0;
}
