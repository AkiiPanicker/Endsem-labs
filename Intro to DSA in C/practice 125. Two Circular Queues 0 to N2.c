#include <stdio.h>
#include <stdbool.h>

#define MAX 10  // Define maximum size of the array

// Structure to represent two circular queues in a single array
typedef struct {
    int data[MAX];  // Array to hold the elements of both queues
    int front1;     // Front index of the first queue
    int rear1;      // Rear index of the first queue
    int front2;     // Front index of the second queue
    int rear2;      // Rear index of the second queue
} TwoCircularQueues;

// Initialize the two circular queues
void initQueues(TwoCircularQueues *queues) {
    queues->front1 = -1;
    queues->rear1 = -1;
    queues->front2 = MAX / 2;  // Second queue starts from the middle
    queues->rear2 = MAX / 2;   // Rear of second queue starts from the middle
}

// Check if the first queue is full
bool isFull1(TwoCircularQueues *queues) {
    return (queues->rear1 + 1) % (MAX / 2) == queues->front1;
}

// Check if the second queue is full
bool isFull2(TwoCircularQueues *queues) {
    return (queues->rear2 + 1) % (MAX / 2) == queues->front2;
}

// Check if the first queue is empty
bool isEmpty1(TwoCircularQueues *queues) {
    return queues->front1 == -1;
}

// Check if the second queue is empty
bool isEmpty2(TwoCircularQueues *queues) {
    return queues->front2 == MAX / 2;
}

// Insert an element into the first circular queue
void insertQueue1(TwoCircularQueues *queues, int value) {
    if (isFull1(queues)) {
        printf("First queue is full. Cannot insert %d.\n", value);
        return;
    }
    if (isEmpty1(queues)) {
        queues->front1 = 0; // Set front for the first queue
    }
    queues->rear1 = (queues->rear1 + 1) % (MAX / 2); // Circular increment
    queues->data[queues->rear1] = value;
    printf("Inserted %d into first queue.\n", value);
}

// Insert an element into the second circular queue
void insertQueue2(TwoCircularQueues *queues, int value) {
    if (isFull2(queues)) {
        printf("Second queue is full. Cannot insert %d.\n", value);
        return;
    }
    if (isEmpty2(queues)) {
        queues->front2 = MAX / 2; // Set front for the second queue
    }
    queues->rear2 = (queues->rear2 + 1) % (MAX / 2) + (MAX / 2); // Circular increment
    queues->data[queues->rear2] = value;
    printf("Inserted %d into second queue.\n", value);
}

// Delete an element from the first circular queue
void deleteQueue1(TwoCircularQueues *queues) {
    if (isEmpty1(queues)) {
        printf("First queue is empty. Cannot delete.\n");
        return;
    }
    printf("Deleted %d from first queue.\n", queues->data[queues->front1]);
    if (queues->front1 == queues->rear1) { // Only one element was present
        queues->front1 = -1;
        queues->rear1 = -1;
    } else {
        queues->front1 = (queues->front1 + 1) % (MAX / 2);
    }
}

// Delete an element from the second circular queue
void deleteQueue2(TwoCircularQueues *queues) {
    if (isEmpty2(queues)) {
        printf("Second queue is empty. Cannot delete.\n");
        return;
    }
    printf("Deleted %d from second queue.\n", queues->data[queues->front2]);
    if (queues->front2 == queues->rear2) { // Only one element was present
        queues->front2 = MAX / 2;
        queues->rear2 = MAX / 2;
    } else {
        queues->front2 = (queues->front2 + 1) % (MAX / 2) + (MAX / 2);
    }
}

// Display the elements of the first circular queue
void displayQueue1(TwoCircularQueues *queues) {
    if (isEmpty1(queues)) {
        printf("First queue is empty.\n");
        return;
    }
    printf("First Queue elements: ");
    for (int i = queues->front1; ; i = (i + 1) % (MAX / 2)) {
        printf("%d ", queues->data[i]);
        if (i == queues->rear1) break;
    }
    printf("\n");
}

// Display the elements of the second circular queue
void displayQueue2(TwoCircularQueues *queues) {
    if (isEmpty2(queues)) {
        printf("Second queue is empty.\n");
        return;
    }
    printf("Second Queue elements: ");
    for (int i = queues->front2; ; i = (i + 1) % (MAX / 2) + (MAX / 2)) {
        printf("%d ", queues->data[i]);
        if (i == queues->rear2) break;
    }
    printf("\n");
}

// Main function to test the two circular queues
int main() {
    TwoCircularQueues queues;
    initQueues(&queues);

    // Inserting into the first circular queue
    insertQueue1(&queues, 1);
    insertQueue1(&queues, 2);
    insertQueue1(&queues, 3);
    displayQueue1(&queues);

    // Inserting into the second circular queue
    insertQueue2(&queues, 4);
    insertQueue2(&queues, 5);
    displayQueue2(&queues);

    // Deleting from both queues
    deleteQueue1(&queues);
    deleteQueue2(&queues);
    
    // Display both queues after deletion
    displayQueue1(&queues);
    displayQueue2(&queues);

    return 0;
}
