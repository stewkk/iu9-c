
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: frame <height> <width> <text>");
        return 0;
    }
    size_t height = (size_t)strtol(argv[1], NULL, 10);
    size_t width = (size_t)strtol(argv[2], NULL, 10);
    char* text = argv[3];
    if (height < 3) {
        fprintf(stderr, "Error: height must be greater than 2");
        return 1;
    }
    size_t sz = strlen(text);
    if (sz > width - 2) {
        fprintf(stderr, "Error: text is too long\n");
        return 1;
    }
    char** buf = calloc(height, sizeof(char*));
    for (size_t i = 0; i < height; ++i) {
        buf[i] = calloc(width + 1, sizeof(char));
    }
    memset(buf[0], '*', width);
    for (size_t i = 1; i < height - 1; ++i) {
        memset(buf[i], ' ', width);
    }
    memset(buf[height - 1], '*', width);
    for (size_t i = 0; i < height; ++i) {
        buf[i][0] = '*';
        buf[i][width - 1] = '*';
        buf[i][width] = '\0';
    }
    strncpy(&buf[(height - 1) / 2][(width - sz) / 2], text, sz);
    for (size_t i = 0; i < height; ++i) {
        puts(buf[i]);
        free(buf[i]);
    }
    free(buf);
    return 0;
}
