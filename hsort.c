
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

void* get_pointer(void* base, size_t width, size_t i);

inline void* get_pointer(void* base, size_t width, size_t i) {
    return (char*)base + width * i;
}

void swap(void* base, size_t width, size_t a, size_t b) {
    uint8_t* first = get_pointer(base, width, a);
    uint8_t* second = get_pointer(base, width, b);
    for (size_t i = 0; i < width; ++i) {
        uint8_t temp = *first;
        *first = *second;
        *second = temp;
        first++;
        second++;
    }
}

void heapify(void* base, size_t width, size_t i, size_t n,
             int (*compare)(const void* a, const void* b)) {
    while (1) {
        size_t l = 2 * i + 1;
        size_t r = l + 1;
        size_t top = i;
        if (l < n && compare(get_pointer(base, width, i),
                             get_pointer(base, width, l)) < 0) {
            i = l;
        }
        if (r < n && compare(get_pointer(base, width, i),
                             get_pointer(base, width, r)) < 0) {
            i = r;
        }
        if (i == top) {
            break;
        }
        swap(base, width, i, top);
    }
}

void build_heap(void* base, size_t width, size_t n,
                int (*compare)(const void* a, const void* b)) {
    for (size_t i = n / 2; i > 0; --i) {
        heapify(base, width, i - 1, n, compare);
    }
}

void hsort(void* base, size_t nel, size_t width,
           int (*compare)(const void* a, const void* b)) {
    if (nel < 2) {
        return;
    }
    build_heap(base, width, nel, compare);
    for (size_t i = nel - 1; i > 0; --i) {
        swap(base, width, 0, i);
        heapify(base, width, 0, i, compare);
    }
}

typedef struct {
    char* str;
    unsigned long a_count;
} mystring_t;

unsigned long calc_a_count(char* str) {
    unsigned long ans = 0;
    while (*str != '\0') {
        if (*str == 'a') {
            ans++;
        }
        str++;
    }
    return ans;
}

int compare_mystring(const void* a, const void* b) {
    unsigned long l = ((const mystring_t*)a)->a_count;
    unsigned long r = ((const mystring_t*)b)->a_count;
    if (l < r) {
        return -1;
    }
    if (l == r) {
        return 0;
    }
    return 1;
}

int main() {
    size_t n;
    scanf("%zu", &n);
    mystring_t* arr = calloc(n, sizeof(mystring_t));
    for (size_t i = 0; i < n; ++i) {
        scanf("%ms", &arr[i].str);
        arr[i].a_count = calc_a_count(arr[i].str);
    }
    hsort(arr, n, sizeof(mystring_t), compare_mystring);
    for (size_t i = 0; i < n; ++i) {
        puts(arr[i].str);
        free(arr[i].str);
    }
    free(arr);
    return 0;
}
