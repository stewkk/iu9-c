
#include <stdio.h>

unsigned long multiply_by_modulo(unsigned long a, unsigned long b, unsigned long m) {
    unsigned long ans = 0;
    for (unsigned long long mask = 1lu << 63; mask > 0; mask >>= 1) {
        ans = ans * 2 % m + (mask & a ? 1lu : 0lu) * (b % m);
        ans %= m;
    }
    return ans;
}

int main() {
    unsigned long a, b, m;
    scanf("%lu%lu%lu", &a, &b, &m);
    unsigned long ans = multiply_by_modulo(a, b, m);
    printf("%lu", ans);
    return 0;
}
