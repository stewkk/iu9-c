
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001

int query(int* t, int i) {
    int res = 0;
    while (i > 0) {
        res ^= t[i];
        i -= i & -i;
    }
    return res;
}

int tree_query(int* t, int l, int r) {
    return query(t, r) ^ query(t, l - 1);
}

void tree_update(int* t, int n, int i, int delta) {
    while (i <= n) {
        t[i] ^= delta;
        i += i & -i;
    }
}

int* tree_make(int n, char* arr) {
    int* tree = calloc((size_t)(n + 1), sizeof(int));
    for (int i = 0; i < n; ++i) {
        tree_update(tree, n, i + 1, (1 << (arr[i] - 'a')));
    }
    return tree;
}

int main() {
    char str[MAX_N];
    scanf("%s", &str[0]);
    int m;
    scanf("%d", &m);
    char op[4];
    char s[MAX_N];
    int n = (int)strlen(str);
    int* t = tree_make(n, str);
    for (int i = 0; i < m; ++i) {
        scanf("%s", &op[0]);
        if (op[0] == 'H') {
            int l;
            int r;
            scanf("%d%d", &l, &r);
            int ans = tree_query(t, l + 1, r + 1);
            if ((r - l + 1) & 1) {
                printf((ans & (ans - 1)) ? "NO\n" : "YES\n");
            } else {
                printf(ans ? "NO\n" : "YES\n");
            }
        } else {
            int ind;
            scanf("%d%s", &ind, &s[0]);
            int len = (int)strlen(s);
            for (int j = ind; j < ind + len; ++j) {
                tree_update(t, n, j + 1, (1 << (str[j] - 'a')) ^ (1 << (s[j - ind] - 'a')));
            }
            memcpy(&str[ind], s, (size_t)len);
            printf("%s\n", str);
        }
    }
    free(t);
    return 0;
}
