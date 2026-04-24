#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum number of vertices

// Graph structure
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX];
    int indegree[MAX];  // Needed for Kahn's Algorithm
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
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->indegree[i] = 0;
    }
    return graph;
}

// Add a directed edge
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    graph->indegree[dest]++;  // Increase indegree for BFS method
}

// DFS-based Topological Sorting
void DFS(Graph* graph, int vertex, int visited[], Stack* stack) {
    visited[vertex] = 1;

    // Visit all adjacent vertices
    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {
            DFS(graph, neighbor, visited, stack);
        }
        temp = temp->next;
    }

    // Push to stack after processing all neighbors
    push(stack, vertex);
}

// Function to perform DFS-based Topological Sort
void topologicalSortDFS(Graph* graph) {
    int visited[MAX] = {0};
    Stack stack;
    initStack(&stack);

    // Call DFS for unvisited vertices
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            DFS(graph, i, visited, &stack);
        }
    }

    // Print topological order (reverse of stack)
    printf("Topological Sort (DFS-based): ");
    while (!isEmpty(&stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");
}

// BFS-based Topological Sorting (Kahn's Algorithm)
void topologicalSortBFS(Graph* graph) {
    int inDeg[MAX], queue[MAX];
    int front = 0, rear = 0;

    // Initialize indegree array
    for (int i = 0; i < graph->numVertices; i++) {
        inDeg[i] = graph->indegree[i];
        if (inDeg[i] == 0) {
            queue[rear++] = i;  // Enqueue nodes with zero indegree
        }
    }

    printf("Topological Sort (BFS-based / Kahn's Algorithm): ");
    int count = 0;
    while (front < rear) {
        int vertex = queue[front++]; // Dequeue
        printf("%d ", vertex);
        count++;

        // Reduce indegree for neighbors and enqueue if it becomes zero
        Node* temp = graph->adjLists[vertex];
        while (temp) {
            inDeg[temp->vertex]--;
            if (inDeg[temp->vertex] == 0) {
                queue[rear++] = temp->vertex;
            }
            temp = temp->next;
        }
    }

    if (count != graph->numVertices) {
        printf("\nCycle detected! Topological sorting not possible.\n");
    } else {
        printf("\n");
    }
}

// Main function
int main() {
    int vertices = 6;
    Graph* graph = createGraph(vertices);

    // Sample DAG
    addEdge(graph, 5, 0);
    addEdge(graph, 5, 2);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    // Perform Topological Sorting
    topologicalSortDFS(graph);
    topologicalSortBFS(graph);

    return 0;
}
