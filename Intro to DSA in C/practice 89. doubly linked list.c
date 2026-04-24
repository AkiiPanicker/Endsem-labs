#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL, *tail = NULL;

void create() {
    struct node *newnode;
    int choice = 1;
    
    while (choice) {
        newnode = (struct node *)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newnode->data);
        newnode->prev = NULL;
        newnode->next = NULL;
        
        if (head == NULL) {
            head = tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        
        printf("Do you want to continue? (0/1): ");
        scanf("%d", &choice);
    }
}

void insert_at_beg() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);
    newnode->prev = NULL;
    newnode->next = head;

    if (head != NULL) {
        head->prev = newnode;
    } else {
        tail = newnode; 
    }
    
    head = newnode;
}

void insert_at_end() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);
    newnode->next = NULL;
    newnode->prev = tail;

    if (tail != NULL) {
        tail->next = newnode;
    } else {
        head = newnode; 
    }
    
    tail = newnode;
}

void insert_at_pos() {
    int pos;
    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos == 1) {
        insert_at_beg();
        return;
    }

    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);

    struct node *temp = head;
    int i = 1;

    while (i < pos - 1 && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Position out of bounds.\n");
        free(newnode);
        return;
    }

    newnode->next = temp->next;
    newnode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newnode;
    }

    temp->next = newnode;

    if (newnode->next == NULL) {
        tail = newnode;
    }
}

void insert_after_pos() {
    int pos;
    printf("Enter position: ");
    scanf("%d", &pos);

    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);

    struct node *temp = head;
    int i = 1;

    while (i < pos && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Position out of bounds.\n");
        free(newnode);
        return;
    }

    newnode->next = temp->next;
    newnode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newnode;
    }

    temp->next = newnode;

    if (newnode->next == NULL) {
        tail = newnode;
    }
}

void delete_from_beg() {
    struct node *temp;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    temp = head;
    head = head->next;

    if (head != NULL) {
        head->prev = NULL;
    } else {
        tail = NULL; // If the list becomes empty
    }

    free(temp);
}

void delete_from_end() {
    struct node *temp;

    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    temp = tail;
    tail = tail->prev;

    if (tail != NULL) {
        tail->next = NULL;
    } else {
        head = NULL; // If the list becomes empty
    }

    free(temp);
}

void delete_from_pos() {
    int pos, i = 1;
    struct node *temp = head;

    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos == 1) {
        delete_from_beg();
        return;
    }

    while (i < pos && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Position out of bounds.\n");
        return;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }

    if (temp == tail) {
        tail = temp->prev;
    }

    free(temp);
}

void reverse() {
    struct node *current, *nextnode;
    current = head;
    while (current != NULL) {
        nextnode = current->next;
        current->next = current->prev;
        current->prev = nextnode;
        current = nextnode;
    }
    current = head;
    head = tail;
    tail = current;
}

void display() {
    struct node *temp = head;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Create list\n");
        printf("2. Display list\n");
        printf("3. Insert at beginning\n");
        printf("4. Insert at end\n");
        printf("5. Insert at specific position\n");
        printf("6. Insert after specific position\n");
        printf("7. Delete from beginning\n");
        printf("8. Delete from end\n");
        printf("9. Delete from specific position\n");
        printf("10. Reverse list\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                insert_at_beg();
                break;
            case 4:
                insert_at_end();
                break;
            case 5:
                insert_at_pos();
                break;
            case 6:
                insert_after_pos();
                break;
            case 7:
                delete_from_beg();
                break;
            case 8:
                delete_from_end();
                break;
            case 9:
                delete_from_pos();
                break;
            case 10:
                reverse();
                break;
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 11);

    return 0;
}
