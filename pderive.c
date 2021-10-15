
#include <stdio.h>

int main() {
    long n, k, x;
    scanf("%ld%ld%ld", &n, &k, &x);
    long sz = n - k + 1;
    long ans;
    scanf("%ld", &ans);
    for (long m = n; m > n - k; --m) {
        ans *= m;
    }
    for (long i = 1; i < sz; ++i) {
        long mult;
        scanf("%ld", &mult);
        for (long m = n - i; m > n - k - i; --m) {
            mult *= m;
        }
        ans *= x;
        ans += mult;
    }
    printf("%ld\n", ans);
    return 0;
}
