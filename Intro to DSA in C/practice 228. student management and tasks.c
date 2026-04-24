#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Graph structure
typedef struct {
    int vertices;
    int adj[MAX][MAX];  // Adjacency matrix
    int visited[MAX];   // Visited array
    int team[MAX];      // Team assigned to each task
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
        g->team[i] = -1; // No team assigned initially
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

// DFS function for topological sort and team dependency check
int dfs(Graph *g, int v, Stack *s, int *cross_team_dependency) {
    g->visited[v] = 1;

    for (int i = 0; i < g->vertices; i++) {
        if (g->adj[v][i] == 1) {
            // Check for cross-team dependencies
            if (g->team[v] != -1 && g->team[i] != -1 && g->team[v] != g->team[i]) {
                *cross_team_dependency = 1;
            }
            if (!g->visited[i]) {
                dfs(g, i, s, cross_team_dependency);
            }
        }
    }
    push(s, v);
    return 0;
}

// Topological Sorting with team dependency check
void topologicalSort(Graph *g) {
    Stack s;
    s.top = -1;
    int cross_team_dependency = 0;

    for (int i = 0; i < g->vertices; i++) {
        if (!g->visited[i]) {
            dfs(g, i, &s, &cross_team_dependency);
        }
    }

    // Print the execution order
    printf("Execution Order: ");
    while (s.top != -1) {
        printf("Task %d ", pop(&s));
    }
    printf("\n");

    if (cross_team_dependency) {
        printf("There are dependencies between different teams.\n");
    } else {
        printf("No dependencies between different teams.\n");
    }
}

// Driver Code
int main() {
    Graph g;
    int vertices = 6;
    
    initGraph(&g, vertices);

    // Assign teams to tasks
    g.team[0] = 1; g.team[1] = 2; g.team[2] = 1;
    g.team[3] = 2; g.team[4] = 1; g.team[5] = 3;

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
