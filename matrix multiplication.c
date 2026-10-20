#include <stdio.h>
#include <stdlib.h>

void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int m = n / 2;

    int A11[m][m], A12[m][m], A21[m][m], A22[m][m];
    int B11[m][m], B12[m][m], B21[m][m], B22[m][m];

    int M1[m][m], M2[m][m], M3[m][m], M4[m][m];
    int M5[m][m], M6[m][m], M7[m][m];

    int T1[m][m], T2[m][m];

    // Divide matrices into four sub-matrices
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(m, A11, A22, T1);
    add(m, B11, B22, T2);
    strassen(m, T1, T2, M1);

    // M2 = (A21 + A22) * B11
    add(m, A21, A22, T1);
    strassen(m, T1, B11, M2);

    // M3 = A11 * (B12 - B22)
    subtract(m, B12, B22, T1);
    strassen(m, A11, T1, M3);

    // M4 = A22 * (B21 - B11)
    subtract(m, B21, B11, T1);
    strassen(m, A22, T1, M4);

    // M5 = (A11 + A12) * B22
    add(m, A11, A12, T1);
    strassen(m, T1, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(m, A21, A11, T1);
    add(m, B11, B12, T2);
    strassen(m, T1, T2, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(m, A12, A22, T1);
    add(m, B21, B22, T2);
    strassen(m, T1, T2, M7);

    int C11[m][m], C12[m][m], C21[m][m], C22[m][m];

    // C11 = M1 + M4 - M5 + M7
    add(m, M1, M4, T1);
    subtract(m, T1, M5, T2);
    add(m, T2, M7, C11);

    // C12 = M3 + M5
    add(m, M3, M5, C12);

    // C21 = M2 + M4
    add(m, M2, M4, C21);

    // C22 = M1 - M2 + M3 + M6
    subtract(m, M1, M2, T1);
    add(m, T1, M3, T2);
    add(m, T2, M6, C22);

    // Combine sub-matrices
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }
}

int main() {
    int r1, c1, r2, c2;

    scanf("%d %d", &r1, &c1);

    int A_original[r1][c1];

    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++)
            scanf("%d", &A_original[i][j]);

    scanf("%d %d", &r2, &c2);

    // Check whether multiplication is possible
    if (c1 != r2) {
        printf("Invalid input\n");
        return 0;
    }

    int B_original[r2][c2];

    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++)
            scanf("%d", &B_original[i][j]);

    // Find next power of 2
    int n = r1;

    if (c1 > n) n = c1;
    if (r2 > n) n = r2;
    if (c2 > n) n = c2;

    int size = 1;
    while (size < n)
        size *= 2;

    // Padded square matrices
    int A[size][size];
    int B[size][size];
    int C[size][size];

    // Initialize with zeros
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = 0;
            B[i][j] = 0;
            C[i][j] = 0;
        }
    }

    // Copy original matrices
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++)
            A[i][j] = A_original[i][j];

    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++)
            B[i][j] = B_original[i][j];

    // Strassen multiplication
    strassen(size, A, B, C);

    // Print only required r1 x c2 portion
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
