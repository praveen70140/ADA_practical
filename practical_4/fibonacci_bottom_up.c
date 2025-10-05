#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long fibonacci_bottom_up(int n) {
    if (n <= 1)
        return n;
    long long *dp = malloc((n+1)*sizeof(long long));
    dp[0] = 0; dp[1] = 1;
    for (int i=2; i<=n; i++) dp[i] = dp[i-1] + dp[i-2];
    long long result = dp[n];
    free(dp);
    return result;
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;
    long long result;
    
    printf("Bottom-Up DP Fibonacci Results:\n");
    printf("n\tTime(seconds)\tResult\n");
    
    for (n = 10; n <= 1000; n += 100) {
        start = clock();
        result = fibonacci_bottom_up(n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t%f\t%lld\n", n, cpu_time_used, result);
        FILE *fp = fopen("bottom_up.txt", "a");
        fprintf(fp, "%d %f\n", n, cpu_time_used);
        fclose(fp);
    }
    return 0;
}
