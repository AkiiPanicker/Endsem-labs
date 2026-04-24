#include <stdio.h>
#include <stdbool.h>

#define MAX 10  // Maximum maze size

// Maze representation (0 = open, 1 = wall)
int maze[MAX][MAX] = {
    {0, 1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0, 1},
    {0, 0, 0, 1, 0, 0},
    {1, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0}
};

int rows = 5, cols = 6; // Maze dimensions

// Graph adjacency matrix
bool graph[MAX * MAX][MAX * MAX] = {false};

// Movement directions: Left, Right, Up, Down
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

// Start and exit positions
int startX = 0, startY = 0;
int endX = 4, endY = 5;

// Converts 2D (i, j) index to 1D graph index
int getIndex(int x, int y) {
    return x * cols + y;
}

// Construct graph from maze
void constructGraph() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 0) {  // If it's an open path
                int u = getIndex(i, j);
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && maze[ni][nj] == 0) {
                        int v = getIndex(ni, nj);
                        graph[u][v] = graph[v][u] = true; // Undirected edge
                    }
                }
            }
        }
    }
}

// DFS function to find a path
bool visited[MAX * MAX];
int path[MAX * MAX], pathIndex = 0;

bool dfs(int u, int target) {
    visited[u] = true;
    path[pathIndex++] = u;

    if (u == target) return true;  // Found exit

    for (int v = 0; v < rows * cols; v++) {
        if (graph[u][v] && !visited[v]) {
            if (dfs(v, target)) return true;  // If found path, return true
        }
    }

    pathIndex--;  // Backtrack
    return false;
}

// Print the maze solution path
void printSolutionPath() {
    printf("Maze Solution Path:\n");
    for (int i = 0; i < pathIndex; i++) {
        int x = path[i] / cols, y = path[i] % cols;
        printf("(%d, %d) -> ", x, y);
    }
    printf("Exit\n");
}

int main() {
    constructGraph();

    int start = getIndex(startX, startY);
    int end = getIndex(endX, endY);

    // Initialize visited array
    for (int i = 0; i < rows * cols; i++) visited[i] = false;

    if (dfs(start, end)) {
        printSolutionPath();
    } else {
        printf("No path found in the maze.\n");
    }

    return 0;
}
