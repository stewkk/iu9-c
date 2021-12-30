
#include <stdio.h>
#include <inttypes.h>

const size_t MAX_N = 24;

char is_power2(int n) {
    if (n <= 0) {
        return 0;
    }
    char flag = 0;
    uint32_t mask = 1;
    while (mask) {
        if (mask & n) {
            if (flag) {
                return 0;
            } else {
                flag = 1;
            }
        }
        mask <<= 1;
    }
    return 1;
}

void gen(size_t index, int sum, size_t n, int* arr, int* ans) {
    if (is_power2(sum)) {
        (*ans)++;
    }
    if (index + 1 == n) {
        return;
    }
    for (size_t i = index + 1; i < n; ++i) {
        gen(i, sum + arr[i], n, arr, ans);
    }
}

int main() {
    size_t n;
    scanf("%zu", &n);
    int arr[MAX_N];
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    int ans = 0;
    for (size_t i = 0; i < n; ++i) {
        gen(i, arr[i], n, arr, &ans);
    }
    printf("%d\n", ans);
    return 0;
}
