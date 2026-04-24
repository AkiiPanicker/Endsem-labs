#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *front = NULL;
struct node *rear = NULL;

void enqueue(int x) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = x;
    newnode->next = NULL;

    if (front == NULL && rear == NULL) {
        front = rear = newnode; // Queue was empty
    } else {
        rear->next = newnode; // Link the new node at the end
        rear = newnode;       // Update rear
    }
    printf("%d enqueued to the queue.\n", x);
}

void display() {
    struct node *temp;
    if (front == NULL) {
        printf("Queue is empty.\n");
    } else {
        temp = front;
        printf("Queue elements: ");
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void dequeue() {
    struct node *temp;
    if (front == NULL) {
        printf("Queue is empty. Cannot dequeue.\n");
    } else {
        temp = front;
        printf("Dequeued element: %d\n", front->data);
        front = front->next; // Move front to the next node
        free(temp);          // Free the dequeued node

        // If the queue becomes empty after dequeuing
        if (front == NULL) {
            rear = NULL; // Also set rear to NULL
        }
    }
}

void peek() {
    if (front == NULL) {
        printf("Queue is empty.\n");
    } else {
        printf("Front element is: %d\n", front->data);
    }
}

int main() {
    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
