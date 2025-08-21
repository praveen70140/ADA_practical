#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binary_search(int arr[], int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int n, key, pos;
    clock_t start, end;
    double cpu_time_used;

    // Experiment for increasing n
    for (n = 1000; n <= 50000; n += 5000) {
        int *arr = (int*)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) arr[i] = i;

        key = n - 1;
        start = clock();
        pos = binary_search(arr, n, key);
        end = clock();

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%d %f\n", n, cpu_time_used);  
       free(arr);
    }
    return 0;
}

