
#include <stdio.h>

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) {
    unsigned long l = 0;
    unsigned long r = nel;
    while (l + 1 < r) {
        unsigned long m = (l + r) / 2;
        if (compare(m) < 0) {
            r = m;
        } else {
            l = m;
        }
    }
    return l;
}

int arr[7] = {1, 2, 3, 4, 5, 7, 10};
int x = 7;

int cmp(unsigned long i) {
    if (x < arr[i]) {
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
