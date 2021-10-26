
#include <stdio.h>

const size_t FIB_SIZE = 94;

void ull_to_fib(unsigned long long x, char* x_fib) {
    if (x == 0) {
        x_fib[0] = '0';
        x_fib[1] = '\0';
        return;
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
    x -= fib[index];
    index--;
    x_fib[0] = '1';
    for (; index >= 0; index--) {
        if (fib[index] <= x) {
            x -= fib[index];
            x_fib[max_index - index] = '1';
        } else {
            x_fib[max_index - index] = '0';
        }
    }
    x_fib[max_index + 1] = '\0';
}

int main() {
    unsigned long long x;
    scanf("%llu", &x);
    char ans[FIB_SIZE];
    ull_to_fib(x, ans);
    printf("%s\n", ans);
    return 0;
}
