#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, uncomment the following two lines:
    // newNode = createNode(src);
    // newNode->next = graph->adjLists[dest];
    // graph->adjLists[dest] = newNode;
}

void insertNode(Graph* graph) {
    graph->numVertices++;
    graph->adjLists = (Node**)realloc(graph->adjLists, graph->numVertices * sizeof(Node*));
    graph->adjLists[graph->numVertices - 1] = NULL;
    graph->visited = (bool*)realloc(graph->visited, graph->numVertices * sizeof(bool));
    graph->visited[graph->numVertices - 1] = false;
    printf("Node %d added.\n", graph->numVertices - 1);
}

void deleteEdge(Graph* graph, int src, int dest) {
    Node* current = graph->adjLists[src];
    Node* prev = NULL;
    while (current != NULL && current->data != dest) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Edge not found.\n");
        return;
    }

    if (prev == NULL) {
        graph->adjLists[src] = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("Edge from %d to %d deleted.\n", src, dest);
}

void deleteNode(Graph* graph, int vertex) {
    if (vertex >= graph->numVertices) {
        printf("Vertex not found.\n");
        return;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (i != vertex) {
            deleteEdge(graph, i, vertex);
        }
    }

    free(graph->adjLists[vertex]);
    graph->adjLists[vertex] = NULL;
    printf("Node %d deleted.\n", vertex);
}

void BFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
    int queue[graph->numVertices];
    int front = 0;
    int rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    free(visited);
    printf("\n");
}

void DFSUtil(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int adjVertex = temp->data;
        if (!graph->visited[adjVertex]) {
            DFSUtil(graph, adjVertex);
        }
        temp = temp->next;
    }
}

void DFS(Graph* graph, int startVertex) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = false;
    }
    DFSUtil(graph, startVertex);
    printf("\n");
}

bool searchElement(Graph* graph, int element) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            if (temp->data == element) {
                return true;
            }
            temp = temp->next;
        }
    }
    return false;
}

int main() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("BFS traversal starting from vertex 0:\n");
    BFS(graph, 0);

    printf("DFS traversal starting from vertex 0:\n");
    DFS(graph, 0);

    printf("Searching for element 3 in the graph: %s\n", searchElement(graph, 3) ? "Found" : "Not found");
    printf("Searching for element 10 in the graph: %s\n", searchElement(graph, 10) ? "Found" : "Not found");

    printf("Deleting edge from 1 to 4:\n");
    deleteEdge(graph, 1, 4);

    printf("Inserting a new node in the graph:\n");
    insertNode(graph);

    printf("Deleting node 2:\n");
    deleteNode(graph, 2);

    return 0;
}
