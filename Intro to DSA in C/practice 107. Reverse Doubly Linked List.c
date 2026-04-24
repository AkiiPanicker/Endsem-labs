#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the node in the doubly linked list
struct Node {
    char data[100]; // Array to hold the word
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(const char* word) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, word); // Copy the word into the node
    newNode->next = NULL; // Initialize next pointer
    newNode->prev = NULL; // Initialize prev pointer
    return newNode;
}

// Function to insert a word at the end of the list
void insertEnd(struct Node** head, const char* word) {
    struct Node* newNode = createNode(word);
    if (*head == NULL) {
        *head = newNode; // If the list is empty, new node is the head
        return;
    }
    
    struct Node* last = *head;
    while (last->next != NULL) {
        last = last->next; // Traverse to the last node
    }
    
    last->next = newNode; // Link the last node to the new node
    newNode->prev = last; // Link the new node back to the last node
}

// Function to reverse the doubly linked list
void reverseList(struct Node** head) {
    struct Node* temp = NULL;
    struct Node* current = *head;
    
    // Swap next and prev pointers for all nodes
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; // Move to the next node (which is the old prev)
    }
    
    // Update the head pointer
    if (temp != NULL) {
        *head = temp->prev; // New head will be the last processed node
    }
}

// Function to display the list
void displayList(struct Node* head) {
    struct Node* current = head;
    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List of words:\n");
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Main function to drive the program
int main() {
    struct Node* head = NULL; // Initialize the head of the list
    
    // Insert words into the doubly linked list
    insertEnd(&head, "Hello");
    insertEnd(&head, "World");
    insertEnd(&head, "This");
    insertEnd(&head, "Is");
    insertEnd(&head, "Doubly");
    insertEnd(&head, "Linked");
    insertEnd(&head, "List");
    
    printf("Original ");
    displayList(head); // Display the original list

    // Reverse the doubly linked list
    reverseList(&head);
    
    printf("Reversed ");
    displayList(head); // Display the reversed list

    return 0;
}
