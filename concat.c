
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat(char** s, int n) {
    size_t overall_size = 0;
    for (int i = 0; i < n; ++i) {
        overall_size += strlen(s[i]);
    }
    char* res = calloc(overall_size + 1, sizeof(char));
    int res_index = 0;
    for (int i = 0; i < n; ++i) {
        int index = 0;
        while (s[i][index] != '\0') {
            res[res_index] = s[i][index];
            res_index++;
            index++;
        }
    }
    res[res_index] = '\0';
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    char* arr[n];
    getc(stdin);
    for (int i = 0; i < n; ++i) {
        arr[i] = calloc(100, sizeof(char));
        scanf("%s", arr[i]);
    }
    char* res = concat(arr, n);
    puts(res);
    free(res);
    for (int i = 0; i < n; ++i) {
        free(arr[i]);
    }
    return 0;
}
