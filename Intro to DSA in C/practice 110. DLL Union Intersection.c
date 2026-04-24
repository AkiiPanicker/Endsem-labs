#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node with given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node into a sorted doubly linked list without duplicates
void insertSorted(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* current = *head;

    // If new node needs to be placed at the start
    if (current->data > data) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
        return;
    }

    // Traverse to find the correct position to insert
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }

    // Check for duplicates
    if (current->data == data || (current->next != NULL && current->next->data == data)) {
        free(newNode); // Free newNode if data already exists
        return;
    }

    // Insert newNode after current
    newNode->next = current->next;
    if (current->next != NULL) {
        newNode->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}

// Function to display a doubly linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to perform union of two doubly linked lists
struct Node* unionLists(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL;

    // Insert all unique elements from the first list
    struct Node* temp = head1;
    while (temp != NULL) {
        insertSorted(&result, temp->data);
        temp = temp->next;
    }

    // Insert all unique elements from the second list
    temp = head2;
    while (temp != NULL) {
        insertSorted(&result, temp->data);
        temp = temp->next;
    }

    return result;
}

// Function to perform intersection of two doubly linked lists
struct Node* intersectionLists(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL;
    struct Node* temp1 = head1;
    struct Node* temp2 = head2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data == temp2->data) {
            insertSorted(&result, temp1->data);
            temp1 = temp1->next;
            temp2 = temp2->next;
        } else if (temp1->data < temp2->data) {
            temp1 = temp1->next;
        } else {
            temp2 = temp2->next;
        }
    }

    return result;
}

// Main function with a menu-driven approach
int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    struct Node* result = NULL;
    int choice, data, n;

    do {
        printf("\nMenu:\n");
        printf("1. Insert into List 1\n");
        printf("2. Insert into List 2\n");
        printf("3. Display List 1\n");
        printf("4. Display List 2\n");
        printf("5. Union of Lists\n");
        printf("6. Intersection of Lists\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of elements to insert into List 1: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Enter element: ");
                    scanf("%d", &data);
                    insertSorted(&list1, data);
                }
                break;
            case 2:
                printf("Enter number of elements to insert into List 2: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Enter element: ");
                    scanf("%d", &data);
                    insertSorted(&list2, data);
                }
                break;
            case 3:
                printf("List 1: ");
                displayList(list1);
                break;
            case 4:
                printf("List 2: ");
                displayList(list2);
                break;
            case 5:
                result = unionLists(list1, list2);
                printf("Union of Lists: ");
                displayList(result);
                break;
            case 6:
                result = intersectionLists(list1, list2);
                printf("Intersection of Lists: ");
                displayList(result);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}
