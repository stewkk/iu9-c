
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int gcd(int a, int b) {
    if (a == 0) {
        return 0;
    }
    while (b != 0) {
        a %= b;
        swap(&a, &b);
    }
    return a;
}

int log2i(int a) {
    return 31 - __builtin_clz((unsigned int)a);
}

int query(int** st, int l, int r) {
    int t = log2i(r - l);
    return gcd(st[t][l], st[t][r - (1 << t)]);
}

int main() {
    size_t n;
    scanf("%zu", &n);
    int logn = log2i((int)n) + 1;
    int** st = malloc((size_t)logn * sizeof(int*));
    for (int i = 0; i < logn; ++i) {
        st[i] = malloc(n * sizeof(int));
    }
    for (size_t i = 0; i < n; ++i) {
        int num;
        scanf("%d", &num);
        st[0][i] = abs(num);
    }
    for (int l = 0; l < logn - 1; ++l) {
        for (int i = 0; i + (2 << l) <= (int)n; ++i) {
            st[l + 1][i] = gcd(st[l][i], st[l][i + (1 << l)]);
        }
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int l;
        int r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(st, l, r + 1));
    }
    for (int i = 0; i < logn; ++i) {
        free(st[i]);
    }
    free(st);
    return 0;
}
