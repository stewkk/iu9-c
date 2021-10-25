
#include <stdio.h>
#include <stdlib.h>

long gorner(int n, long* a, long x) {
    long ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans = ans * x + a[i];
    }
    return ans;
}

long gorner_from_derivative(int n, long* a, long x) {
    long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = ans * x + a[i] * (n - i);
    }
    return ans;
}

int main() {
    int n;
    long x;
    scanf("%d%ld", &n, &x);
    long* a = malloc((n + 1) * (sizeof(long)));
    for (int i = 0; i <= n; ++i) {
        scanf("%ld", &a[i]);
    }
    long ans = gorner(n, a, x);
    long ans_derived = gorner_from_derivative(n, a, x);
    printf("%ld\n%ld\n", ans, ans_derived);
    free(a);
    return 0;
}
