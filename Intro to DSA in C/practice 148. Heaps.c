#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    int size;
    int capacity;
} Heap;

#define INITIAL_CAPACITY 10

Heap* createHeap() {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->array = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    heap->size = 0;
    heap->capacity = INITIAL_CAPACITY;
    return heap;
}

void resizeHeap(Heap* heap) {
    heap->capacity *= 2;
    heap->array = (int*)realloc(heap->array, heap->capacity * sizeof(int));
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(Heap* heap, int index) {
    int parentIndex = (index - 1) / 2;
    if (index > 0 && heap->array[index] < heap->array[parentIndex]) {
        swap(&heap->array[index], &heap->array[parentIndex]);
        heapifyUp(heap, parentIndex);
    }
}

void insert(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        resizeHeap(heap);
    }
    heap->array[heap->size] = value;
    heapifyUp(heap, heap->size);
    heap->size++;
}

void heapifyDown(Heap* heap, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < heap->size && heap->array[leftChild] < heap->array[smallest]) {
        smallest = leftChild;
    }
    if (rightChild < heap->size && heap->array[rightChild] < heap->array[smallest]) {
        smallest = rightChild;
    }
    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        heapifyDown(heap, smallest);
    }
}

int removeMin(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty.\n");
        return -1;
    }
    int minValue = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return minValue;
}

void displayHeap(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

void freeHeap(Heap* heap) {
    free(heap->array);
    free(heap);
}

int main() {
    Heap* heap = createHeap();

    insert(heap, 10);
    insert(heap, 4);
    insert(heap, 15);
    insert(heap, 20);
    insert(heap, 3);

    printf("Heap after insertions: ");
    displayHeap(heap);

    printf("Removed min: %d\n", removeMin(heap));
    printf("Heap after removal: ");
    displayHeap(heap);

    freeHeap(heap);
    return 0;
}
