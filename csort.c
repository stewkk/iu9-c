
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <ctype.h>

int calc_words(char* str, int* words, int* words_len) {
    if (str[0] == '\0') {
        return 0;
    }
    if (str[1] == '\0') {
        if (!isspace(str[0])) {
            words[0] = 0;
            words_len[0] = 1;
            return 1;
        } else {
            return 0;
        }
    }
    int index = 0;
    int words_count = 0;
    if (!isspace(str[index])) {
        words[words_count] = index;
        int len = 0;
        while (!isspace(str[index])) {
            len++;
            index++;
        }
        words_len[words_count] = len;
        words_count++;
    }
    index++;
    while (str[index] != '\0') {
        if (isspace(str[index - 1]) && !isspace(str[index])) {
            words[words_count] = index;
            int len = 0;
            while (!isspace(str[index])) {
                len++;
                index++;
            }
            words_len[words_count] = len;
            words_count++;
        }
        index++;
    }
    return words_count;
}

char cmp(int a, int b) {
    if (a < b) {
        return 1;
    }
    if (a == b) {
        return 0;
    }
    return -1;
}

void csort(char* src, char* dest) {
    int words[BUFSIZ];
    int words_len[BUFSIZ];
    int words_count = calc_words(src, words, words_len);
    int indexes[BUFSIZ] = {0};
    for (int i = 0; i < words_count - 1; ++i) {
        for (int j = i + 1; j < words_count; ++j) {
            if (cmp(words_len[i], words_len[j]) >= 0) {
                indexes[j]++;
            } else {
                indexes[i]++;
            }
        }
    }
    int dest_index = 0;
    for (int i = 0; i < words_count; ++i) {
        int j = 0;
        while (indexes[j] != i) {
            j++;
        }
        for (int p = words[j]; !isspace(src[p]); ++p) {
            dest[dest_index] = src[p];
            dest_index++;
        }
        dest[dest_index] = ' ';
        dest_index++;
        dest[dest_index] = '\0';
    }
}

int main() {
    char* str = NULL;
    size_t sz = 0;
    getline(&str, &sz, stdin);
    char ans[sz];
    csort(str, ans);
    puts(ans);
    return 0;
}
