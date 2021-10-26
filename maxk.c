
#include <stdio.h>
#include <stdlib.h>

long long maxksum(size_t n, int* arr, size_t k) {
    long long max_sum = 0;
    for (size_t i = 0; i < k; ++i) {
        max_sum += arr[i];
    }
    long long cur_sum = max_sum;
    for (size_t i = 0; i < n - k; ++i) {
        cur_sum -= arr[i];
        cur_sum += arr[i + k];
        if (cur_sum > max_sum) {
            max_sum = cur_sum;
        }
    }
    return max_sum;
}

int main() {
    size_t n;
    scanf("%zu", &n);
    int* arr = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    size_t k;
    scanf("%zu", &k);
    long long ans = maxksum(n, arr, k);
    printf("%lld\n", ans);
    free(arr);
    return 0;
}
