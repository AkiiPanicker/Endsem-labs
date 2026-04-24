#include <stdio.h>
#include <stdlib.h>

// Define the structure for the linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Insert element at the end of the list
void insertEnd(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Display the elements of the list
void displayList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Check if an element is present in the list
int isPresent(Node* head, int data) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// Union of two lists with header node
Node* unionWithHeader(Node* head1, Node* head2) {
    Node* result = (Node*)malloc(sizeof(Node));
    result->next = NULL;
    Node* temp = result;

    Node* current = head1->next;  // Skip header node
    while (current != NULL) {
        insertEnd(&temp, current->data);
        current = current->next;
    }

    current = head2->next;  // Skip header node
    while (current != NULL) {
        if (!isPresent(result->next, current->data)) {
            insertEnd(&temp, current->data);
        }
        current = current->next;
    }
    return result;
}

// Union of two lists without header node
Node* unionWithoutHeader(Node* head1, Node* head2) {
    Node* result = NULL;
    Node* current = head1;
    while (current != NULL) {
        insertEnd(&result, current->data);
        current = current->next;
    }

    current = head2;
    while (current != NULL) {
        if (!isPresent(result, current->data)) {
            insertEnd(&result, current->data);
        }
        current = current->next;
    }
    return result;
}

// Intersection of two lists with header node
Node* intersectionWithHeader(Node* head1, Node* head2) {
    Node* result = (Node*)malloc(sizeof(Node));
    result->next = NULL;
    Node* temp = result;

    Node* current = head1->next;  // Skip header node
    while (current != NULL) {
        if (isPresent(head2->next, current->data)) {
            insertEnd(&temp, current->data);
        }
        current = current->next;
    }
    return result;
}

// Intersection of two lists without header node
Node* intersectionWithoutHeader(Node* head1, Node* head2) {
    Node* result = NULL;
    Node* current = head1;
    while (current != NULL) {
        if (isPresent(head2, current->data)) {
            insertEnd(&result, current->data);
        }
        current = current->next;
    }
    return result;
}

int main() {
    Node* head1WithHeader = (Node*)malloc(sizeof(Node));
    Node* head2WithHeader = (Node*)malloc(sizeof(Node));
    head1WithHeader->next = NULL;
    head2WithHeader->next = NULL;

    Node* head1WithoutHeader = NULL;
    Node* head2WithoutHeader = NULL;

    // Sample data for list with header node
    insertEnd(&head1WithHeader, 1);
    insertEnd(&head1WithHeader, 2);
    insertEnd(&head1WithHeader, 3);
    insertEnd(&head2WithHeader, 2);
    insertEnd(&head2WithHeader, 3);
    insertEnd(&head2WithHeader, 4);

    // Sample data for list without header node
    insertEnd(&head1WithoutHeader, 1);
    insertEnd(&head1WithoutHeader, 2);
    insertEnd(&head1WithoutHeader, 3);
    insertEnd(&head2WithoutHeader, 2);
    insertEnd(&head2WithoutHeader, 3);
    insertEnd(&head2WithoutHeader, 4);

    // Perform Union and Intersection with Header
    printf("Union with header node: ");
    Node* unionHeader = unionWithHeader(head1WithHeader, head2WithHeader);
    displayList(unionHeader->next);  // Skip header node for display

    printf("Intersection with header node: ");
    Node* intersectionHeader = intersectionWithHeader(head1WithHeader, head2WithHeader);
    displayList(intersectionHeader->next);  // Skip header node for display

    // Perform Union and Intersection without Header
    printf("Union without header node: ");
    Node* unionNoHeader = unionWithoutHeader(head1WithoutHeader, head2WithoutHeader);
    displayList(unionNoHeader);

    printf("Intersection without header node: ");
    Node* intersectionNoHeader = intersectionWithoutHeader(head1WithoutHeader, head2WithoutHeader);
    displayList(intersectionNoHeader);

    return 0;
}
