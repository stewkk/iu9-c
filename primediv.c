#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    long x;
    scanf("%ld", &x);
    int sieve_size = (int)(labs(x) / 2) + 1;
    char* sieve = calloc((unsigned long)sieve_size, sizeof(char));
    memset(sieve, 1, (unsigned long)sieve_size);
    int ans = 1;
    char is_x_prime = 1;
    /* sieve[0] = sieve[1] = 0; */
    for (int i = 2; i < sieve_size; ++i) {
        if (x % i == 0) {
            is_x_prime = 0;
        }
        if (sieve[i]) {
            if (x % i == 0) {
                ans = i;
            }
            if (i >= 46341) {
                continue;
            }
            for (int j = i * i; j < sieve_size; j += i) {
                sieve[j] = 0;
            }
        }
    }
    if (is_x_prime) {
        printf("%ld\n", labs(x));
    } else {
        printf("%d\n", ans);
    }
    free(sieve);
    return 0;
}
