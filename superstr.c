
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <inttypes.h>

int n;
int len[10];
char arr[10][BUFSIZ];
int ans = INT_MAX;
uint8_t used[10];

int calc_overlap(int llen, char* left, int rlen, char* right) {
    int overlap = llen < rlen ? llen : rlen;
    while (overlap && strncmp(left + llen - overlap, right, (size_t)overlap)) {
        overlap--;
    }
    return overlap;
}

void gen(char* cur, int cur_len, int used_count) {
    if (used_count == n) {
        ans = cur_len < ans ? cur_len : ans;
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            used[i] = 1;
            int overlap = calc_overlap(cur_len, cur, len[i], arr[i]);
            strcat(cur, arr[i] + overlap);
            gen(cur, cur_len + len[i] - overlap, used_count + 1);
            cur[cur_len] = '\0';
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        scanf("%s", arr[i]);
    }
    for (int i = 0; i < n; ++i) {
        len[i] = (int)strlen(arr[i]);
    }
    for (int i = 0; i < n; ++i) {
        char buf[BUFSIZ * 10];
        used[i] = 1;
        strcpy(buf, arr[i]);
        gen(buf, len[i], 1);
        used[i] = 0;
    }
    printf("%d\n", ans);
    return 0;
}
