#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a node for the singly linked list
struct Node {
    char data[100];
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(char* word) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, word);
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
struct Node* insertEnd(struct Node* head, char* word) {
    struct Node* newNode = createNode(word);
    if (head == NULL) {
        return newNode;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Recursive function to reverse the list
struct Node* reverseList(struct Node* head) {
    // Base case: empty list or end of the list reached
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Recursively reverse the remaining list
    struct Node* newHead = reverseList(head->next);

    // Reverse the current node's link
    head->next->next = head;
    head->next = NULL;

    return newHead; // Return new head of the reversed list
}

// Function to display the list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%s -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    // Insert words into the linked list
    head = insertEnd(head, "Hello");
    head = insertEnd(head, "world");
    head = insertEnd(head, "this");
    head = insertEnd(head, "is");
    head = insertEnd(head, "ChatGPT");

    printf("Original List:\n");
    displayList(head);

    // Reverse the linked list
    head = reverseList(head);

    printf("\nReversed List:\n");
    displayList(head);

    return 0;
}
