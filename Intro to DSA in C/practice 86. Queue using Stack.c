#include <stdio.h>
#include <stdlib.h>
#define N 5

int S1[N], S2[N];
int top1 = -1, top2 = -1;
int count = 0;

void push1(int data) {
    if (top1 == N - 1) {
        printf("Stack 1 is Full\n");
    } else {
        top1++;
        S1[top1] = data;
    }
}

void push2(int data) {
    if (top2 == N - 1) {
        printf("Stack 2 is Full\n");
    } else {
        top2++;
        S2[top2] = data;
    }
}

int pop1() {
    if (top1 == -1) {
        printf("Stack 1 is Empty\n");
        return -1;
    } else {
        return S1[top1--];
    }
}

int pop2() {
    if (top2 == -1) {
        printf("Stack 2 is Empty\n");
        return -1;
    } else {
        return S2[top2--];
    }
}

void enqueue(int x) {
    push1(x);
    count++;
}

void dequeue() {
    if (top1 == -1 && top2 == -1) {
        printf("Queue is empty\n");
    } else {
        // Transfer elements from S1 to S2
        for (int i = 0; i < count; i++) {
            int a = pop1();
            push2(a);
        }

        // Dequeue the front element
        int b = pop2();
        printf("Dequeued: %d\n", b);
        count--;

        // Transfer elements back to S1 from S2
        for (int i = 0; i < count; i++) {
            int a = pop2();
            push1(a);
        }
    }
}

void display() {
    if (top1 == -1) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements: ");
        for (int i = 0; i <= top1; i++) {
            printf("%d ", S1[i]);
        }
        printf("\n");
    }
}

int main() {
    int choice, x;

    while (1) {
        printf("\nQueue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &x);
                enqueue(x);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
