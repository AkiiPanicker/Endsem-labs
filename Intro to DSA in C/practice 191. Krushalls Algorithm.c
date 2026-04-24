#include <stdio.h>
#include <stdlib.h>

// Structure for an edge
typedef struct Edge {
    int src, dest, weight;
} Edge;

// Structure for a graph
typedef struct Graph {
    int numNodes, numEdges;
    Edge* edges;
} Graph;

// Structure for Union-Find
typedef struct Subset {
    int parent, rank;
} Subset;

// Function to create a graph
Graph* createGraph(int nodes, int edges) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = nodes;
    graph->numEdges = edges;
    graph->edges = (Edge*)malloc(edges * sizeof(Edge));
    return graph;
}

// Find operation in Union-Find
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);  // Path compression
    return subsets[i].parent;
}

// Union operation in Union-Find
void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Comparison function for sorting edges by weight
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Function to find MST using Kruskal's Algorithm
void kruskalMST(Graph* graph) {
    int nodes = graph->numNodes;
    Edge* result = (Edge*)malloc((nodes - 1) * sizeof(Edge));  
    int e = 0;  // Index for result[]
    
    qsort(graph->edges, graph->numEdges, sizeof(Edge), compareEdges);

    Subset* subsets = (Subset*)malloc(nodes * sizeof(Subset));
    for (int i = 0; i < nodes; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    for (int i = 0; i < graph->numEdges && e < nodes - 1; i++) {
        Edge nextEdge = graph->edges[i];
        int root1 = find(subsets, nextEdge.src);
        int root2 = find(subsets, nextEdge.dest);

        if (root1 != root2) {
            result[e++] = nextEdge;
            unionSets(subsets, root1, root2);
        }
    }

    printf("Minimum Spanning Tree (Kruskal's Algorithm):\n");
    for (int i = 0; i < e; i++)
        printf("%d - %d (Weight: %d)\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
    free(result);  
}

int main() {
    int numNodes, numEdges;
    
    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);
    printf("Enter number of edges: ");
    scanf("%d", &numEdges);

    Graph* graph = createGraph(numNodes, numEdges);

    printf("Enter edges (src dest weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    kruskalMST(graph);
    
    free(graph->edges);
    free(graph);
    return 0;
}
