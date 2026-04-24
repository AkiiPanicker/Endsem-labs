#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
} *head = NULL, *tail = NULL;

// Function to create a doubly circular linked list
void createDCLL() {
    struct node *newnode;
    head = NULL;  // Initialize head to NULL
    int choice = 1;
    while (choice) {
        newnode = (struct node *)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newnode->data);
        if (head == NULL) {
            head = tail = newnode;
            head->next = head;
            head->prev = head;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            newnode->next = head;
            head->prev = newnode;
            tail = newnode;
        }
        printf("Do you want to continue? (1/0): ");
        scanf("%d", &choice);
    }
}

// Function to insert a node at the beginning
void insert_at_beg() {
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);
    if (head == NULL) {
        head = tail = newnode;
        newnode->next = head;
        newnode->prev = head;
    } else {
        newnode->next = head;
        newnode->prev = tail;
        tail->next = newnode;
        head->prev = newnode;
        head = newnode;
    }
}

// Function to insert a node at the end
void insert_at_end() {
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);
    if (head == NULL) {
        head = tail = newnode;
        newnode->next = head;
        newnode->prev = head;
    } else {
        newnode->prev = tail;
        tail->next = newnode;
        newnode->next = head;
        head->prev = newnode;
        tail = newnode;
    }
}

// Function to get the length of the list
int getlength() {
    struct node *temp = head;
    int count = 0;
    if (head != NULL) {
        do {
            count++;
            temp = temp->next;
        } while (temp != head);
    }
    return count;
}

// Function to insert a node at a specified position
void insert_at_pos() {
    struct node *newnode, *temp;
    int pos, i = 1, l;
    printf("Enter position: ");
    scanf("%d", &pos);
    l = getlength();
    if (pos < 1 || pos > l + 1) { // Allow insert at end (l + 1)
        printf("Invalid position\n");
    } else if (pos == 1) {
        insert_at_beg();
    } else {
        newnode = (struct node *)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newnode->data);
        temp = head;
        while (i < pos - 1) {
            temp = temp->next;
            i++;
        }
        newnode->prev = temp;
        newnode->next = temp->next;
        temp->next->prev = newnode;
        temp->next = newnode;
    }
}

// Function to delete a node from the beginning
void del_from_beg() {
    if (head == NULL) {
        printf("List is empty, cannot delete.\n");
        return;
    }
    struct node *temp = head;
    if (head->next == head) { // Only one node
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }
    free(temp);
    printf("Node deleted from beginning.\n");
}

// Function to delete a node from the end
void del_from_end() {
    if (head == NULL) {
        printf("List is empty, cannot delete.\n");
        return;
    }
    struct node *temp = tail;
    if (head->next == head) { // Only one node
        head = tail = NULL;
    } else {
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
    }
    free(temp);
    printf("Node deleted from end.\n");
}

// Function to delete a node from a specified position
void del_from_pos() {
    struct node *temp;
    int pos, i = 1, l;
    temp = head;
    printf("Enter position: ");
    scanf("%d", &pos);
    l = getlength();
    if (pos < 1 || pos > l) {
        printf("Invalid Position\n");
        return;
    }
    if (pos == 1) {
        del_from_beg();
        return;
    }
    while (i < pos) {
        temp = temp->next;
        i++;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    if (temp == tail) { // If deleting the tail
        tail = temp->prev;
    }
    free(temp);
    printf("Node deleted from position %d.\n", pos);
}

// Function to display the list
void display() {
    struct node *temp = head;
    if (head == NULL) {
        printf("List is empty\n");
    } else {
        do {
            printf("%d ", temp->data);
            temp = temp->next;
        } while (temp != head);
        printf("\n");
    }
}

// Main function
int main() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Create DCLL\n");
        printf("2. Insert at Beginning\n");
        printf("3. Insert at End\n");
        printf("4. Insert at Position\n");
        printf("5. Delete from Beginning\n");
        printf("6. Delete from End\n");
        printf("7. Delete from Position\n");
        printf("8. Display\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createDCLL(); break;
            case 2: insert_at_beg(); break;
            case 3: insert_at_end(); break;
            case 4: insert_at_pos(); break;
            case 5: del_from_beg(); break;
            case 6: del_from_end(); break;
            case 7: del_from_pos(); break;
            case 8: display(); break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 9);
    
    return 0;
}
