
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void dsort(char* str) {
    unsigned int count[26] = {0};
    char* p = str;
    while (*p != '\0') {
        count[*p - 'a']++;
        p++;
    }
    for (int8_t i = 0; i < 26; ++i) {
        while (count[i]) {
            *str = (char)i + 'a';
            str++;
            count[i]--;
        }
    }
}

int main() {
    char* str;
    scanf("%ms", &str);
    if (!str) {
        printf("\n");
        return 0;
    }
    dsort(str);
    printf("%s\n", str);
    free(str);
    return 0;
}
