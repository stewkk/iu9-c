
#include <stdio.h>
#include <inttypes.h>

const size_t MAX_N = 24;

char is_power2(int n) {
    return (n & (n - 1)) == 0;
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
