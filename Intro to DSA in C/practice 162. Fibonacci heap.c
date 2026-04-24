#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int key;
    struct Node *parent;
    struct Node *child;
    struct Node *left;
    struct Node *right;
    int degree;
    int mark;
} Node;

typedef struct FibonacciHeap {
    Node *min;
    int n;
} FibonacciHeap;

Node* createNode(int key) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->left = newNode;
    newNode->right = newNode;
    newNode->degree = 0;
    newNode->mark = 0;
    return newNode;
}

FibonacciHeap* createHeap() {
    FibonacciHeap *heap = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

void insert(FibonacciHeap *heap, int key) {
    Node *node = createNode(key);
    if (!heap->min) {
        heap->min = node;
    } else {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;
        if (node->key < heap->min->key) {
            heap->min = node;
        }
    }
    heap->n++;
}

void link(Node *y, Node *x) {
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->right = y;
        y->left = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}

void consolidate(FibonacciHeap *heap) {
    int maxDegree = (int)(log(heap->n) / log(2)) + 1;
    Node *A[maxDegree];
    for (int i = 0; i < maxDegree; i++) A[i] = NULL;

    Node *x = heap->min;
    Node *start = heap->min;

    do {
        Node *y = x;
        int d = y->degree;
        while (A[d] != NULL) {
            Node *z = A[d];
            if (y->key > z->key) {
                Node *temp = y;
                y = z;
                z = temp;
            }
            link(z, y);
            A[d] = NULL;
            d++;
        }
        A[d] = y;
        x = x->right;
    } while (x != start);

    heap->min = NULL;
    for (int i = 0; i < maxDegree; i++) {
        if (A[i] != NULL) {
            if (!heap->min) {
                heap->min = A[i];
            } else {
                A[i]->left = heap->min;
                A[i]->right = heap->min->right;
                heap->min->right->left = A[i];
                heap->min->right = A[i];
                if (A[i]->key < heap->min->key) {
                    heap->min = A[i];
                }
            }
        }
    }
}

int extractMin(FibonacciHeap *heap) {
    Node *z = heap->min;
    if (z != NULL) {
        Node *child = z->child;
        if (child != NULL) {
            do {
                Node *next = child->right;
                child->left = heap->min;
                child->right = heap->min->right;
                heap->min->right->left = child;
                heap->min->right = child;
                child->parent = NULL;
                child = next;
            } while (child != z->child);
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            heap->min = NULL;
        } else {
            heap->min = z->right;
            consolidate(heap);
        }
        heap->n--;
        int minKey = z->key;
        free(z);
        return minKey;
    }
    return -1;
}

void decreaseKey(FibonacciHeap *heap, Node *x, int newKey) {
    if (newKey > x->key) {
        printf("New key is greater than current key.\n");
        return;
    }
    x->key = newKey;
    Node *y = x->parent;
    if (y != NULL && x->key < y->key) {
        // Cut the link between x and y
        cut(x, y);
        cascadingCut(y, heap);
    }
    if (x->key < heap->min->key) {
        heap->min = x;
    }
}

void cut(Node *x, Node *y) {
    if (x->right != x) {
        x->left->right = x->right;
        x->right->left = x->left;
    }
    if (y->child == x) {
        if (x->right == x) {
            y->child = NULL;
        } else {
            y->child = x->right;
        }
    }
    y->degree--;
    x->parent = NULL;
    x->left = heap->min;
    x->right = heap->min->right;
    heap->min->right->left = x;
    heap->min->right = x;
}

void cascadingCut(Node *y, FibonacciHeap *heap) {
    Node *z = y->parent;
    if (z != NULL) {
        if (y->mark == 0) {
            y->mark = 1;
        } else {
            cut(y, z);
            cascadingCut(z, heap);
        }
    }
}

void deleteNode(FibonacciHeap *heap, Node *x) {
    decreaseKey(heap, x, -INFINITY);
    extractMin(heap);
}

void unionHeaps(FibonacciHeap *heap1, FibonacciHeap *heap2) {
    if (heap1->min == NULL) {
        heap1->min = heap2->min;
        return;
    }

    if (heap2->min == NULL) return;

    Node *temp = heap1->min->right;
    heap1->min->right = heap2->min->right;
    heap2->min->right->left = heap1->min;
    heap2->min->right = temp;
    temp->left = heap2->min;

    if (heap2->min->key < heap1->min->key) {
        heap1->min = heap2->min;
    }

    heap1->n += heap2->n;
}

int main() {
    FibonacciHeap *heap = createHeap();
    int choice, key;
    Node *node;

    while(1) {
        printf("\nOperations on Fibonacci Heap:\n");
        printf("1. Insert\n");
        printf("2. Extract Minimum\n");
        printf("3. Decrease Key\n");
        printf("4. Delete Node\n");
        printf("5. Find Minimum\n");
        printf("6. Union Heaps\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(heap, key);
                break;
            case 2:
                key = extractMin(heap);
                if (key != -1)
                    printf("Extracted minimum: %d\n", key);
                else
                    printf("Heap is empty\n");
                break;
            case 3:
                printf("Enter key to decrease: ");
                scanf("%d", &key);
                node = createNode(key); // Assume the node exists for simplicity
                decreaseKey(heap, node, key - 1);
                break;
            case 4:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                node = createNode(key); // Assume node exists
                deleteNode(heap, node);
                break;
            case 5:
                if (heap->min != NULL)
                    printf("Minimum value: %d\n", heap->min->key);
                else
                    printf("Heap is empty\n");
                break;
            case 6:
                // Implement union for two heaps
                break;
            case 7:
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
