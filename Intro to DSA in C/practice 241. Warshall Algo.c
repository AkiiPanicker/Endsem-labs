#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void warshall(int graph[MAX][MAX], int V){
    int path[MAX][MAX];

    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            path[i][j] = graph[i][j];
        }
    }
    for(int k=0; k<V; k++){
        for(int i=0; i<V; i++){
            for(int j=0;j<V;j++){
                path[i][j] = path[i][j] || (path[i][k] && path[k][j]);
            }
        }
    }
    printf("Transitive Closure");
    for(int i=0; i<V;i++){
        for(int j=0; j<V; j++){
            printf("%d", path[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int V;
    int graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (0 or 1):\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    warshall(graph, V);

    return 0;
}