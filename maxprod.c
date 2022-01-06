
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-6

typedef struct {
    size_t first;
    size_t second;
} pair_t;

pair_t maxprod(size_t n, int* a, int* b) {
    long double prod = 1;
    long double max = 0;
    size_t l = 0;
    size_t r = 0;
    size_t start = 0;
    for (size_t i = 0; i < n; ++i) {
        prod *= a[i];
        prod /= b[i];
        if (prod - max > EPS) {
            max = prod;
            l = start;
            r = i;
        }
        if (fabsl(prod) < EPS) {
            start = i + 1;
            prod = 1;
        }
    }
    pair_t ans;
    ans.first = l;
    ans.second = r;
    return ans;
}

int main() {
    size_t n;
    scanf("%zu", &n);
    int* a = malloc(n * sizeof(int));
    int* b = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        char temp[2];
        scanf("%d%s%d", &a[i], temp, &b[i]);
    }
    pair_t ans = maxprod(n, a, b);
    printf("%zu %zu\n", ans.first, ans.second);
    free(a);
    free(b);
    return 0;
}
