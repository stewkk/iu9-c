
#include <stdio.h>
#include <limits.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int max_elems_indexes[n];
    int min_elems[m];
    int min_elems_indexes[m];
    for (int j = 0; j < m; ++j) {
        min_elems[j] = INT_MAX;
    }
    for (int i = 0; i < n; ++i) {
        int index = -1;
        int mx = INT_MIN;
        for (int j = 0; j < m; ++j) {
            int num;
            scanf("%d", &num);
            if (num > mx) {
                mx = num;
                index = j;
            } else if (num == mx) {
                index = -1;
            }
            if (num < min_elems[j]) {
                min_elems[j] = num;
                min_elems_indexes[j] = i;
            } else if (num == min_elems[j]) {
                min_elems_indexes[j] = -1;
            }
        }
        max_elems_indexes[i] = index;
    }
    for (int i = 0; i < n; ++i) {
        if (max_elems_indexes[i] != -1
            && min_elems_indexes[max_elems_indexes[i]] == i) {
            printf("%d %d\n", i, max_elems_indexes[i]);
            return 0;
        }
    }
    printf("none\n");
    return 0;
}
