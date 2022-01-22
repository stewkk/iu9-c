
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000001

int max(int a, int b) {
    return a > b ? a : b;
}

void build(int* t, int* arr, int i, int l, int r) {
    if (l + 1 == r) {
        t[i] = arr[l];
        return;
    }
    int m = (l + r) / 2;
    build(t, arr, i * 2 + 1, l, m);
    build(t, arr, i * 2 + 2, m, r);
    t[i] = max(t[i * 2 + 1], t[i * 2 + 2]);
}

int* segtree_make(int* arr, int n) {
    int* tree = malloc((size_t)n * 4 * sizeof(int));
    build(tree, arr, 0, 0, n);
    return tree;
}

void update(int* t, int* arr, int qi, int i, int l, int r) {
    if (l + 1 == r) {
        t[i] = arr[l];
        return;
    }
    int m = (l + r) / 2;
    if (qi < m) {
        update(t, arr, qi, i * 2 + 1, l, m);
    } else {
        update(t, arr, qi, i * 2 + 2, m, r);
    }
    t[i] = max(t[i * 2 + 1], t[i * 2 + 2]);
}

void segtree_update(int* t, int* arr, int n, int i, int v) {
    arr[i] = v;
    update(t, arr, i, 0, 0, n);
}

int query(int* t, int i, int l, int r, int ql, int qr) {
    if (ql >= r || qr <= l) {
        return -INF;
    }
    if (l >= ql && r <= qr) {
        return t[i];
    }
    int m = (l + r) / 2;
    return max(query(t, i * 2 + 1, l, m, ql, qr),
               query(t, i * 2 + 2, m, r, ql, qr));
}

int segtree_query(int* t, int l, int r, int n) {
    return query(t, 0, 0, n, l, r + 1);
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    int* t = segtree_make(arr, n);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        char* op;
        scanf("%ms", &op);
        if (strcmp(op, "MAX") == 0) {
            int l;
            int r;
            scanf("%d%d", &l, &r);
            printf("%d\n", segtree_query(t, l, r, n));
        } else if (strcmp(op, "UPD") == 0) {
            int ind;
            int v;
            scanf("%d%d", &ind, &v);
            segtree_update(t, arr, n, ind, v);
        }
        free(op);
    }
    free(arr);
    free(t);
    return 0;
}
