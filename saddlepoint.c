
#include <stdio.h>
#include <limits.h>
#include <assert.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int mins[m];
    int mx = INT_MIN;
    int mx_index = 0;
    int ans = INT_MAX;
    for (int i = 0; i < m; ++i) {
        scanf("%d", &mins[i]);
        if (mins[i] > mx) {
            mx_index = i;
            mx = mins[i];
        }
    }
    ans = mx;
    int ans_i = 0;
    int ans_j = mx_index;
    for (int i = 1; i < n; ++i) {
        mx = INT_MIN;
        mx_index = 0;
        for (int j = 0; j < m; ++j) {
            int next;
            scanf("%d", &next);
            if (next < mins[j]) {
                if (mins[j] == ans) {
                    ans = INT_MAX;
                }
                mins[j] = next;
            }
            if (next > mx) {
                mx = next;
                mx_index = j;
            }
        }
        if (mins[mx_index] == mx) {
            assert(ans == INT_MAX);
            ans = mx;
            ans_i = i;
            ans_j = mx_index;
        }
    }
    if (ans == INT_MAX) {
        printf("none\n");
    } else {
        printf("%d %d\n", ans_i, ans_j);
    }
    return 0;
}
