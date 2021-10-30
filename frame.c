
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
    /* to fit \n character */
    width++;
    size_t res_len = height * width;
    char* buf = calloc(res_len + 1, sizeof(char));
    /* initialize buffer with spaces */
    memset(buf, ' ', res_len);
    /* fill first line with asterisks */
    memset(buf, '*', width);
    /* fill last list with asterisks */
    memset(&buf[res_len - width], '*', width);
    /* fill first and last-1 coloumn with asterisks and last with newline */
    for (size_t i = 0; i < res_len; i += width) {
        buf[i] = '*';
        buf[i + width - 1] = '\n';
        buf[i + width - 2] = '*';
    }
    /* copy text to buf */
    strncpy(&buf[(height - 1) / 2 * width + (width - sz - 1) / 2], text, sz);
    /* terminating character */
    buf[res_len] = '\0';
    printf("%s", buf);
    free(buf);
    return 0;
}
