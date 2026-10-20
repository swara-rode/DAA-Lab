#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

typedef struct {
    int u, v, w;
} Edge;

void printPath(int parent[], int v) {
    if (parent[v] == -1) {
        printf("%d", v);
        return;
    }
    printPath(parent, parent[v]);
    printf("->%d", v);
}

int main() {
    int V, E;
    scanf("%d", &V); 
    scanf("%d", &E);

    Edge edges[E];

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    int source;
    scanf("%d", &source);

    int dist[V + 1], parent[V + 1];

    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[source] = 0;

    // Bellman-Ford relaxation
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // Check for negative cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative cycle detected");
            return 0;
        }
    }

    // Print shortest distances and paths
    for (int i = 1; i <= V; i++) {
        if (i == source)
            continue;

        if (dist[i] == INF) {
            printf("%d INF None\n", i);
        } else {
            printf("%d %d ", i, dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }

    return 0;
}
