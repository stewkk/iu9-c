
#include <stdio.h>

#define MAX_FIB_SZ 40

size_t calc_fib(long n, long* fib) {
    fib[0] = 1;
    fib[1] = 2;
    size_t index = 1;
    long next;
    while ((next = fib[index - 1] + fib[index]) < n) {
        index++;
        fib[index] = next;
    }
    return index + 1;
}

void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)) {
    long fib[MAX_FIB_SZ];
    size_t sz = calc_fib(nel, fib);
    for (long d_index = sz - 1; d_index >= 0; --d_index) {
        long d = fib[d_index];
        for (long i = d; i < nel; ++i) {
            for (long loc = i - d;
                    loc >= 0 && compare(loc + d, loc) > 0; loc -= d) {
                swap(loc + d, loc);
            }
        }
    }
}

int arr[] = {2, 3, 10, 5, 9, 1, 4};
const size_t ARR_SZ = sizeof(arr) / sizeof(arr[0]);

int compare(unsigned long i, unsigned long j) {
    if (arr[i] == arr[j]) {
        return 0;
    }
    if (arr[i] < arr[j]) {
        return 1;
    }
    return -1;
}

void swap(unsigned long i, unsigned long j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int main() {
    shellsort(ARR_SZ, compare, swap);
    for (size_t i = 0; i < ARR_SZ; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
