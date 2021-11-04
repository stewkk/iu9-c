
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preffunc(char* str, size_t* pref, size_t sz) {
    pref[0] = 0;
    for (size_t i = 1; i < sz; ++i) {
        size_t t = pref[i - 1];
        while (str[t] != str[i] && t > 0) {
            t = pref[t - 1];
        }
        if (str[t] == str[i]) {
            t++;
        }
        pref[i] = t;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 0;
    }
    char* s = argv[1];
    char* t = argv[2];
    size_t s_sz = strlen(s);
    size_t t_sz = strlen(t);
    size_t* pref = calloc(s_sz, sizeof(size_t));
    preffunc(s, pref, s_sz);
    size_t p = 0;
    for (size_t i = 0; i < t_sz; ++i) {
        while (s[p] != t[i] && p > 0) {
            p = pref[p - 1];
        }
        if (s[p] == t[i]) {
            p++;
        }
        if (p == s_sz) {
            printf("%zu ", i - s_sz + 1);
        }
    }
    printf("\n");
    free(pref);
    return 0;
}
