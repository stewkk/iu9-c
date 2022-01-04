
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int query(int* t, int i) {
    int res = 0;
    while (i > 0) {
        res += t[i];
        i -= i & -i;
    }
    return res;
}

int tree_query(int* t, int l, int r) {
    return query(t, r) - query(t, l - 1);
}

void tree_update(int* t, int n, int i, int delta) {
    while (i <= n) {
        t[i] += delta;
        i += i & -i;
    }
}

int* tree_make(int n, char* arr) {
    int* tree = calloc((size_t)(n + 1), sizeof(int));
    for (int i = 0; i < n; ++i) {
        tree_update(tree, n, i + 1, arr[i]);
    }
    return tree;
}

void check_for_peak(int ind, char* peak, int n, int* t, int* arr) {
    if (ind < 0) {
        return;
    }
    if (ind >= n) {
        return;
    }
    int old = peak[ind];
    if ((ind == 0 || arr[ind - 1] <= arr[ind]) &&
        (ind == n - 1 || arr[ind + 1] <= arr[ind])) {
        peak[ind] = 1;
    } else {
        peak[ind] = 0;
    }
    int delta = peak[ind] - old;
    if (delta) {
        tree_update(t, n, ind + 1, delta);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr = malloc((size_t)n * sizeof(int));
    char* peak = calloc((size_t)n, sizeof(char));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; ++i) {
        if ((i == 0 || arr[i - 1] <= arr[i]) && (i == n - 1 || arr[i + 1] <= arr[i])) {
            peak[i] = 1;
        }
    }
    int* t = tree_make(n, peak);
    int m;
    for (int i = 0; i < n; ++i) {
        printf("%d ", peak[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        char* op;
        scanf("%ms", &op);
        if (!strcmp(op, "PEAK")) {
            int l;
            int r;
            scanf("%d%d", &l, &r);
            printf("%d\n", tree_query(t, l + 1, r + 1));
        } else if (!strcmp(op, "UPD")) {
            int ind;
            int v;
            scanf("%d%d", &ind, &v);
            arr[ind] = v;
            check_for_peak(ind, peak, n, t, arr);
            check_for_peak(ind - 1, peak, n, t, arr);
            check_for_peak(ind + 1, peak, n, t, arr);
        }
        free(op);
    }
    free(arr);
    free(t);
    free(peak);
    return 0;
}
