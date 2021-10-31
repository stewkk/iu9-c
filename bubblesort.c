
#include <stdio.h>

void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)) {
    if (!nel) {
        return;
    }
    unsigned long l = 0;
    unsigned long r = nel - 1;
    for (unsigned long i = 0; i < nel - 1; ++i) {
        if (i % 2 == 0) {
            for (unsigned long j = l; j < r; ++j) {
                if (compare(j, j + 1) < 0) {
                    swap(j, j + 1);
                }
            }
            r--;
        } else {
            for (unsigned long j = r; j > l; --j) {
                if (compare(j - 1, j) < 0) {
                    swap(j - 1, j);
                }
            }
            l++;
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
    bubblesort(ARR_SZ, compare, swap);
    for (size_t i = 0; i < ARR_SZ; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
