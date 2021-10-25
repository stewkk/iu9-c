
#include <stdio.h>
#include <stdlib.h>

long long gorner(int n, long long* a, long long x) {
    long long ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans = ans * x + a[i];
    }
    return ans;
}

long long gorner_from_derivative(int n, long long* a, long long x) {
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = ans * x + a[i] * (n - i);
    }
    return ans;
}

int main() {
    int n;
    long long x;
    scanf("%d%lld", &n, &x);
    long long* a = malloc((n + 1) * (sizeof(long long)));
    for (int i = 0; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    long long ans = gorner(n, a, x);
    long long ans_derived = gorner_from_derivative(n, a, x);
    printf("%lld\n%lld\n", ans, ans_derived);
    free(a);
    return 0;
}
