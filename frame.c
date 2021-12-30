
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage: frame <height> <width> <text>\n");
        return 0;
    }
    size_t height = (size_t)strtol(argv[1], NULL, 10);
    size_t width = (size_t)strtol(argv[2], NULL, 10);
    size_t len = strlen(argv[3]);
    for (int i = 4; i < argc; ++i) {
        len++;
        len += strlen(argv[i]);
    }
    char* text = malloc(len + 1);
    strcpy(text, argv[3]);
    for (int i = 4; i < argc; ++i) {
        strcat(text, " ");
        strcat(text, argv[i]);
    }
    if (height < 3) {
        free(text);
        printf("Error\n");
        return 0;
    }
    size_t sz = strlen(text);
    if (sz > width - 2) {
        free(text);
        printf("Error\n");
        return 0;
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
    free(text);
    return 0;
}
