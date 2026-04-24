#include <stdio.h>
#include <stdlib.h>

struct node {
    float coefficient;
    int exponent;
    struct node *link;
};

struct node* createNode(float coeff, int exp) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->link = NULL;
    return newNode;
}

void insertNode(struct node **head, float coeff, int exp) {
    struct node *newNode = createNode(coeff, exp);
    if (*head == NULL || (*head)->exponent < exp) {
        newNode->link = *head;
        *head = newNode;
    } else {
        struct node *current = *head;
        while (current->link != NULL && current->link->exponent >= exp) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

void displayPolynomial(struct node *head) {
    struct node *temp = head;
    if (temp == NULL) {
        printf("0\n");
        return;
    }
    while (temp != NULL) {
        printf("%.1fx^%d", temp->coefficient, temp->exponent);
        temp = temp->link;
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

struct node* addPolynomials(struct node *poly1, struct node *poly2) {
    struct node *result = NULL;
    struct node *temp1 = poly1;
    struct node *temp2 = poly2;

    while (temp1 != NULL || temp2 != NULL) {
        if (temp1 == NULL) {
            insertNode(&result, temp2->coefficient, temp2->exponent);
            temp2 = temp2->link;
        } else if (temp2 == NULL) {
            insertNode(&result, temp1->coefficient, temp1->exponent);
            temp1 = temp1->link;
        } else if (temp1->exponent == temp2->exponent) {
            insertNode(&result, temp1->coefficient + temp2->coefficient, temp1->exponent);
            temp1 = temp1->link;
            temp2 = temp2->link;
        } else if (temp1->exponent > temp2->exponent) {
            insertNode(&result, temp1->coefficient, temp1->exponent);
            temp1 = temp1->link;
        } else {
            insertNode(&result, temp2->coefficient, temp2->exponent);
            temp2 = temp2->link;
        }
    }
    return result;
}

void freePolynomial(struct node *head) {
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->link;
        free(temp);
    }
}

int main() {
    struct node *poly1 = NULL;
    struct node *poly2 = NULL;
    struct node *result = NULL;

    int n1, n2;
    float coeff;
    int exp;

    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n1);
    printf("Enter the terms (coefficient exponent) of the first polynomial:\n");
    for (int i = 0; i < n1; i++) {
        printf("Term %d: ", i + 1);
        scanf("%f %d", &coeff, &exp);
        insertNode(&poly1, coeff, exp);
    }

    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n2);
    printf("Enter the terms (coefficient exponent) of the second polynomial:\n");
    for (int i = 0; i < n2; i++) {
        printf("Term %d: ", i + 1);
        scanf("%f %d", &coeff, &exp);
        insertNode(&poly2, coeff, exp);
    }

    printf("First Polynomial: ");
    displayPolynomial(poly1);
    printf("Second Polynomial: ");
    displayPolynomial(poly2);

    result = addPolynomials(poly1, poly2);
    printf("Resultant Polynomial after addition: ");
    displayPolynomial(result);

    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}
