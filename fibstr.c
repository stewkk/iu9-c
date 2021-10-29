
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void size_swap(size_t* a, size_t* b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

void str_swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

char* fibstr(int n) {
    char* fib1 = calloc(2, sizeof(char));
    char* fib2 = calloc(2, sizeof(char));
    strcpy(fib1, "a");
    strcpy(fib2, "b");
    if (n == 1) {
        free(fib2);
        return fib1;
    }
    if (n == 2) {
        free(fib1);
        return fib2;
    }
    size_t sz1 = 1;
    size_t sz2 = 1;
    for (int i = 3; i <= n; ++i) {
        fib1 = realloc(fib1, sz1 + sz2 + 1);
        strcat(fib1, fib2);
        str_swap(&fib1, &fib2);
        sz1 += sz2;
        size_swap(&sz1, &sz2);
    }
    free(fib1);
    return fib2;
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        char* str = fibstr(i);
        puts(str);
        free(str);
    }
    return 0;
}
