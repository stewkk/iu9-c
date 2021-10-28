
#include <stdio.h>

unsigned long peak(unsigned long nel,
                   int (*less)(unsigned long i, unsigned long j)) {
    if (nel == 1) {
        return 0;
    }
    if (!less(0, 1)) {
        return 0;
    }
    for (unsigned int i = 1; i < nel - 1; ++i) {
        if (!less(i, i - 1) && !less(i, i + 1)) {
            return i;
        }
    }
    return nel - 1;
}

int arr[7] = {1, 2, 3, 4, 5, 10, 7};

int less(unsigned long i, unsigned long j) {
    if (arr[i] < arr[j]) {
        return 1;
    }
    return 0;
}

int main() {
    unsigned long ans = peak(7, less);
    printf("%lu\n", ans);
    return 0;
}
