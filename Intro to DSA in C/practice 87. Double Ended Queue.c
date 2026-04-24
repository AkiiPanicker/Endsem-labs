#include <stdio.h>
#include <stdlib.h>
#define N 5

int deque[N];
int f = -1, r = -1;

void enqueueFront(int x) {
    if ((f == 0 && r == N - 1) || (f == r + 1)) {
        printf("Overflow\n");
    } 
    else if (f == -1 && r == -1) {
        f = r = 0;
        deque[f] = x;
    } 
    else if (f == 0) {
        f = N - 1;
        deque[f] = x;
    } 
    else {
        f--;
        deque[f] = x;
    }
}

void enqueueRear(int x) {
    if ((f == 0 && r == N - 1) || (f == r + 1)) {
        printf("Overflow\n");
    } 
    else if (f == -1 && r == -1) {
        f = r = 0;
        deque[r] = x;
    } 
    else if (r == N - 1) {
        r = 0;
        deque[r] = x;
    } 
    else {
        r++;
        deque[r] = x;
    }
}

void display() {
    if (f == -1) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque elements: ");
    int i = f;
    while (i != r) {
        printf("%d ", deque[i]);
        i = (i + 1) % N;
    }
    printf("%d\n", deque[r]);
}

void getFront() {
    if (f == -1) {
        printf("Deque is empty\n");
    } else {
        printf("Front element: %d\n", deque[f]);
    }
}

void getRear() {
    if (r == -1) {
        printf("Deque is empty\n");
    } else {
        printf("Rear element: %d\n", deque[r]);
    }
}

void dequeueFront() {
    if (f == -1 && r == -1) {
        printf("Deque is empty\n");
    } 
    else if (f == r) {
        printf("Dequeued from front: %d\n", deque[f]);
        f = r = -1;
    } 
    else if (f == N - 1) {
        printf("Dequeued from front: %d\n", deque[f]);
        f = 0;
    } 
    else {
        printf("Dequeued from front: %d\n", deque[f]);
        f++;
    }
}

void dequeueRear() {
    if (f == -1 && r == -1) {
        printf("Deque is empty\n");
    } 
    else if (f == r) {
        printf("Dequeued from rear: %d\n", deque[r]);
        f = r = -1;
    } 
    else if (r == 0) {
        printf("Dequeued from rear: %d\n", deque[r]);
        r = N - 1;
    } 
    else {
        printf("Dequeued from rear: %d\n", deque[r]);
        r--;
    }
}

int main() {
    int choice, x;

    while (1) {
        printf("\nDeque Menu:\n");
        printf("1. Enqueue Front\n");
        printf("2. Enqueue Rear\n");
        printf("3. Dequeue Front\n");
        printf("4. Dequeue Rear\n");
        printf("5. Display\n");
        printf("6. Get Front\n");
        printf("7. Get Rear\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue at front: ");
                scanf("%d", &x);
                enqueueFront(x);
                break;
            case 2:
                printf("Enter the element to enqueue at rear: ");
                scanf("%d", &x);
                enqueueRear(x);
                break;
            case 3:
                dequeueFront();
                break;
            case 4:
                dequeueRear();
                break;
            case 5:
                display();
                break;
            case 6:
                getFront();
                break;
            case 7:
                getRear();
                break;
            case 8:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
