#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define MAX_EDGES 10000

struct Edge {
    int to;
    int rev;  // Index of reverse edge
    int capacity;
    int flow;
};

struct Graph {
    struct Edge edges[MAX_NODES][MAX_EDGES];
    int edge_count[MAX_NODES];
    int level[MAX_NODES];
    int ptr[MAX_NODES];
};

void add_edge(struct Graph* g, int from, int to, int capacity) {
    // Forward edge
    g->edges[from][g->edge_count[from]] = (struct Edge){
        .to = to,
        .rev = g->edge_count[to],
        .capacity = capacity,
        .flow = 0
    };
    
    // Reverse edge
    g->edges[to][g->edge_count[to]] = (struct Edge){
        .to = from,
        .rev = g->edge_count[from],
        .capacity = 0,
        .flow = 0
    };
    
    g->edge_count[from]++;
    g->edge_count[to]++;
}

int bfs(struct Graph* g, int s, int t) {
    for (int i = 0; i < MAX_NODES; i++) g->level[i] = -1;
    g->level[s] = 0;
    
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = s;
    
    while (front < rear) {
        int u = queue[front++];
        for (int i = 0; i < g->edge_count[u]; i++) {
            struct Edge* e = &g->edges[u][i];
            if (g->level[e->to] == -1 && e->flow < e->capacity) {
                g->level[e->to] = g->level[u] + 1;
                queue[rear++] = e->to;
            }
        }
    }
    return g->level[t] != -1;
}

int dfs(struct Graph* g, int u, int t, int flow) {
    if (u == t) return flow;
    
    for (; g->ptr[u] < g->edge_count[u]; g->ptr[u]++) {
        struct Edge* e = &g->edges[u][g->ptr[u]];
        
        if (g->level[e->to] == g->level[u] + 1 && e->flow < e->capacity) {
            int min_flow = (flow < e->capacity - e->flow) ? flow : (e->capacity - e->flow);
            int pushed = dfs(g, e->to, t, min_flow);
            
            if (pushed > 0) {
                e->flow += pushed;
                g->edges[e->to][e->rev].flow -= pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int max_flow(struct Graph* g, int s, int t) {
    int total_flow = 0;
    
    while (bfs(g, s, t)) {
        for (int i = 0; i < MAX_NODES; i++) g->ptr[i] = 0;
        
        while (int pushed = dfs(g, s, t, INT_MAX)) {
            total_flow += pushed;
        }
    }
    return total_flow;
}

int main() {
    struct Graph g = {0};
    
    // Example network from CP-Algorithms
    add_edge(&g, 0, 1, 3);
    add_edge(&g, 0, 2, 3);
    add_edge(&g, 1, 2, 2);
    add_edge(&g, 1, 3, 3);
    add_edge(&g, 2, 3, 1);
    add_edge(&g, 2, 4, 2);
    add_edge(&g, 3, 4, 2);

    printf("Maximum flow: %d\n", max_flow(&g, 0, 4));
    return 0;
}
