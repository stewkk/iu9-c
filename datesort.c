
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

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

typedef struct {
    int Day;
    int Month;
    int Year;
} Date;

int get_key(void* entry, int q) {
    Date* date = (Date*)entry;
    if (q == 2) {
        return date->Day - 1;
    }
    if (q == 1) {
        return date->Month - 1;
    }
    return date->Year - 1970;
}

int main() {
    size_t n;
    scanf("%zu", &n);
    Date* arr = calloc(n, sizeof(Date));
    for (size_t i = 0; i < n; ++i) {
        scanf("%d%d%d", &arr[i].Year,
              &arr[i].Month,
              &arr[i].Day);
    }
    int bases[3] = {60, 11, 30};
    arr = radixsort(arr, sizeof(Date), n, 3, bases, get_key);
    for (size_t i = 0; i < n; ++i) {
        printf("%d %02d %02d\n", arr[i].Year, arr[i].Month, arr[i].Day);
    }
    free(arr);
    return 0;
}
