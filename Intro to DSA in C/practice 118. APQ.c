#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10 // Initial capacity for the priority queue

typedef struct {
    int* data;      // Array to store elements
    int size;       // Current number of elements in the priority queue
    int capacity;   // Current capacity of the array
} AscendingPriorityQueue;

// Function to initialize the priority queue
void initAPQ(AscendingPriorityQueue* pq) {
    pq->data = (int*)malloc(INITIAL_SIZE * sizeof(int));
    pq->size = 0;
    pq->capacity = INITIAL_SIZE;
}

// Function to free the allocated memory for the priority queue
void freeAPQ(AscendingPriorityQueue* pq) {
    free(pq->data);
}

// Function to insert an element into the ascending priority queue
void pqInsert(AscendingPriorityQueue* pq, int x) {
    // Check if the array needs to be resized
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->data = (int*)realloc(pq->data, pq->capacity * sizeof(int));
    }

    // Insert the element while maintaining order
    int i;
    for (i = pq->size - 1; (i >= 0 && pq->data[i] > x); i--) {
        pq->data[i + 1] = pq->data[i]; // Shift elements to the right
    }
    pq->data[i + 1] = x; // Insert the new element
    pq->size++;
}

// Function to remove and return the minimum element from the ascending priority queue
int pqMinDelete(AscendingPriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty\n");
        return -1; // Indicate error
    }
    return pq->data[--pq->size]; // Return the last element (minimum) and reduce size
}

// Function to display the contents of the ascending priority queue
void displayAPQ(AscendingPriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->data[i]);
    }
    printf("\n");
}

// Example usage of the ascending priority queue
int main() {
    AscendingPriorityQueue pq;
    initAPQ(&pq);

    // Inserting elements into the priority queue
    pqInsert(&pq, 30);
    pqInsert(&pq, 20);
    pqInsert(&pq, 50);
    pqInsert(&pq, 10);
    pqInsert(&pq, 40);

    printf("Priority Queue after inserts: ");
    displayAPQ(&pq);

    // Removing the minimum element
    printf("Minimum element removed: %d\n", pqMinDelete(&pq));
    printf("Priority Queue after removing the minimum: ");
    displayAPQ(&pq);

    // Free the allocated memory
    freeAPQ(&pq);
    return 0;
}
