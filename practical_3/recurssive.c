#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** allocate_matrix(int n) {
    int **matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void matrix_add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void recursive_matrix_multiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    
    int half = n / 2;
    
    // Allocate memory for submatrices
    int **A11 = allocate_matrix(half);
    int **A12 = allocate_matrix(half);
    int **A21 = allocate_matrix(half);
    int **A22 = allocate_matrix(half);
    
    int **B11 = allocate_matrix(half);
    int **B12 = allocate_matrix(half);
    int **B21 = allocate_matrix(half);
    int **B22 = allocate_matrix(half);
    
    int **C11 = allocate_matrix(half);
    int **C12 = allocate_matrix(half);
    int **C21 = allocate_matrix(half);
    int **C22 = allocate_matrix(half);
    
    int **temp1 = allocate_matrix(half);
    int **temp2 = allocate_matrix(half);
    
    // Divide matrices into quadrants
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }
    
    // C11 = A11*B11 + A12*B21
    recursive_matrix_multiply(A11, B11, temp1, half);
    recursive_matrix_multiply(A12, B21, temp2, half);
    matrix_add(temp1, temp2, C11, half);
    
    // C12 = A11*B12 + A12*B22
    recursive_matrix_multiply(A11, B12, temp1, half);
    recursive_matrix_multiply(A12, B22, temp2, half);
    matrix_add(temp1, temp2, C12, half);
    
    // C21 = A21*B11 + A22*B21
    recursive_matrix_multiply(A21, B11, temp1, half);
    recursive_matrix_multiply(A22, B21, temp2, half);
    matrix_add(temp1, temp2, C21, half);
    
    // C22 = A21*B12 + A22*B22
    recursive_matrix_multiply(A21, B12, temp1, half);
    recursive_matrix_multiply(A22, B22, temp2, half);
    matrix_add(temp1, temp2, C22, half);
    
    // Combine results
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }
    
    // Free memory
    free_matrix(A11, half); free_matrix(A12, half); free_matrix(A21, half); free_matrix(A22, half);
    free_matrix(B11, half); free_matrix(B12, half); free_matrix(B21, half); free_matrix(B22, half);
    free_matrix(C11, half); free_matrix(C12, half); free_matrix(C21, half); free_matrix(C22, half);
    free_matrix(temp1, half); free_matrix(temp2, half);
}

void initialize_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;
    
    srand(time(NULL));
    
    for (n = 64; n <= 512; n *= 2) {
        int **A = allocate_matrix(n);
        int **B = allocate_matrix(n);
        int **C = allocate_matrix(n);
        
        initialize_matrix(A, n);
        initialize_matrix(B, n);
        
        start = clock();
        recursive_matrix_multiply(A, B, C, n);
        end = clock();
        
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d %f\n", n, cpu_time_used);
        
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }
    return 0;
}

