#include <stdio.h>

#define MAX 100

int a[MAX], subset[MAX];
int ans[MAX][MAX], len[MAX];
int count = 0;
int n, target;

void storeSubset(int size) {
    len[count] = size;
    for (int i = 0; i < size; i++)
        ans[count][i] = subset[i];
    count++;
}

void findSubsets(int index, int sum, int size) {
    if (sum == target) {
        storeSubset(size);
        return;
    }

    if (index == n || sum > target)
        return;

    // Include current element
    subset[size] = a[index];
    findSubsets(index + 1, sum + a[index], size + 1);

    // Exclude current element
    findSubsets(index + 1, sum, size);
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    scanf("%d", &target);

    findSubsets(0, 0, 0);

    if (count == 0) {
        printf("-1");
    } else {
        for (int i = count - 1; i >= 0; i--) {
            for (int j = 0; j < len[i]; j++)
                printf("%d ", ans[i][j]);
            printf("\n");
        }
    }

    return 0;
}

