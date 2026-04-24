#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // Maximum size of the deque

typedef struct {
    char data[MAX][100]; // Array to store strings, each up to 100 characters
    int front;
    int rear;
} Deque;

// Function to initialize the deque
void initDeque(Deque *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the deque is empty
int isEmpty(Deque *q) {
    return (q->front == -1 && q->rear == -1);
}

// Check if the deque is full
int isFull(Deque *q) {
    return ((q->rear + 1) % MAX == q->front);
}

// Insert at the rear
void insertRear(Deque *q, char *str) {
    if (isFull(q)) {
        printf("\nQueue is full! Cannot insert.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    strcpy(q->data[q->rear], str);
    printf("Inserted '%s' at rear\n", str);
}

// Insert at the front
void insertFront(Deque *q, char *str) {
    if (isFull(q)) {
        printf("\nQueue is full! Cannot insert.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->front = (q->front - 1 + MAX) % MAX;
    }
    strcpy(q->data[q->front], str);
    printf("Inserted '%s' at front\n", str);
}

// Delete from the front
void deleteFront(Deque *q) {
    if (isEmpty(q)) {
        printf("\nQueue is empty! Cannot delete.\n");
        return;
    }
    printf("Deleted '%s' from front\n", q->data[q->front]);
    if (q->front == q->rear) {
        q->front = q->rear = -1; // Queue becomes empty
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

// Display the deque contents
void display(Deque *q) {
    if (isEmpty(q)) {
        printf("\nQueue is empty!\n");
        return;
    }
    printf("\nQueue contents:\n");
    int i = q->front;
    while (1) {
        printf("%s ", q->data[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    Deque q;
    initDeque(&q);

    int op;
    char str[100];

    do {
        printf("\n1. Insert at Front\n2. Insert at Rear\n3. Delete from Front\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &op);
        
        switch (op) {
            case 1:
                printf("Enter string to insert at front: ");
                scanf("%s", str);
                insertFront(&q, str);
                break;
            case 2:
                printf("Enter string to insert at rear: ");
                scanf("%s", str);
                insertRear(&q, str);
                break;
            case 3:
                deleteFront(&q);
                break;
            case 4:
                display(&q);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (op != 5);

    return 0;
}
