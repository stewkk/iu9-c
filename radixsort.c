
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void* dsort(void* base, size_t width, size_t n, int q, int q_base,
            int (*get_key)(void* entry, int q)) {
    int count[q_base];
    memset(count, 0, (size_t)q_base * sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        int key = get_key((uint8_t*)base + i * width, q);
        count[key]++;
    }
    for (int i = 1; i < q_base; ++i) {
        count[i] += count[i - 1];
    }
    uint8_t* ans = calloc(n, width);
    for (size_t i = n; i > 0; --i) {
        int key = get_key((uint8_t*)base + (i - 1) * width, q);
        count[key]--;
        int sorted_index = count[key];
        memcpy(ans + (size_t)sorted_index * width,
               (uint8_t*)base + (i - 1) * width,
               width);
    }
    free(base);
    return ans;
}

void* radixsort(void* base, size_t width, size_t n, int q_count, int* q_base,
                int (*get_key)(void* entry, int q)) {
    void* ans = base;
    for (int i = q_count - 1; i >= 0; --i) {
        ans = dsort(ans, width, n, i, q_base[i], get_key);
    }
    return ans;
}

union Int32 {
    int32_t x;
    uint8_t bytes[4];
};

int get_key(void* entry, int q) {
    union Int32* n = entry;
    q = 3 - q;
    if (q == 3) {
        return (int)(n->bytes[q] ^ 0x80);
    }
    return n->bytes[q];
}

int main() {
    size_t n;
    scanf("%zu", &n);
    int32_t* arr = calloc(n, sizeof(int32_t));
    for (size_t i = 0; i < n; ++i) {
        scanf("%"SCNd32, &arr[i]);
    }
    int bases[4] = {256, 256, 256, 256};
    arr = radixsort(arr, sizeof(int), n, 4, bases, get_key);
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
