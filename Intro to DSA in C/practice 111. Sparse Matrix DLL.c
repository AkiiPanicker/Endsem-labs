#include <stdio.h>
#include <stdlib.h>

// Node structure for each non-zero element
struct Node {
    int row;
    int col;
    int value;
    struct Node *next;
    struct Node *prev;
};

// Function to create a new node
struct Node* createNode(int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertNode(struct Node** head, int row, int col, int value) {
    struct Node* newNode = createNode(row, col, value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to display the sparse matrix representation
void displaySparseMatrix(struct Node* head) {
    struct Node* temp = head;
    printf("Row\tColumn\tValue\n");
    while (temp != NULL) {
        printf("%d\t%d\t%d\n", temp->row, temp->col, temp->value);
        temp = temp->next;
    }
}

// Function to take sparse matrix input and store non-zero elements in the doubly linked list
void createSparseMatrix(struct Node** head, int rows, int cols) {
    int value;
    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element at (%d, %d): ", i, j);
            scanf("%d", &value);
            if (value != 0) {
                insertNode(head, i, j, value);
            }
        }
    }
}

int main() {
    struct Node* sparseMatrix = NULL;
    int rows, cols;

    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &rows, &cols);

    createSparseMatrix(&sparseMatrix, rows, cols);

    printf("\nSparse Matrix Representation (Only non-zero elements):\n");
    displaySparseMatrix(sparseMatrix);

    return 0;
}
