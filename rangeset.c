
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    long l, r;
    scanf("%ld%ld", &l, &r);
    for (int i = 1; i < n; ++i) {
        long new_l, new_r;
        scanf("%ld%ld", &new_l, &new_r);
        if (new_l > r + 1) {
            printf("%ld %ld\n", l, r);
            l = new_l;
            r = new_r;
        } else if (new_r > r) {
            r = new_r;
        }
    }
    printf("%ld %ld\n", l, r);
    return 0;
}
