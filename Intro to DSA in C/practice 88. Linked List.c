#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};


struct node *head = NULL;
struct node *temp;

// Function to insert a node at the beginning
void insert_at_beginning(int value) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newnode->data = value;
    newnode->next = head; // Point new node to the current head
    head = newnode;       // Update head to new node
}

// Function to insert a node at the end
void insert_at_end(int value) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newnode->data = value;
    newnode->next = NULL;

    if (head == NULL) {
        head = newnode; // If list is empty, make new node the head
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode; // Add new node at the end
    }
}

// Function to insert a node at a specific position
void insert_at_position(int value, int pos) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newnode->data = value;

    if (pos == 1) {
        newnode->next = head; // Insert at beginning
        head = newnode;
    } else {
        temp = head;
        int i;
        for (i = 1; i < pos - 1 && temp != NULL; i++) {
            temp = temp->next; // Traverse to the position
        }
        if (temp == NULL) {
            printf("Invalid position.\n");
            free(newnode); // Free memory if position is invalid
        } else {
            newnode->next = temp->next; // Insert new node
            temp->next = newnode;
        }
    }
}

void delete_from_beg() {
    if (head == NULL) {
        printf("List is empty.\n");
    } else {
        temp = head;
        head = head->next;
        printf("Deleted: %d\n", temp->data);
        free(temp);
    }
}

void delete_from_end() {
    struct node *prevnode;
    if (head == NULL) {
        printf("List is empty.\n");
    } else if (head->next == NULL) {
        printf("Deleted: %d\n", head->data);
        free(head);
        head = NULL;
    } else {
        temp = head;
        while (temp->next != NULL) {
            prevnode = temp;
            temp = temp->next;
        }
        prevnode->next = NULL;
        printf("Deleted: %d\n", temp->data);
        free(temp);
    }
}

void delete_from_pos() {
    struct node *nextnode;
    int pos, i = 1;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos == 1) {
        delete_from_beg();
    } else {
        temp = head;
        while (i < pos - 1 && temp != NULL) {
            temp = temp->next;
            i++;
        }

        if (temp == NULL || temp->next == NULL) {
            printf("Invalid position.\n");
        } else {
            nextnode = temp->next;
            temp->next = nextnode->next;
            printf("Deleted: %d\n", nextnode->data);
            free(nextnode);
        }
    }
}

void display() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    temp = head;
    printf("Linked list: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}



void getlength() {
    int count = 0;
    temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Length is %d\n", count);
}

void reverse() {
    struct node *prevnode = NULL, *currentnode = head, *nextnode;
    while (currentnode != NULL) {
        nextnode = currentnode->next;
        currentnode->next = prevnode;
        prevnode = currentnode;
        currentnode = nextnode;
    }
    head = prevnode;
}

int main() {
    int choice, value, option;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete from beginning\n");
        printf("3. Delete from end\n");
        printf("4. Delete from a position\n");
        printf("5. Display\n");
        printf("6. Get length\n");
        printf("7. Reverse\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                delete_from_beg();
                break;
            case 3:
                delete_from_end();
                break;
            case 4:
                delete_from_pos();
                break;
            case 5:
                display();
                break;
            case 6:
                getlength();
                break;
            case 7:
                reverse();
                display();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
