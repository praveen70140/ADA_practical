#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long fibonacci_recursive(int n) {
    if (n <= 1)
        return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;
    long long result;
    
    printf("Recursive Fibonacci Results:\n");
    printf("n\tTime(seconds)\tResult\n");
    
    for (n = 10; n <= 45; n += 5) {
        start = clock();
        result = fibonacci_recursive(n);
        end = clock();
        
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t%f\t%lld\n", n, cpu_time_used, result);
        
        FILE *fp = fopen("recursive.txt", "a");
        fprintf(fp, "%d %f\n", n, cpu_time_used);
        fclose(fp);
    }
    return 0;
}
