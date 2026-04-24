#include <stdio.h>
#include <stdlib.h>

// Define the structure for the linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a node at the end of the list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to delete duplicates in a sorted linked list
void removeDuplicates(struct Node* head) {
    struct Node* current = head;

    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            // Duplicate found, remove the next node
            struct Node* duplicate = current->next;
            current->next = current->next->next;
            free(duplicate);
        } else {
            // Move to the next node if no duplicate
            current = current->next;
        }
    }
}

// Function to display the list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to test the above code
int main() {
    struct Node* head = NULL;

    // Insert elements in the linked list
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertEnd(&head, 4);
    insertEnd(&head, 4);
    insertEnd(&head, 5);

    printf("Original list:\n");
    displayList(head);

    // Remove duplicates
    removeDuplicates(head);

    printf("List after removing duplicates:\n");
    displayList(head);

    return 0;
}
