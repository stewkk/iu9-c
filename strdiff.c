
#include <stdio.h>
#include <inttypes.h>

int strdiff(char* a, char* b) {
    int32_t index = -1;
    do {
      index++;
      uint8_t mask = 1;
      for (size_t i = 0; i < 8 * sizeof(char); ++i) {
        if ((a[index] & mask) != (b[index] & mask)) {
          return index * 8 * sizeof(char) + i;
        }
        mask <<= 1;
      }
    } while (a[index] != '\0' && b[index] != '\0');
    return -1;
}

int main() {
    printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
           strdiff("", "The quick brown fox jumps over the lazy dog"),
           strdiff("T", "The quick brown fox jumps over the lazy dog"),
           strdiff("The quick ", "The quick brown fox jumps over the lazy dog"),
           strdiff("The quick brown fox ", "The quick brown fox jumps over the lazy dog"),
           strdiff("The quick brown fox jumps over the lazy do", "The quick brown fox jumps over the lazy dog"),
           strdiff("The quick brown fox jumps over the lazy dog", ""),
           strdiff("The quick brown fox jumps over the lazy dog", "T"),
           strdiff("The quick brown fox jumps over the lazy dog", "The quick "),
           strdiff("The quick brown fox jumps over the lazy dog", "The quick brown fox "),
           strdiff("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog"),
           strdiff("", ""),
           strdiff("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy do"));
    return 0;
}
