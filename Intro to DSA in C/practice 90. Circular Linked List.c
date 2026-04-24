#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
} *head = NULL, *tail = NULL;

// Function to create Circular Linked List
void createCLL() {
    struct node *newnode;
    int choice = 1;
    
    while (choice) {
        newnode = (struct node *)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newnode->data);
        newnode->next = NULL;

        if (head == NULL) {
            head = tail = newnode;
            tail->next = head;  // Circular linkage
        } else {
            tail->next = newnode;
            tail = newnode;
            tail->next = head;  // Maintain circular linkage
        }

        printf("Do you want to add another node? (0/1): ");
        scanf("%d", &choice);
    }
}

// Insert node at the beginning of the list
void insert_at_beg() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);

    if (tail == NULL) {
        // List is empty, so newnode is both head and tail
        head = tail = newnode;
        tail->next = head;  // Circular linkage
    } else {
        newnode->next = head;  // New node points to the current head
        head = newnode;        // Head is updated
        tail->next = head;     // Tail still points to the new head (maintain circular)
    }
}

// Insert node at the end of the list
void insert_at_end() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);

    if (tail == NULL) {
        // List is empty, so newnode is both head and tail
        head = tail = newnode;
        tail->next = head;  // Circular linkage
    } else {
        newnode->next = head;  // New node points to the head (circular)
        tail->next = newnode;  // Current tail points to new node
        tail = newnode;        // Update tail to the new node
    }
}

// Function to calculate the length of the circular linked list
int getlength() {
    int count = 0;
    struct node *temp = head;

    if (head == NULL) {
        return 0;  // Empty list
    }

    do {
        count++;
        temp = temp->next;
    } while (temp != head);  // Traverse until we circle back to head

    return count;
}

// Insert node at a specific position
void insert_at_pos() {
    struct node *newnode, *temp;
    int pos, i = 1, l;
    
    printf("Enter position: ");
    scanf("%d", &pos);
    
    l = getlength();
    if (pos < 1 || pos > l + 1) {
        printf("Invalid position\n");
        return;
    } else if (pos == 1) {
        insert_at_beg();
    } else if (pos == l + 1) {
        insert_at_end();
    } else {
        newnode = (struct node *)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newnode->data);
        
        temp = head;
        while (i < pos - 1) {
            temp = temp->next;
            i++;
        }
        // Insert new node between temp and temp->next
        newnode->next = temp->next;
        temp->next = newnode;
    }
}

// Delete node from the beginning
void del_from_beg() {
    struct node *temp;
    temp = head;
    
    if (head == NULL) {
        printf("List is empty.\n");
    } else if (head->next == head) {
        // Only one node in the list
        head = tail = NULL;
        free(temp);
    } else {
        head = head->next;
        tail->next = head;  // Maintain circular linkage
        free(temp);
    }
}

// Delete node from the end
void del_from_end() {
    struct node *current, *prev;
    current = head;

    if (tail == NULL) {
        printf("List is empty.\n");
    } else if (head == tail) {
        // Only one node in the list
        free(head);
        head = tail = NULL;
    } else {
        while (current->next != head) {
            prev = current;
            current = current->next;
        }
        prev->next = head;
        tail = prev;
        free(current);
    }
}

// Delete node from a specific position
void del_from_pos() {
    struct node *current, *nextnode;
    int pos, i = 1, l;
    
    printf("Enter position: ");
    scanf("%d", &pos);
    
    l = getlength();
    if (pos < 1 || pos > l) {
        printf("Invalid position\n");
        return;
    } else if (pos == 1) {
        del_from_beg();
    } else {
        current = head;
        while (i < pos - 1) {
            current = current->next;
            i++;
        }
        nextnode = current->next;
        current->next = nextnode->next;
        if (nextnode == tail) {
            tail = current;
        }
        free(nextnode);
    }
}

// Reverse the circular linked list
void reverse() {
    struct node *prev, *current, *nextnode;
    current = head;
    prev = NULL;
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }
    do {
        nextnode = current->next;
        current->next = prev;
        prev = current;
        current = nextnode;
    } while (current != head);

    head->next = prev;
    tail = head;
    head = prev;
}

// Display the circular linked list
void displayCLL() {
    struct node *temp;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);  // Traverse until we circle back to head

    printf("(head)\n");
}

// Main function with switch case
int main() {
    int choice;

    do {
        printf("\nCircular Linked List Operations:\n");
        printf("1. Create Circular Linked List\n");
        printf("2. Insert at Beginning\n");
        printf("3. Insert at End\n");
        printf("4. Insert at Position\n");
        printf("5. Delete from Beginning\n");
        printf("6. Delete from End\n");
        printf("7. Delete from Position\n");
        printf("8. Reverse List\n");
        printf("9. Display List\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createCLL();
                break;
            case 2:
                insert_at_beg();
                break;
            case 3:
                insert_at_end();
                break;
            case 4:
                insert_at_pos();
                break;
            case 5:
                del_from_beg();
                break;
            case 6:
                del_from_end();
                break;
            case 7:
                del_from_pos();
                break;
            case 8:
                reverse();
                break;
            case 9:
                displayCLL();
                break;
            case 10:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 10);

    return 0;
}
