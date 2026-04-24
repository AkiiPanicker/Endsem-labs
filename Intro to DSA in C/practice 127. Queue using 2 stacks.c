#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100 // Define maximum size for the stacks

// Stack structure
typedef struct {
    int top;
    int items[MAX];
} Stack;

// Queue structure
typedef struct {
    Stack stack1; // Input stack
    Stack stack2; // Output stack
} Queue;

// Function to initialize a stack
void initStack(Stack* s) {
    s->top = -1;
}

// Function to check if the stack is full
bool isFull(Stack* s) {
    return s->top == MAX - 1;
}

// Function to check if the stack is empty
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// Function to push an element onto the stack
void push(Stack* s, int item) {
    if (!isFull(s)) {
        s->items[++s->top] = item;
    } else {
        printf("Stack Overflow\n");
    }
}

// Function to pop an element from the stack
int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top--];
    } else {
        printf("Stack Underflow\n");
        return -1; // Indicate error
    }
}

// Function to get the top element of the stack
int peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    } else {
        printf("Stack is empty\n");
        return -1; // Indicate error
    }
}

// Function to initialize the queue
void initQueue(Queue* q) {
    initStack(&q->stack1);
    initStack(&q->stack2);
}

// Function to enqueue an element into the queue
void enqueue(Queue* q, int item) {
    push(&q->stack1, item);
}

// Function to dequeue an element from the queue
int dequeue(Queue* q) {
    // Move elements from stack1 to stack2 if stack2 is empty
    if (isEmpty(&q->stack2)) {
        while (!isEmpty(&q->stack1)) {
            push(&q->stack2, pop(&q->stack1));
        }
    }
    // If stack2 is still empty, the queue is empty
    if (!isEmpty(&q->stack2)) {
        return pop(&q->stack2);
    } else {
        printf("Queue is empty\n");
        return -1; // Indicate error
    }
}

// Function to display the contents of the queue
void displayQueue(Queue* q) {
    // Temporary stack to hold elements for display
    Stack temp;
    initStack(&temp);

    // Move elements from stack2 to temporary stack for display
    while (!isEmpty(&q->stack2)) {
        push(&temp, pop(&q->stack2));
    }

    // Display elements from temp stack (which is in correct order)
    while (!isEmpty(&temp)) {
        int item = pop(&temp);
        printf("%d ", item);
        push(&q->stack2, item); // Move back to stack2 to maintain state
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    // Example usage
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printf("Queue after enqueuing 10, 20, 30: ");
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Queue after dequeuing: ");
    displayQueue(&q);

    enqueue(&q, 40);
    printf("Queue after enqueuing 40: ");
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Queue after dequeuing: ");
    displayQueue(&q);

    return 0;
}
