#include <limits.h> 
#include <stdio.h>
#define MAX 20
int V, E;
int graph[MAX][MAX];
#define INFINITY 99999

void dijkstra(int G[MAX][MAX], int n, int startnode) {
	
	int distance[MAX], pred[MAX];
    int visited[MAX];
    int count, nextnode, i, j;
    
    // Initialize the graph matrix defaults since main() sets graph[i][i]=0 instead of graph[i][j]=INFINITY
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i != j && G[i][j] == 0) {
                G[i][j] = INFINITY;
            }
        }
    }

    // Initialize distance, predecessor, and visited arrays
    for (i = 1; i <= n; i++) {
        distance[i] = G[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }

    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;

    while (count < n - 1) {
        int mindistance = INFINITY;
        nextnode = -1;

        // Find the unvisited node with the minimum distance
        for (i = 1; i <= n; i++) {
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        // If no more reachable nodes are found, break early
        if (nextnode == -1) {
            break;
        }

        visited[nextnode] = 1;
        
        // Update the distance of neighboring nodes
        for (i = 1; i <= n; i++) {
            if (!visited[i]) {
                if (mindistance + G[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + G[nextnode][i];
                    pred[i] = nextnode;
                }
            }
        }
        count++;
    }

    // Print the output exactly matching the sample layout
    printf("Node\tDistance\tPath\n");
    for (i = 1; i <= n; i++) {
        if (i != startnode) {
            // Check if node is unreachable
            if (distance[i] >= INFINITY || distance[i] < 0) {
                printf("   %d\t     INF\tNO PATH\n", i);
            } else {
                printf("   %d\t       %d\t%d", i, distance[i], i);
                j = i;
                // Trace the path backwards using the predecessor array
                while (j != startnode) {
                    j = pred[j];
                    printf("<-%d", j);
                }
                printf("\n");
            }
        }
    }
// write your code here
	
}
int main() { 
	int s, d, w, i, j;
	printf("Enter the number of vertices : ");
	scanf("%d", &V);
	printf("Enter the number of edges : ");
	scanf("%d", &E);
	for(i = 1 ; i <= V; i++) {
		for(j = 1; j <= V; j++) {
			graph[i][i] = 0;
		}
	}
	for(i = 1; i <= E; i++) {
		printf("Enter source : ");
		scanf("%d", &s);
		printf("Enter destination : ");
		scanf("%d", &d);
		printf("Enter weight : ");
		scanf("%d", &w);
		if(s > V || d > V || s <= 0 || d <= 0) {
			printf("Invalid index. Try again.\n");
			i--;
			continue;
		} else {
			graph[s][d] = w;
		}
	}
	printf("Enter the source :");
	scanf("%d", &s);
	dijkstra(graph, V, s); 
	return 0; 
} 
