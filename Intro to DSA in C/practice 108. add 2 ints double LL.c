#include <stdio.h>
#include <stdlib.h>

// Define the structure for the node in the circular doubly linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Define the structure for the circular doubly linked list with a header node
struct CircularDoublyLinkedList {
    struct Node* header;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = newNode; // Point to itself initially
    newNode->prev = newNode; // Point to itself initially
    return newNode;
}

// Function to initialize a circular doubly linked list
struct CircularDoublyLinkedList* createList() {
    struct CircularDoublyLinkedList* list = (struct CircularDoublyLinkedList*)malloc(sizeof(struct CircularDoublyLinkedList));
    list->header = createNode(0); // Header node
    list->header->next = list->header; // Circular link
    list->header->prev = list->header; // Circular link
    return list;
}

// Function to insert a digit at the end of the list
void insertEnd(struct CircularDoublyLinkedList* list, int data) {
    struct Node* newNode = createNode(data);
    struct Node* last = list->header->prev;

    last->next = newNode;
    newNode->prev = last;
    newNode->next = list->header;
    list->header->prev = newNode;
}

// Function to display the list
void displayList(struct CircularDoublyLinkedList* list) {
    struct Node* current = list->header->next;
    if (current == list->header) {
        printf("List is empty.\n");
        return;
    }
    printf("Number: ");
    while (current != list->header) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to add two numbers represented by circular doubly linked lists
struct CircularDoublyLinkedList* addLists(struct CircularDoublyLinkedList* list1, struct CircularDoublyLinkedList* list2) {
    struct CircularDoublyLinkedList* result = createList();
    struct Node* p1 = list1->header->prev; // Start from the last node
    struct Node* p2 = list2->header->prev; // Start from the last node
    int carry = 0;

    // Loop until both lists are exhausted and no carry remains
    while (p1 != list1->header || p2 != list2->header || carry) {
        int sum = carry; // Start with carry

        // Add from list1 if not exhausted
        if (p1 != list1->header) {
            sum += p1->data;
            p1 = p1->prev; // Move to the previous node
        }

        // Add from list2 if not exhausted
        if (p2 != list2->header) {
            sum += p2->data;
            p2 = p2->prev; // Move to the previous node
        }

        // Calculate new carry and the digit to insert
        carry = sum / 10;
        insertEnd(result, sum % 10); // Insert the digit at the end of the result list
    }

    return result;
}

// Main function to drive the program
int main() {
    struct CircularDoublyLinkedList* num1 = createList();
    struct CircularDoublyLinkedList* num2 = createList();
    
    // Example inputs for the first number
    insertEnd(num1, 3); // Represents the number 3
    insertEnd(num1, 4); // Represents the number 34
    insertEnd(num1, 2); // Represents the number 234
    
    // Example inputs for the second number
    insertEnd(num2, 4); // Represents the number 4
    insertEnd(num2, 6); // Represents the number 46
    insertEnd(num2, 5); // Represents the number 546

    printf("First Number: ");
    displayList(num1);
    printf("Second Number: ");
    displayList(num2);

    struct CircularDoublyLinkedList* sumList = addLists(num1, num2);
    
    printf("Sum: ");
    displayList(sumList);

    return 0;
}
