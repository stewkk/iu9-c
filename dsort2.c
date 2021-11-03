
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void count_letters(char* str, int* count) {
    while (*str != '\0') {
        count[*str - 'a']++;
        str++;
    }
}

void dsort(char** str_p) {
    char* str = *str_p;
    size_t sz = strlen(str);
    int count[26] = {0};
    count_letters(str, count);
    for (int i = 1; i < 26; ++i) {
        count[i] += count[i - 1];
    }
    char* sorted = calloc(sz + 1, sizeof(char));
    for (size_t i = sz; i > 0; --i) {
        char entry = str[i - 1];
        int key = entry - 'a';
        count[key]--;
        int sorted_index = count[key];
        sorted[sorted_index] = entry;
    }
    free(str);
    *str_p = sorted;
}

int main() {
    char* str;
    int c = scanf("%ms", &str);
    if (c == 1) {
        dsort(&str);
        printf("%s\n", str);
        free(str);
    }
    return 0;
}
