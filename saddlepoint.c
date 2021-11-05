
#include <stdio.h>
#include <limits.h>

const int INF = INT_MAX;
const int MAX_N = 10;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int mins[MAX_N];
    for (int i = 0; i < m; ++i) {
        mins[i] = INF;
    }
    int mx = -INF;
    int mx_index = 0;
    int ans = -INF;
    int ans_i = INF;
    int ans_j = INF;
    for (int i = 0; i < n; ++i) {
        mx = -INF;
        for (int j = 0; j < m; ++j) {
            int next;
            scanf("%d", &next);
            if (next < mins[j]) {
                if (mins[j] == ans) {
                    ans = -INF;
                }
                mins[j] = next;
            }
            if (next > mx) {
                mx = next;
                mx_index = j;
            }
        }
        if (mins[mx_index] == mx) {
            ans = mx;
            ans_i = i;
            ans_j = mx_index;
        }
    }
    if (ans == -INF) {
        printf("none\n");
    } else {
        printf("%d %d\n", ans_i, ans_j);
    }
    return 0;
}
