#include <stdio.h>
#include <stdlib.h>

#define MAX 100 

int queue1[MAX];
int queue2[MAX];
int front1 = -1, rear1 = -1;
int front2 = -1, rear2 = -1;

int isEmpty(int queue) {
    if (queue == 1) {
        return (front1 == -1);
    } else {
        return (front2 == -1);
    }
}

void enqueue(int queue, int value) {
    if (queue == 1) {
        if (rear1 == MAX - 1) {
            printf("Queue 1 is full\n");
            return;
        }
        if (front1 == -1) {
            front1 = 0; 
        }
        rear1++;
        queue1[rear1] = value;
    } else {
        if (rear2 == MAX - 1) {
            printf("Queue 2 is full\n");
            return;
        }
        if (front2 == -1) {
            front2 = 0;
        }
        rear2++;
        queue2[rear2] = value;
    }
}

int dequeue(int queue) {
    int value;
    if (queue == 1) {
        if (isEmpty(1)) {
            printf("Queue 1 is empty\n");
            return -1;
        }
        value = queue1[front1];
        front1++;
        if (front1 > rear1) { 
            front1 = rear1 = -1;
        }
    } else {
        if (isEmpty(2)) {
            printf("Queue 2 is empty\n");
            return -1;
        }
        value = queue2[front2];
        front2++;
        if (front2 > rear2) { 
            front2 = rear2 = -1;
        }
    }
    return value;
}

void push(int value) {
    enqueue(2, value); 

    while (!isEmpty(1)) {
        enqueue(2, dequeue(1)); 
    }

    // Swap queue1 and queue2
    int tempFront = front1;
    int tempRear = rear1;
    front1 = front2;
    rear1 = rear2;
    front2 = tempFront;
    rear2 = tempRear;
}

int pop() {
    if (isEmpty(1)) {
        printf("Stack is empty\n");
        return -1;
    }
    return dequeue(1); 
}

void display() {
    if (isEmpty(1)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    for (int i = front1; i <= rear1; i++) {
        printf("%d ", queue1[i]);
    }
    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                value = pop();
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
