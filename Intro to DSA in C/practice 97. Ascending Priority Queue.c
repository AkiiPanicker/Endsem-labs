#include <stdio.h>
#include <stdlib.h>
#define N 10

int queue[N];
int front = -1;
int rear = -1;

// Function to enqueue an element in the priority queue
void enqueue() {
    int data;
    printf("Enter data: ");
    scanf("%d", &data);

    if (rear == N - 1) {
        printf("Overflow\n");
        return;
    }

    // If queue is empty
    if (front == -1) {
        front++;
        rear++;
        queue[rear] = data;
        return;
    }

    // Call priority function to insert in the correct position
    priority(data);
}

// Function to insert an element at the correct position based on priority
void priority(int data) {
    if (queue[rear] < data) {
        rear++;
        queue[rear] = data;
    } else {
        for (int i = rear; i >= front; i--) {
            if (queue[i] > data) {
                queue[i + 1] = queue[i]; // Shift elements to the right
            } else {
                queue[i + 1] = data;
                break;
            }
        }
        rear++; // Increment the rear index
    }
}

// Function to dequeue an element from the priority queue
void dequeue() {
    if (front == -1) {
        printf("Queue is empty\n");
        return;
    } else if (front == rear) {
        printf("Dequeued: %d\n", queue[front]);
        front = -1;
        rear = -1;
        return;
    }

    printf("Dequeued: %d\n", queue[front]);
    front++; // Increment front to remove the element
}

// Function to display the elements of the queue
void display() {
    if (front == -1) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

// Main function to drive the program
int main() {
    int choice;

    while (1) {
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
