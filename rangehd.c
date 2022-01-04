#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001

int main() {
    char str[MAX_N];
    scanf("%s", &str[0]);
    int m;
    scanf("%d", &m);
    char op[4];
    char s[MAX_N];
    int arr[MAX_N];
    int ind = 1;
    arr[0] = 1 << (str[0] - 'a');
    char* it = &str[1];
    while (*it != '\0') {
        arr[ind] = arr[ind - 1] ^ (1 << (*it - 'a'));
        ind++;
        it++;
    }
    for (int i = 0; i < m; ++i) {
        scanf("%s", &op[0]);
        if (op[0] == 'H') {
            int l;
            int r;
            scanf("%d%d", &l, &r);
            int ans = arr[r];
            if (l) {
                ans ^= arr[l - 1];
            }
            if ((r - l + 1) & 1) {
                printf((ans & (ans - 1)) ? "NO\n" : "YES\n");
            } else {
                printf(ans ? "NO\n" : "YES\n");
            }
        } else {
            int ind;
            scanf("%d%s", &ind, &s[0]);
            it = &s[0];
            while (*it != '\0') {
                arr[ind] = arr[ind - 1] ^ (1 << (*it - 'a'));
                ind++;
                it++;
            }
            it = &str[ind];
            while (*it != '\0') {
                arr[ind] = arr[ind - 1] ^ (1 << (*it - 'a'));
                ind++;
                it++;
            }
        }
    }
    return 0;
}
