#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Item {
    int value;
    int weight;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack_01(const struct Item* items, int n, int capacity) {
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)calloc(capacity + 1, sizeof(int));
    }

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(
                    items[i - 1].value + dp[i - 1][w - items[i - 1].weight],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    int result = dp[n][capacity];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int capacity = 1000;
    FILE *outfile = fopen("01_knapsack.txt", "w");

    printf("0/1 Knapsack (DP) Results (Capacity = %d):\n", capacity);
    printf("Items(n)\tTime(microseconds)\tResult\n");

    for (int n = 100; n <= 2000; n += 100) {
        struct Item* items = (struct Item*)malloc(n * sizeof(struct Item));
        for (int i = 0; i < n; ++i) {
            items[i].value = rand() % 100 + 1;
            items[i].weight = rand() % 50 + 1;
        }

        clock_t start = clock();
        int result = knapsack_01(items, n, capacity);
        clock_t end = clock();
        long long duration = (long long)(((double)(end - start)) * 1000000 / CLOCKS_PER_SEC);

        printf("%d\t\t%lld\t\t\t%d\n", n, duration, result);
        fprintf(outfile, "%d %lld\n", n, duration);
        free(items);
    }
    fclose(outfile);
    return 0;
}

