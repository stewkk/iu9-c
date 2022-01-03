
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int* delta1(char* s, int len) {
    int sz = (126 - 33 + 1);
    int* d = malloc((size_t)sz * sizeof(int));
    for (int i = 0; i < sz; ++i) {
        d[i] = len;
    }
    for (int i = 0; i < len; ++i) {
        d[s[i] - 33] = len - i - 1;
    }
    return d;
}

int* suf_func(char* s, int len) {
    int* suf = malloc(len * sizeof(int));
    int t = len - 1;
    suf[len - 1] = t;
    for (int i = len - 2; i >= 0; --i) {
        while (t < len - 1 && s[t] != s[i]) {
            t = suf[t + 1];
        }
        if (s[t] == s[i]) {
            t--;
        }
        suf[i] = t;
    }
    return suf;
}

int* delta2(char* s, int len) {
    int* d = malloc(len * sizeof(int));
    int* suff = suf_func(s, len);
    int t = suff[0];
    for (int i = 0; i < len; ++i) {
        while (t < i) {
            t = suff[t + 1];
        }
        d[i] = -i + t + len;
    }
    for (int i = 0; i < len - 1; ++i) {
        t = i;
        while (t < len - 1) {
            t = suff[t + 1];
            if (s[i] != s[t]) {
                d[t] = -(i + 1) + len;
            }
        }
    }
    free(suff);
    return d;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        return 0;
    }
    char* s = argv[1];
    char* t = argv[2];
    int s_len = (int)strlen(s);
    int t_len = (int)strlen(t);
    int* d1 = delta1(s, s_len);
    int* d2 = delta2(s, s_len);
    int k = s_len - 1;
    while (k < t_len) {
        int i = s_len - 1;
        while (t[k] == s[i]) {
            if (i == 0) {
                printf("%d ", k);
                break;
            }
            i--;
            k--;
        }
        k += max(d1[t[k] - 33], d2[i]);
    }
    printf("\n");
    free(d1);
    free(d2);
    return 0;
}
