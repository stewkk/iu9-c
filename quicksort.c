
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int* arr, size_t i, size_t j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
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

void heapify(int* base, size_t i, size_t n) {
    while (1) {
        size_t l = 2 * i + 1;
        size_t r = l + 1;
        size_t top = i;
        if (l < n && base[i] < base[l]) {
            i = l;
        }
        if (r < n && base[i] < base[r]) {
            i = r;
        }
        if (i == top) {
            break;
        }
        swap(base, i, top);
    }
}

void build_heap(int* base, size_t n) {
    for (size_t i = n / 2; i > 0; --i) {
        heapify(base, i - 1, n);
    }
}

void heapsort(int* base, size_t n) {
    if (n < 2) {
        return;
    }
    build_heap(base, n);
    for (size_t i = n - 1; i > 0; --i) {
        swap(base, 0, i);
        heapify(base, 0, i);
    }
}

size_t partition(int* arr, size_t l, size_t r) {
    int pivot = arr[r - 1];
    size_t i = l;
    for (size_t j = l; j < r - 1; ++j) {
        if (arr[j] < pivot) {
            swap(arr, i, j);
            ++i;
        }
    }
    swap(arr, i, r - 1);
    return i;
}

void quicksort_rec(int* arr, size_t l, size_t r, size_t selection_sort_sz, int depth) {
    if (l + 1 >= r) {
        return;
    }
    if (r - l < selection_sort_sz) {
        selectsort(arr + l, r - l);
        return;
    }
    if (!depth) {
        heapsort(arr + l, r - l);
        return;
    }
    size_t m = partition(arr, l, r);
    quicksort_rec(arr, l, m, selection_sort_sz, depth - 1);
    quicksort_rec(arr, m + 1, r, selection_sort_sz, depth - 1);
}

void quicksort(int* arr, size_t n, size_t selection_sort_sz) {
    quicksort_rec(arr, 0, n, selection_sort_sz, log10(n));
}

int main() {
    size_t n;
    scanf("%zu", &n);
    size_t m;
    scanf("%zu", &m);
    int* arr = calloc(n, sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    quicksort(arr, n, m);
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
