#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Graph structure
typedef struct {
    int vertices;
    int adj[MAX][MAX]; // Adjacency matrix
    int visited[MAX];  // Visited array
} Graph;

// Stack for storing topological order
typedef struct {
    int data[MAX];
    int top;
} Stack;

void initGraph(Graph *g, int vertices) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++)
            g->adj[i][j] = 0;
        g->visited[i] = 0;
    }
}

void addEdge(Graph *g, int u, int v) {
    g->adj[u][v] = 1; // Directed edge u -> v
}

// Stack functions
void push(Stack *s, int value) {
    s->data[++(s->top)] = value;
}

int pop(Stack *s) {
    return s->data[(s->top)--];
}

// DFS function for topological sort
void dfs(Graph *g, int v, Stack *s) {
    g->visited[v] = 1;

    for (int i = 0; i < g->vertices; i++) {
        if (g->adj[v][i] == 1 && !g->visited[i]) {
            dfs(g, i, s);
        }
    }

    push(s, v);
}

// Topological Sorting
void topologicalSort(Graph *g) {
    Stack s;
    s.top = -1;

    for (int i = 0; i < g->vertices; i++) {
        if (!g->visited[i]) {
            dfs(g, i, &s);
        }
    }

    // Print the execution order
    printf("Execution Order: ");
    while (s.top != -1) {
        printf("Task %d ", pop(&s));
    }
    printf("\n");
}

// Driver Code
int main() {
    Graph g;
    int vertices = 6;
    
    initGraph(&g, vertices);

    // Adding dependency edges (Directed edges)
    addEdge(&g, 5, 2);
    addEdge(&g, 5, 0);
    addEdge(&g, 4, 0);
    addEdge(&g, 4, 1);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 1);

    topologicalSort(&g);

    return 0;
}
