
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

const int N = 8;
const int INF = INT_MAX;

bool is_permutation(int* a, int* b) {
    for (int i = 0; i < N; ++i) {
        int el = a[i];
        bool is_found = false;
        for (int j = 0; j < N; ++j) {
            if (el == b[j]) {
                b[j] = INF;
                is_found = true;
                break;
            }
        }
        if (!is_found) {
            return false;
        }
    }
    return true;
}

int main() {
    int a[N];
    int b[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", &b[i]);
    }
    if (is_permutation(a, b)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
    return 0;
}
