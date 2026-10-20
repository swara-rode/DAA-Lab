#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

int n;
int cost[20][20];
int memo[20][1 << 20];

// Helper function to find the minimum of two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// TSP solver using Dynamic Programming + Bitmasking
int tsp(int mask, int u) {
    // If all cities have been visited, return the cost to go back to the starting city (0)
    if (mask == (1 << n) - 1) {
        if (cost[u][0] == -1) return INF;
        return cost[u][0];
    }
    
    // Return cached result if already computed
    if (memo[u][mask] != -1) {
        return memo[u][mask];
    }
    
    int ans = INF;
    
    // Try visiting all other unvisited cities
    for (int v = 0; v < n; v++) {
        if (!(mask & (1 << v)) && cost[u][v] != -1) {
            int new_cost = cost[u][v] + tsp(mask | (1 << v), v);
            ans = min(ans, new_cost);
        }
    }
    
    return memo[u][mask] = ans;
}

int main() {
    // Read the number of cities
    if (scanf("%d", &n) != 1) return 0;
    
    // Read the cost matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
    
    // Initialize memoization table with -1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            memo[i][j] = -1;
        }
    }
    
    // Start the tour from city 0 with only city 0 visited (mask = 1)
    int ans = tsp(1, 0);
    
    // Output the optimal cost (or -1 if no valid path exists)
    if (ans >= INF) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
    
    return 0;
}
