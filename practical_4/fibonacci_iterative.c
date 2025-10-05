#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long fibonacci_iterative(int n) {
    if (n <= 1)
        return n;
    
    long long prev1 = 0, prev2 = 1, current;
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev1 = prev2;
        prev2 = current;
    }
    return prev2;
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;
    long long result;
    
    printf("Iterative Fibonacci Results:\n");
    printf("n\tTime(seconds)\tResult\n");
    
    for (n = 10; n <= 1000; n += 100) {
        start = clock();
        result = fibonacci_iterative(n);
        end = clock();
        
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t%f\t%lld\n", n, cpu_time_used, result);
        
        FILE *fp = fopen("iterative.txt", "a");
        fprintf(fp, "%d %f\n", n, cpu_time_used);
        fclose(fp);
    }
    return 0;
}
