
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char cmp(size_t a, size_t b) {
    if (a < b) {
        return 1;
    }
    if (a == b) {
        return 0;
    }
    return -1;
}

typedef struct {
    char* p;
    size_t len;
} word_t;

typedef struct {
    size_t sz;
    word_t* data;
    size_t _i_sz;
} words_array_t;

words_array_t* make_words_array() {
    words_array_t* arr = malloc(sizeof(words_array_t));
    arr->sz = 0;
    arr->data = calloc(10, sizeof(word_t));
    arr->_i_sz = 10;
    return arr;
}

void push_back(words_array_t* arr, word_t word) {
    if (arr->sz == arr->_i_sz) {
        arr->_i_sz *= 2;
        arr->data = realloc(arr->data, arr->_i_sz * sizeof(word_t));
    }
    arr->data[arr->sz] = word;
    arr->sz++;
}

void cleanup_words_array(words_array_t* arr) {
    if (arr) {
        free(arr->data);
    }
    free(arr);
}

size_t find_words(char* str, words_array_t** words) {
    *words = make_words_array();
    size_t words_count = 0;
    char prev = ' ';
    char* cur = str;
    while (*cur != '\0') {
        if (isspace(prev) && !isspace(*cur)) {
            char* start = cur;
            while (*cur != '\0' && !isspace(*cur)) {
                cur++;
            }
            size_t len = (size_t)(cur - start);
            word_t word = {start, len};
            push_back(*words, word);
            words_count++;
        } else {
            cur++;
        }
    }
    return words_count;
}

void sorted_string_recovery(size_t words_count, size_t* count, words_array_t* words, char* dest) {
    int dest_index = 0;
    for (size_t i = 0; i < words_count; ++i) {
        size_t j = 0;
        while (count[j] != i) {
            j++;
        }
        for (char* p = words->data[j].p; !isspace(*p); ++p) {
            dest[dest_index] = *p;
            dest_index++;
        }
        dest[dest_index] = ' ';
        dest_index++;
        dest[dest_index] = '\0';
    }
}

void csort(char* src, char* dest) {
    words_array_t* words = NULL;
    size_t words_count = find_words(src, &words);
    if (!words_count) {
        return;
    }
    size_t* count = calloc(words_count, sizeof(size_t));
    for (size_t i = 0; i < words_count - 1; ++i) {
        for (size_t j = i + 1; j < words_count; ++j) {
            if (cmp(words->data[i].len, words->data[j].len) >= 0) {
                count[j]++;
            } else {
                count[i]++;
            }
        }
    }
    sorted_string_recovery(words_count, count, words, dest);
    cleanup_words_array(words);
    free(count);
}

int main() {
    char* str = NULL;
    size_t sz = 0;
    getline(&str, &sz, stdin);
    char* ans = calloc(sz, sizeof(char));
    csort(str, ans);
    puts(ans);
    free(ans);
    free(str);
    return 0;
}
