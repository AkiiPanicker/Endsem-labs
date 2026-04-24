#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100  // Maximum number of vertices

// Graph structure using adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX];
    bool visited[MAX];
} Graph;

// Stack for DFS
typedef struct Stack {
    int data[MAX];
    int top;
} Stack;

// Function to initialize stack
void initStack(Stack* s) {
    s->top = -1;
}

// Push function
void push(Stack* s, int value) {
    s->data[++(s->top)] = value;
}

// Pop function
int pop(Stack* s) {
    return s->data[(s->top)--];
}

// Check if stack is empty
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// Create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

// Add an edge to the graph (undirected)
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add for undirected graph
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// DFS traversal
void DFS(Graph* graph, int startVertex) {
    Stack stack;
    initStack(&stack);

    // Arrays to track push and pop order
    int pushOrder[MAX], popOrder[MAX];
    int pushIndex = 0, popIndex = 0;

    push(&stack, startVertex);
    graph->visited[startVertex] = true;
    pushOrder[pushIndex++] = startVertex;

    while (!isEmpty(&stack)) {
        int vertex = stack.data[stack.top];  // Peek
        bool hasUnvisitedNeighbor = false;

        // Explore neighbors
        Node* temp = graph->adjLists[vertex];
        while (temp) {
            int neighbor = temp->vertex;
            if (!graph->visited[neighbor]) {
                push(&stack, neighbor);
                graph->visited[neighbor] = true;
                pushOrder[pushIndex++] = neighbor;
                hasUnvisitedNeighbor = true;
                break;
            }
            temp = temp->next;
        }

        // If no unvisited neighbor, pop the vertex
        if (!hasUnvisitedNeighbor) {
            popOrder[popIndex++] = pop(&stack);
        }
    }

    // Print push order
    printf("Push Order: ");
    for (int i = 0; i < pushIndex; i++) {
        printf("%d ", pushOrder[i]);
    }
    printf("\n");

    // Print pop order
    printf("Pop Order: ");
    for (int i = 0; i < popIndex; i++) {
        printf("%d ", popOrder[i]);
    }
    printf("\n");
}

// Main function
int main() {
    int vertices = 6;  // Number of vertices
    Graph* graph = createGraph(vertices);

    // Sample graph edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    printf("DFS Traversal starting from vertex 0:\n");
    DFS(graph, 0);

    return 0;
}
