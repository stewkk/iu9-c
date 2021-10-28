
#include <stdio.h>
#include <inttypes.h>

size_t maxarray(void* base, size_t nel, size_t width,
             int (*compare)(void* a, void* b)) {
    size_t ans = 0;
    void* max = base;
    uint8_t* cur = base;
    for (size_t i = 1; i < nel; ++i) {
        cur += width;
        if (compare(cur, max) > 0) {
            ans = i;
            max = cur;
        }
    }
    return ans;
}

int cmp(void* a, void* b) {
    int a_int = *(int*)a;
    int b_int = *(int*)b;
    if (a_int == b_int) {
        return 0;
    }
    if (a_int > b_int) {
        return 1;
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 4, 2, 3}; // 5
    size_t ans = maxarray(arr, 8, sizeof(int), cmp);
    printf("%zu\n", ans);
    return 0;
}
