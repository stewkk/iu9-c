
#include <stdio.h>

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) {
    unsigned long l = 0;
    unsigned long r = nel;
    while (l + 1 < r) {
        unsigned long m = (l + r) / 2;
        int res = compare(m);
        if (!res) {
            return m;
        }
        if (res < 0) {
            l = m;
        } else {
            r = m;
        }
    }
    if (compare(l) == 0) {
        return l;
    }
    return nel;
}

int arr[7] = {1, 2, 3, 4, 5, 7, 10};
int x = 11;

int cmp(unsigned long i) {
    if (arr[i] < x) {
        return -1;
    }
    if (x == arr[i]) {
        return 0;
    }
    return 1;
}

int main() {
    unsigned long ans = binsearch(7, cmp);
    printf("%lu\n", ans);
    return 0;
}
