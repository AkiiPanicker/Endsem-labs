#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // Maximum vertices

int path[MAX]; // Array to store the path of vertices
int graph[MAX][MAX]; // Adjacency matrix for the graph

// Function to check if a vertex can be added to the Hamiltonian path
bool isSafe(int v, int pos, int n) {
    // Check if this vertex is an adjacent vertex of the previous vertex
    if (graph[path[pos-1]][v] == 0) {
        return false;
    }

    // Check if the vertex has already been included
    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;
}

// Function to solve the Hamiltonian Circuit problem using backtracking
bool hamCycleUtil(int n, int pos) {
    // If all vertices are included in the path
    if (pos == n) {
        // And if there is an edge from the last vertex to the first vertex
        if (graph[path[pos-1]][path[0]] == 1) {
            return true;
        } else {
            return false;
        }
    }

    // Try different vertices as the next candidate in the Hamiltonian Cycle
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos, n)) {
            path[pos] = v;
            if (hamCycleUtil(n, pos + 1)) {
                return true;
            }
            // Backtrack
            path[pos] = -1;
        }
    }

    return false;
}

// Function to solve the Hamiltonian Cycle problem
bool hamCycle(int n) {
    // Initialize the path array with -1
    for (int i = 0; i < n; i++) {
        path[i] = -1;
    }

    // Let the first vertex be the starting point
    path[0] = 0;

    // Try to find the Hamiltonian cycle starting from the second vertex
    if (hamCycleUtil(n, 1)) {
        return true;
    }

    return false;
}

// Function to print the Hamiltonian Cycle
void printSolution(int n) {
    printf("Hamiltonian Cycle: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", path[i]);
    }
    printf("%d\n", path[0]);  // To make it a cycle
}

int main() {
    int n;

    // Take number of vertices as input
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (1 for an edge, 0 for no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    if (hamCycle(n)) {
        printSolution(n);
    } else {
        printf("Solution does not exist\n");
    }

    return 0;
}
