#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];  // Adjacency matrix
int color[MAX];       // Color array (0: unvisited, 1: color1, -1: color2)
int n;               // Number of vertices

// DFS function to check bipartiteness
bool isBipartiteDFS(int v, int c) {
    color[v] = c;  // Assign color

    for (int i = 0; i < n; i++) {
        if (graph[v][i]) {  // If there's an edge
            if (color[i] == 0) {  // If not colored, color with opposite
                if (!isBipartiteDFS(i, -c))
                    return false;
            } else if (color[i] == color[v]) {
                return false;  // Conflict found
            }
        }
    }
    return true;
}

// BFS function to check bipartiteness
#include <stdlib.h>

bool isBipartiteBFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    queue[rear++] = start;
    color[start] = 1;  // Start with color 1

    while (front < rear) {
        int v = queue[front++];
        for (int i = 0; i < n; i++) {
            if (graph[v][i]) {  // If there's an edge
                if (color[i] == 0) {  // If not colored
                    color[i] = -color[v];  // Assign opposite color
                    queue[rear++] = i;
                } else if (color[i] == color[v]) {
                    return false;  // Conflict found
                }
            }
        }
    }
    return true;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    // Checking using DFS
    for (int i = 0; i < n; i++) color[i] = 0;
    bool bipartiteDFS = true;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {  // Check all components
            if (!isBipartiteDFS(i, 1)) {
                bipartiteDFS = false;
                break;
            }
        }
    }

    // Checking using BFS
    for (int i = 0; i < n; i++) color[i] = 0;
    bool bipartiteBFS = true;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (!isBipartiteBFS(i)) {
                bipartiteBFS = false;
                break;
            }
        }
    }

    if (bipartiteDFS)
        printf("Graph is Bipartite (Checked using DFS)\n");
    else
        printf("Graph is NOT Bipartite (Checked using DFS)\n");

    if (bipartiteBFS)
        printf("Graph is Bipartite (Checked using BFS)\n");
    else
        printf("Graph is NOT Bipartite (Checked using BFS)\n");

    return 0;
}
