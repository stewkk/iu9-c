
#include <stdio.h>
#include <inttypes.h>

int strdiff(char* a, char* b) {
    size_t index = 0;
    while (a[index] != '\0' && b[index] != '\0') {
        uint8_t mask = 1;
        for (size_t i = 0; i < 8 * sizeof(char); ++i) {
            if ((a[index] & mask) != (b[index] & mask)) {
                return index * 8 * sizeof(char) + i;
            }
            mask <<= 1;
        }
        index++;
    }
    return -1;
}

int main() {
    printf("%d\n%d\n%d\n",
           strdiff("aa", "ai"),
           strdiff("abcd", "abcd"),
           strdiff("ba", "aa"));
    return 0;
}
