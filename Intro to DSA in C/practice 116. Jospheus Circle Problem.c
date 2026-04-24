#include <stdio.h>
#include <stdlib.h>

// Define a node for the circular linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = newNode;  // Point to itself (circular link)
    return newNode;
}

// Function to append a node to the circular linked list
struct Node* appendNode(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }

    struct Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

// Function to find the position that survives
int josephusCircle(int n, int m) {
    // Create the circular linked list with n nodes
    struct Node* head = NULL;
    for (int i = 1; i <= n; i++) {
        head = appendNode(head, i);
    }

    // Find the last remaining person in the circle
    struct Node* current = head;
    struct Node* previous = NULL;

    // Traverse until only one node is left
    while (current->next != current) {
        // Skip m-1 nodes
        for (int count = 1; count < m; count++) {
            previous = current;
            current = current->next;
        }

        // Remove the m-th node
        printf("Person at position %d is executed.\n", current->data);
        previous->next = current->next;
        free(current);
        current = previous->next;
    }

    int survivor = current->data;
    free(current);
    return survivor;
}

int main() {
    int n, m;
    printf("Enter the total number of people (n): ");
    scanf("%d", &n);
    printf("Enter the number of people to skip (m): ");
    scanf("%d", &m);

    int survivor = josephusCircle(n, m);
    printf("The position to stand to be the last survivor is: %d\n", survivor);

    return 0;
}
