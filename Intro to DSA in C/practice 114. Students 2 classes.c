#include <stdio.h>
#include <stdlib.h>

// Define the structure for the linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to insert element at the end of the list
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

// Function to display the list
void displayList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("->%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to merge two sorted linked lists into a single sorted list
Node* mergeLists(Node* headA, Node* headB) {
    Node* mergedHead = NULL;
    Node* mergedTail = NULL;

    // Merge the two lists
    while (headA != NULL && headB != NULL) {
        Node* newNode;
        if (headA->data < headB->data) {
            newNode = headA;
            headA = headA->next;
        } else {
            newNode = headB;
            headB = headB->next;
        }

        if (mergedHead == NULL) {
            mergedHead = newNode;
            mergedTail = newNode;
        } else {
            mergedTail->next = newNode;
            mergedTail = mergedTail->next;
        }
    }

    // Append remaining elements
    if (headA != NULL) {
        mergedTail->next = headA;
    }
    if (headB != NULL) {
        mergedTail->next = headB;
    }

    return mergedHead;
}

int main() {
    int n1, n2, data;

    // Input the number of students in each class
    printf("Enter the number of students in class A and class B: ");
    scanf("%d %d", &n1, &n2);

    Node* classA = NULL;
    Node* classB = NULL;

    // Input heights of students in Class A
    printf("Enter the heights of students in class A in ascending order: ");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &data);
        insertEnd(&classA, data);
    }

    // Input heights of students in Class B
    printf("Enter the heights of students in class B in ascending order: ");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &data);
        insertEnd(&classB, data);
    }

    // Display the original lists
    printf("Class A\n");
    displayList(classA);
    printf("Class B\n");
    displayList(classB);

    // Merge the lists
    Node* mergedClass = mergeLists(classA, classB);

    // Display the merged list
    printf("Joint Class\n");
    displayList(mergedClass);

    return 0;
}
