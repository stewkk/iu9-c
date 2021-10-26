
#include <stdio.h>
#include <inttypes.h>

uint32_t nset_input() {
    size_t a_size;
    scanf("%zu", &a_size);
    uint32_t ans = 0;
    for (size_t i = 0; i < a_size; ++i) {
        uint8_t num;
        scanf("%"SCNu8, &num);
        ans |= UINT32_C(1) << num;
    }
    return ans;
}

int main() {
    uint32_t a = nset_input();
    uint32_t b = nset_input();
    a &= b;
    uint32_t mask = 1;
    for (uint8_t i = 0; i <= UINT8_C(31); ++i) {
        if (mask & a) {
            printf("%"PRIu8" ", i);
        }
        mask <<= 1;
    }
    printf("\n");
    return 0;
}
