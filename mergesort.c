
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

inline void swap(int* base, size_t i, size_t j) {
    int temp = base[i];
    base[i] = base[j];
    base[j] = temp;
}

void selectsort(int* base, size_t n) {
    for (size_t j = n - 1; j > 0; --j) {
        size_t mx = 0;
        for (size_t i = 1; i <= j; ++i) {
            if (base[i] >= base[mx]) {
                mx = i;
            }
        }
        swap(base, mx, j);
    }
}

void merge(int* base, size_t l, size_t m, size_t r) {
    size_t buf_sz = r - l;
    int* buf = calloc(buf_sz, sizeof(int));
    size_t i = l;
    size_t j = m;
    for (size_t buf_index = 0; buf_index < buf_sz; ++buf_index) {
        if (j < r && (i == m || base[j] < base[i])) {
            buf[buf_index] = base[j];
            j++;
        } else {
            buf[buf_index] = base[i];
            i++;
        }
    }
    memcpy(base + l, buf, buf_sz * sizeof(int));
    free(buf);
}

void mergesort_rec(int* base, size_t l, size_t r) {
    size_t len = r - l;
    if (len > 5) {
        size_t m = (l + r) / 2;
        mergesort_rec(base, l, m);
        mergesort_rec(base, m, r);
        merge(base, l, m, r);
    }
    if (len > 1) {
        selectsort(base + l, r - l);
    }
}

void mergesort(int* base, size_t n) {
    mergesort_rec(base, 0, n);
}

int main() {
    size_t n;
    scanf("%zu", &n);
    int* arr = calloc(n, sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    mergesort(arr, n);
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
