#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Item {
    int value;
    int weight;
};

int compareItems(const void* a, const void* b) {
    struct Item* itemA = (struct Item*)a;
    struct Item* itemB = (struct Item*)b;
    double r1 = (double)itemA->value / itemA->weight;
    double r2 = (double)itemB->value / itemB->weight;
    if (r1 < r2) return 1;
    if (r1 > r2) return -1;
    return 0;
}

double fractional_knapsack(struct Item* items, int n, int capacity) {
    qsort(items, n, sizeof(struct Item), compareItems);

    double total_value = 0.0;
    int current_weight = 0;

    for (int i = 0; i < n; i++) {
        if (current_weight + items[i].weight <= capacity) {
            current_weight += items[i].weight;
            total_value += items[i].value;
        } else {
            int remaining_capacity = capacity - current_weight;
            total_value += items[i].value * ((double)remaining_capacity / items[i].weight);
            break;
        }
    }
    return total_value;
}

int main() {
    int capacity = 1000;
    FILE *outfile = fopen("fractional_knapsack.txt", "w");

    printf("Fractional Knapsack (Greedy) Results (Capacity = %d):\n", capacity);
    printf("Items(n)\tTime(microseconds)\tResult\n");

    for (int n = 100; n <= 2000; n += 100) {
        struct Item* items = (struct Item*)malloc(n * sizeof(struct Item));
        for (int i = 0; i < n; ++i) {
            items[i].value = rand() % 100 + 1;
            items[i].weight = rand() % 50 + 1;
        }

        clock_t start = clock();
        double result = fractional_knapsack(items, n, capacity);
        clock_t end = clock();
        long long duration = (long long)(((double)(end - start)) * 1000000 / CLOCKS_PER_SEC);

        printf("%d\t\t%lld\t\t\t%.2f\n", n, duration, result);
        fprintf(outfile, "%d %lld\n", n, duration);
        free(items);
    }
    fclose(outfile);
    return 0;
}

