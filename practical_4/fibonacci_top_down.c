#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long fibonacci_memoization_helper(int n, long long *memo) {
    if (n <= 1)
        return n;
    if (memo[n] != -1)
        return memo[n];
    memo[n] = fibonacci_memoization_helper(n-1, memo) +
              fibonacci_memoization_helper(n-2, memo);
    return memo[n];
}

long long fibonacci_top_down(int n) {
    if (n <= 1) return n;
    long long *memo = malloc((n+1)*sizeof(long long));
    for (int i=0;i<=n;i++) memo[i] = -1;
    long long result = fibonacci_memoization_helper(n, memo);
    free(memo);
    return result;
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;
    long long result;

    printf("Top-Down DP Fibonacci Results:\n");
    printf("n\tTime(seconds)\tResult\n");

    for (n = 10; n <= 1000; n += 100) {
        start = clock();
        result = fibonacci_top_down(n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t%f\t%lld\n", n, cpu_time_used, result);
        FILE *fp = fopen("top_down.txt", "a");
        fprintf(fp, "%d %f\n", n, cpu_time_used);
        fclose(fp);
    }
    return 0;
}
