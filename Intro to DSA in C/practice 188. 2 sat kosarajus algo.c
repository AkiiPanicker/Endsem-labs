#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VAR 2000  // Maximum number of variables (can be adjusted)

// Graph representation
typedef struct Graph {
    int** adj;  // Adjacency matrix
    int numNodes;
} Graph;

// Function to initialize graph dynamically
void initGraph(Graph* g, int nodes) {
    g->numNodes = nodes;
    g->adj = (int**)malloc(nodes * sizeof(int*));
    for (int i = 0; i < nodes; i++) {
        g->adj[i] = (int*)malloc(nodes * sizeof(int));
        for (int j = 0; j < nodes; j++) {
            g->adj[i][j] = 0;
        }
    }
}

// Function to free the dynamically allocated memory of the graph
void freeGraph(Graph* g) {
    for (int i = 0; i < g->numNodes; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
}

// Function to add directed edge to the graph
void addEdge(Graph* g, int u, int v) {
    g->adj[u][v] = 1;
}

// Function to perform DFS and fill the order of vertices
void dfs(Graph* g, int node, bool* visited, int* order, int* index) {
    visited[node] = true;
    for (int i = 0; i < g->numNodes; i++) {
        if (g->adj[node][i] == 1 && !visited[i]) {
            dfs(g, i, visited, order, index);
        }
    }
    order[(*index)++] = node;
}

// Function to reverse the graph
void reverseGraph(Graph* g, Graph* rev) {
    for (int i = 0; i < g->numNodes; i++) {
        for (int j = 0; j < g->numNodes; j++) {
            if (g->adj[i][j] == 1) {
                addEdge(rev, j, i);
            }
        }
    }
}

// Function to check if 2-SAT is satisfiable using Kosaraju's algorithm
bool isSatisfiable(Graph* g, int numVars) {
    bool* visited = (bool*)malloc(g->numNodes * sizeof(bool)); // Dynamically allocated visited array
    int* order = (int*)malloc(g->numNodes * sizeof(int));  // Dynamically allocated order array
    int index = 0;

    // Step 1: Perform DFS to fill the order of vertices
    for (int i = 0; i < g->numNodes; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < g->numNodes; i++) {
        if (!visited[i]) {
            dfs(g, i, visited, order, &index);
        }
    }

    // Step 2: Reverse the graph
    Graph revGraph;
    initGraph(&revGraph, g->numNodes);
    reverseGraph(g, &revGraph);

    // Step 3: Perform DFS on reversed graph to find SCCs
    bool* component = (bool*)malloc(g->numNodes * sizeof(bool)); // Dynamically allocated component array
    for (int i = 0; i < g->numNodes; i++) {
        component[i] = false;
    }

    // Step 4: Process nodes in reverse order of DFS
    for (int i = g->numNodes - 1; i >= 0; i--) {
        int v = order[i];
        if (!component[v]) {
            bool* stack = (bool*)malloc(g->numNodes * sizeof(bool)); // Dynamically allocated stack array
            int stackTop = -1;
            stack[++stackTop] = v;
            component[v] = true;
            // Find all nodes in the same SCC
            while (stackTop >= 0) {
                int node = stack[stackTop--];
                for (int j = 0; j < g->numNodes; j++) {
                    if (revGraph.adj[node][j] == 1 && !component[j]) {
                        stack[++stackTop] = j;
                        component[j] = true;
                    }
                }
            }
            free(stack); // Free the dynamically allocated stack
        }
    }

    // Step 5: Check for contradictions
    for (int i = 0; i < numVars; i++) {
        if (component[i] == component[i + numVars]) {
            free(visited);
            free(order);
            free(component);
            return false;  // Unsatisfiable
        }
    }

    // Free dynamically allocated memory
    free(visited);
    free(order);
    free(component);

    return true;  // Satisfiable
}

int main() {
    int numVars, numClauses;
    printf("Enter number of variables: ");
    scanf("%d", &numVars);

    Graph g;
    initGraph(&g, 2 * numVars);  // Each variable and its negation

    printf("Enter number of clauses: ");
    scanf("%d", &numClauses);

    // Reading clauses and adding edges to the graph
    for (int i = 0; i < numClauses; i++) {
        int x, y;
        printf("Enter clause %d (x y): ", i + 1);
        scanf("%d %d", &x, &y);

        // Convert the literals to indices
        int xIndex = (x > 0) ? x - 1 : -x - 1 + numVars;
        int yIndex = (y > 0) ? y - 1 : -y - 1 + numVars;

        // Add implications
        addEdge(&g, numVars + (x < 0), yIndex);  // ¬x → y
        addEdge(&g, numVars + (y < 0), xIndex);  // ¬y → x
    }

    // Check satisfiability
    if (isSatisfiable(&g, numVars)) {
        printf("The 2-SAT formula is satisfiable.\n");
    } else {
        printf("The 2-SAT formula is unsatisfiable.\n");
    }

    // Free dynamically allocated memory
    freeGraph(&g);

    return 0;
}
