#include <stdio.h>
#include <string.h>

#define MAX 5    // Define maximum number of elements in the circular queue
#define STR_SIZE 50  // Define maximum size for each string

// Circular queue structure
typedef struct {
    char data[MAX][STR_SIZE];   // Array to hold strings
    int front;                  // Index of front element
    int rear;                   // Index of rear element
} CircularQueue;

// Initialize the circular queue
void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is full
int isFull(CircularQueue *q) {
    return ((q->rear + 1) % MAX == q->front);
}

// Check if the queue is empty
int isEmpty(CircularQueue *q) {
    return (q->front == -1);
}

// Insert a string into the circular queue
void insertcq(CircularQueue *q, char str[]) {
    if (isFull(q)) {
        printf("Queue is full. Cannot insert.\n");
        return;
    }

    // If queue is empty, initialize front and rear to 0
    if (isEmpty(q)) {
        q->front = 0;
    }

    // Move rear to the next position in a circular manner
    q->rear = (q->rear + 1) % MAX;
    strcpy(q->data[q->rear], str);
    printf("Inserted: %s\n", str);
}

// Delete a string from the circular queue
void deletecq(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot delete.\n");
        return;
    }

    // Display the element being removed
    printf("Deleted: %s\n", q->data[q->front]);

    // If there was only one element in the queue, reset it to empty state
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        // Move front to the next position in a circular manner
        q->front = (q->front + 1) % MAX;
    }
}

// Display elements in the circular queue
void displaycq(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements:\n");
    int i = q->front;
    while (1) {
        printf("%s ", q->data[i]);
        if (i == q->rear) {
            break;
        }
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Main function to test circular queue operations
int main() {
    CircularQueue q;
    initQueue(&q);

    insertcq(&q, "Alice");
    insertcq(&q, "Bob");
    insertcq(&q, "Charlie");
    insertcq(&q, "Diana");
    insertcq(&q, "Eve");

    displaycq(&q);  // Should display all elements

    deletecq(&q);  // Deletes "Alice"
    deletecq(&q);  // Deletes "Bob"

    displaycq(&q);  // Displays remaining elements

    insertcq(&q, "Frank");  // Inserts "Frank"
    insertcq(&q, "Grace");  // Inserts "Grace"

    displaycq(&q);  // Should display all elements in the new order

    return 0;
}
