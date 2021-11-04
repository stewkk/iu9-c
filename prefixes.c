
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    if (!argc) {
        return 0;
    }
    char* str = argv[1];
    size_t sz = strlen(str);
    size_t* pref = calloc(sz, sizeof(size_t));
    preffunc(str, pref, sz);
    for (size_t period = 1; period <= sqrt(sz); ++period) {
        size_t i = period * 2 - 1;
        int k = 2;
        while (i < sz && pref[i] >= period) {
            printf("%zu %d\n", i + 1, k);
            i += period;
            k++;
        }
    }
    free(pref);
    return 0;
}
