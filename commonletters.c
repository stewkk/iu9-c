
#include <stdio.h>

int main() {
    long u1 = 0;
    long u2 = 0;
    long mask = 1;
    int i = 0;
    int c;
    while ((c = getchar()) != ' ') {
        u1 |= mask << (c - 'a');
        ++i;
    }
    i = 0;
    while ((c = getchar()) != '\n') {
        u2 |= mask << (c - 'a');
        ++i;
    }
    u1 &= u2;
    i = 0;
    while (mask != 0) {
        if (mask & u1) {
            printf("%c", i + 'a');
        }
        ++i;
        mask <<= 1;
    }
    printf("\n");
    return 0;
}
