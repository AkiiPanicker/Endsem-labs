#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the polynomial
struct PolyNode {
    int coeff;           // Coefficient of the term
    int exp;            // Exponent of the term
    struct PolyNode* next; // Pointer to the next node
};

// Function to create a new polynomial node
struct PolyNode* createNode(int coeff, int exp) {
    struct PolyNode* newNode = (struct PolyNode*)malloc(sizeof(struct PolyNode));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode; // Pointing to itself for circular behavior
    return newNode;
}

// Function to insert a term into the polynomial
void insertTerm(struct PolyNode** header, int coeff, int exp) {
    struct PolyNode* newNode = createNode(coeff, exp);
    if (*header == NULL) {
        *header = newNode; // If header is NULL, initialize it
        return;
    }

    struct PolyNode* temp = *header;
    // Insert the new term in sorted order (by exponent)
    while (temp->next != *header && temp->next->exp > exp) {
        temp = temp->next;
    }
    
    // If the exponent already exists, add the coefficient
    if (temp->next != *header && temp->next->exp == exp) {
        temp->next->coeff += coeff;
        free(newNode); // Free the newly created node
        return;
    }

    // Insertion
    newNode->next = temp->next; // Link to the next node
    temp->next = newNode; // Link the previous node to the new node

    // If inserted at the end, make it circular
    if (newNode->next == *header) {
        struct PolyNode* end = *header;
        while (end->next != *header) {
            end = end->next;
        }
        end->next = newNode;
    }
}

// Function to display the polynomial
void displayPolynomial(struct PolyNode* header) {
    if (header == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }
    struct PolyNode* temp = header;
    do {
        printf("%dx^%d ", temp->coeff, temp->exp);
        temp = temp->next;
    } while (temp != header);
    printf("\n");
}

// Function to subtract two polynomials
struct PolyNode* subtractPolynomials(struct PolyNode* p1, struct PolyNode* p2) {
    struct PolyNode* result = NULL;
    struct PolyNode* temp1 = p1;
    struct PolyNode* temp2 = p2;

    do {
        int coeff = temp1->coeff;
        int exp = temp1->exp;

        // Traverse p2 to find a matching exponent
        while (temp2 != p2 || temp2->exp != exp) {
            if (temp2->exp == exp) {
                coeff -= temp2->coeff; // Subtract coefficient
                break;
            }
            temp2 = temp2->next;
        }
        
        // Insert the resulting term into the result polynomial
        insertTerm(&result, coeff, exp);
        temp1 = temp1->next;
        temp2 = p2; // Reset temp2 for next term of p1
    } while (temp1 != p1);

    return result;
}

// Function to multiply two polynomials
struct PolyNode* multiplyPolynomials(struct PolyNode* p1, struct PolyNode* p2) {
    struct PolyNode* result = NULL;
    struct PolyNode* temp1 = p1;
    struct PolyNode* temp2 = p2;

    do {
        do {
            int coeff = temp1->coeff * temp2->coeff;
            int exp = temp1->exp + temp2->exp;

            // Insert the resulting term into the result polynomial
            insertTerm(&result, coeff, exp);
            temp2 = temp2->next;
        } while (temp2 != p2);
        
        temp1 = temp1->next; // Move to the next term in p1
        temp2 = p2; // Reset temp2 for the next term of p1
    } while (temp1 != p1);

    return result;
}

// Main function to drive the program
int main() {
    struct PolyNode* poly1 = NULL; // Header for polynomial 1
    struct PolyNode* poly2 = NULL; // Header for polynomial 2
    struct PolyNode* result = NULL; // Header for result

    int choice, coeff, exp;

    do {
        printf("\nMenu:\n");
        printf("1. Input first polynomial\n");
        printf("2. Input second polynomial\n");
        printf("3. Subtract polynomials\n");
        printf("4. Multiply polynomials\n");
        printf("5. Display polynomials\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Input terms for the first polynomial (coeff exp, enter -1 for coeff to stop):\n");
                while (1) {
                    scanf("%d", &coeff);
                    if (coeff == -1) break;
                    scanf("%d", &exp);
                    insertTerm(&poly1, coeff, exp);
                }
                break;
            case 2:
                printf("Input terms for the second polynomial (coeff exp, enter -1 for coeff to stop):\n");
                while (1) {
                    scanf("%d", &coeff);
                    if (coeff == -1) break;
                    scanf("%d", &exp);
                    insertTerm(&poly2, coeff, exp);
                }
                break;
            case 3:
                result = subtractPolynomials(poly1, poly2);
                printf("Subtracted Polynomial: ");
                displayPolynomial(result);
                break;
            case 4:
                result = multiplyPolynomials(poly1, poly2);
                printf("Multiplied Polynomial: ");
                displayPolynomial(result);
                break;
            case 5:
                printf("First Polynomial: ");
                displayPolynomial(poly1);
                printf("Second Polynomial: ");
                displayPolynomial(poly2);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    // Free allocated memory (not shown in this code for simplicity)

    return 0;
}
