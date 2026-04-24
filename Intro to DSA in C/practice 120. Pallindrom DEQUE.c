#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    char data[MAX];
    int front;
    int rear;
} Deque;

// Initialize the deque
void initDeque(Deque *dq) {
    dq->front = -1;
    dq->rear = -1;
}

// Check if deque is empty
bool isEmpty(Deque *dq) {
    return (dq->front == -1);
}

// Check if deque is full
bool isFull(Deque *dq) {
    return ((dq->rear + 1) % MAX == dq->front);
}

// Insert an element at the rear
void insertRear(Deque *dq, char ch) {
    if (isFull(dq)) {
        printf("Deque is full!\n");
        return;
    }
    if (isEmpty(dq)) {
        dq->front = dq->rear = 0;
    } else {
        dq->rear = (dq->rear + 1) % MAX;
    }
    dq->data[dq->rear] = ch;
}

// Remove an element from the front
char deleteFront(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return '\0';
    }
    char ch = dq->data[dq->front];
    if (dq->front == dq->rear) { // Single element
        dq->front = dq->rear = -1;
    } else {
        dq->front = (dq->front + 1) % MAX;
    }
    return ch;
}

// Remove an element from the rear
char deleteRear(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return '\0';
    }
    char ch = dq->data[dq->rear];
    if (dq->front == dq->rear) { // Single element
        dq->front = dq->rear = -1;
    } else {
        dq->rear = (dq->rear - 1 + MAX) % MAX;
    }
    return ch;
}

// Function to check if a string is a palindrome
bool isPalindrome(char *str) {
    Deque dq;
    initDeque(&dq);
    int len = strlen(str);

    // Insert all characters of the string into the deque
    for (int i = 0; i < len; i++) {
        insertRear(&dq, str[i]);
    }

    // Check characters from both ends
    while (!isEmpty(&dq)) {
        char frontChar = deleteFront(&dq);
        if (!isEmpty(&dq)) {
            char rearChar = deleteRear(&dq);
            if (frontChar != rearChar) {
                return false; // Not a palindrome
            }
        }
    }
    return true; // Palindrome
}

int main() {
    char str[MAX];

    printf("Enter a string: ");
    scanf("%s", str);

    if (isPalindrome(str)) {
        printf("The string \"%s\" is a palindrome.\n", str);
    } else {
        printf("The string \"%s\" is not a palindrome.\n", str);
    }

    return 0;
}
