#include <stdio.h>
#include <stdlib.h>


int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        return 0;
    }


    int *values = (int *)malloc(N * sizeof(int));
    int *weights = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        if (scanf("%d", &values[i]) != 1) return 0;
    }

    for (int i = 0; i < N; i++) {
        if (scanf("%d", &weights[i]) != 1) return 0;
    }

    int W;
    if (scanf("%d", &W) != 1) return 0;


    int *dp = (int *)calloc(W + 1, sizeof(int));


    for (int i = 0; i < N; i++) {
        int item_weight = weights[i];
        int item_value = values[i];


        for (int w = W; w >= item_weight; w--) {
            dp[w] = max(dp[w], dp[w - item_weight] + item_value);
        }
    }


    printf("%d\n", dp[W]);


    free(values);
    free(weights);
    free(dp);

    return 0;
}
