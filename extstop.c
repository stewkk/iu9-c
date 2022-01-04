
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int** delta1(char* s, int len) {
    int sz = (126 - 33 + 1);
    int** d = malloc((size_t)len * sizeof(int*));
    for (int i = 0; i < len; ++i) {
        d[i] = malloc((size_t)sz * sizeof(int));
    }
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < sz; ++j) {
            d[i][j] = len;
        }
    }
    d[0][s[0] - 33] = len - 0 - 1;
    for (int i = 1; i < len; ++i) {
        memcpy(d[i], d[i - 1], (size_t)sz * (sizeof(int)));
        d[i][s[i] - 33] = len - i - 1;
    }
    return d;
}

void d1_cleanup(int** d1, int s_len) {
    for (int i = 0; i < s_len; ++i) {
      free(d1[i]);
    }
    free(d1);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        return 0;
    }
    char* s = argv[1];
    char* t = argv[2];
    int s_len = (int)strlen(s);
    int t_len = (int)strlen(t);
    int** d1 = delta1(s, s_len);
    int k = s_len - 1;
    while (k < t_len) {
        int i = s_len - 1;
        while (t[k] == s[i]) {
            if (i == 0) {
                printf("%d\n", k);
                d1_cleanup(d1, s_len);
                return 0;
            }
            i--;
            k--;
        }
        k += max(d1[i][t[k] - 33], s_len - i);
    }
    printf("%d\n", t_len);
    d1_cleanup(d1, s_len);
    return 0;
}
