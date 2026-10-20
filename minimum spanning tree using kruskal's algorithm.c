#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// Structure to represent an edge for explicit sorting
typedef struct {
    int u, v, w;
} Edge;

// Disjoint Set find function with path compression
int find_set(int i, int parent[]) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_set(parent[i], parent);
}

// Disjoint Set union function
int union_sets(int i, int j, int parent[]) {
    int root_i = find_set(i, parent);
    int root_j = find_set(j, parent);
    if (root_i != root_j) {
        parent[root_i] = root_j;
        return 1;
    }
    return 0;
}

// Comparator function to sort edges strictly by weight, then row-wise order
int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->w != e2->w) {
        return e1->w - e2->w;
    }
    if (e1->u != e2->u) {
        return e1->u - e2->u;
    }
    return e1->v - e2->v;
}



void kruskalMST(int **cost, int V) {
  int max_edges = (V * (V - 1)) / 2;
    Edge *edges = (Edge *)malloc(max_edges * sizeof(Edge));
    int edge_idx = 0;

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (cost[i][j] != 9999) {
                edges[edge_idx].u = i;
                edges[edge_idx].v = j;
                edges[edge_idx].w = cost[i][j];
                edge_idx++;
            }
        }
    }

    // 2. Sort the edges according to the priority requirements
    qsort(edges, edge_idx, sizeof(Edge), compareEdges);

    // 3. Initialize DSU components
    int *parent = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    int edge_count = 0;
    int min_cost = 0;

    // 4. Iterate through sorted edges and construct the MST
    for (int i = 0; i < edge_idx && edge_count < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (union_sets(u, v, parent)) {
            printf("Edge %d:(%d, %d) cost:%d\n", edge_count, u, v, w);
            min_cost += w;
            edge_count++;
        }
    }

    printf("Minimum cost= %d\n", min_cost);

    // Clean up memory
    free(parent);
    free(edges);
}
	// Write your code here...
	



int main() {
    int V;
    printf("No of vertices: ");
    scanf("%d", &V);

    int **cost = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        cost[i] = (int *)malloc(V * sizeof(int));

    printf("Adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &cost[i][j]);

    kruskalMST(cost, V);

    for (int i = 0; i < V; i++)
        free(cost[i]);
    free(cost);

    return 0;
}
