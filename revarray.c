
#include <stdio.h>
#include <stdint.h>

void swap(uint8_t* a, uint8_t* b) {
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}

void revarray(void* base, size_t nel, size_t width) {
    uint8_t* left = base;
    uint8_t* right = (uint8_t*)base + (nel - 1) * width;
    while (left < right) {
        swap(left, right);
        left++;
        right--;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    revarray(arr, 10, sizeof(int));
    for (size_t i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
