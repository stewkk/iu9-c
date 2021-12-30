
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

inline void* get_pointer(void* base, size_t width, size_t i) {
    return (char*)base + width * i;
}

void merge(void* base, size_t width,
           size_t l, size_t m, size_t r,
           int (*compare)(void* a, void* b)) {
    size_t buf_sz = r - l;
    uint8_t* buf = calloc(buf_sz, width);
    size_t i = l;
    size_t j = m;
    for (size_t buf_index = 0; buf_index < buf_sz; ++buf_index) {
        uint8_t* i_p = get_pointer(base, width, i);
        uint8_t* j_p = get_pointer(base, width, j);
        uint8_t* buf_index_p = get_pointer(buf, width, buf_index);
        if (j < r && (i == m || compare(j_p, i_p) < 0)) {
            memcpy(buf_index_p, j_p, width);
            j++;
        } else {
            memcpy(buf_index_p, i_p, width);
            i++;
        }
    }
    memcpy(get_pointer(base, width, l), buf, buf_sz * width);
    free(buf);
}

void mergesort_rec(void* base, size_t width,
                   size_t l, size_t r,
                   int (*compare)(void* a, void* b)) {
    if (l + 1 < r) {
        size_t m = (l + r) / 2;
        mergesort_rec(base, width, l, m, compare);
        mergesort_rec(base, width, m, r, compare);
        merge(base, width, l, m, r, compare);
    }
}

void mergesort(void* base, size_t width, size_t n,
               int (*compare)(void* a, void* b)) {
    mergesort_rec(base, width, 0, n, compare);
}

int compare(void* a, void* b) {
    int first = abs(*(int*)a);
    int second = abs(*(int*)b);
    if (first < second) {
        return -1;
    }
    if (first == second) {
        return 0;
    }
    return 1;
}

int main() {
    size_t n;
    scanf("%zu", &n);
    int* arr = calloc(n, sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    mergesort(arr, sizeof(int), n, compare);
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
