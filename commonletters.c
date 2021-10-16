
#include <stdio.h>
#include <ctype.h>

const int LOWER_SHIFT = 'a';
const int UPPER_SHIFT = 'A' - 26;

unsigned long get_letters_set() {
    int i = 0;
    unsigned long ans = 0;
    int c;
    while ((c = getchar()) != ' ' && c != '\n') {
        ans |= 1ul << (c - (islower(c) ? LOWER_SHIFT : UPPER_SHIFT));
        ++i;
    }
    return ans;
}

int main() {
    unsigned long u = get_letters_set();
    unsigned long u2 = get_letters_set();
    u &= u2;
    int i = 0;
    unsigned long mask = 1;
    while (mask != 0) {
        if (mask & u) {
            printf("%c", i + (i < 26 ? LOWER_SHIFT : UPPER_SHIFT));
        }
        ++i;
        mask <<= 1;
    }
    printf("\n");
    return 0;
}
