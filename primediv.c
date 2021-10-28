
#include <stdio.h>

const int SIEVE_SIZE = 46342;
const int PRIMES_SIZE = 4792;

void calc_primes(int primes[PRIMES_SIZE]) {
    char sieve[SIEVE_SIZE];
    for (int i = 0; i < SIEVE_SIZE; ++i) {
        sieve[i] = 1;
    }
    /* sieve[0] = sieve[1] = 0; */
    int index = 0;
    for (int i = 2; i < SIEVE_SIZE; ++i) {
        if (sieve[i]) {
            primes[index] = i;
            index++;
            for (int j = i * i; j < SIEVE_SIZE; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int main() {
    int x;
    scanf("%d", &x);
    if (x == 0) {
        return 0;
    }
    int primes[PRIMES_SIZE];
    calc_primes(primes);
    for (int i = PRIMES_SIZE - 1; i >= 0; --i) {
        if (x % primes[i] == 0) {
            printf("%d\n", primes[i]);
            return 0;
        }
    }
    return 0;
}
