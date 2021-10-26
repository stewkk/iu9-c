
#include <stdio.h>
#include <stdlib.h>

const size_t FIB_SIZE = 94;

char* ull_to_fib(unsigned long long x) {
    if (x == 0) {
        char* ans = malloc(2 * sizeof(char));
        ans[0] = '0';
        ans[1] = '\0';
        return ans;
    }
    unsigned long long fib[FIB_SIZE];
    fib[0] = 1;
    fib[1] = 2;
    for (size_t i = 2; i < FIB_SIZE; ++i) {
        fib[i] = fib[i - 2] + fib[i - 1];
    }
    int index = 0;
    while (fib[index + 1] <= x) {
        index++;
    }
    int max_index = index;
    char* ans = malloc((size_t)(max_index + 2) * sizeof(char));
    x -= fib[index];
    index--;
    ans[0] = '1';
    for (; index >= 0; index--) {
        if (fib[index] <= x) {
            x -= fib[index];
            ans[max_index - index] = '1';
        } else {
            ans[max_index - index] = '0';
        }
    }
    ans[max_index + 1] = '\0';
    return ans;
}

int main() {
    unsigned long long x;
    scanf("%llu", &x);
    char* ans = ull_to_fib(x);
    printf("%s\n", ans);
    free(ans);
    return 0;
}
