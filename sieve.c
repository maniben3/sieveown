#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define BYTE unsigned char

inline BYTE *create_bitarray(size_t elements) {
    size_t bytes = elements / 8 + ((elements % 8) > 1);
    return (BYTE *) calloc(bytes, 1);
}

inline BYTE bitarray_get(BYTE *bitarray, size_t index) {
    size_t byte = index / 8;
    size_t offset_mask = 1 << (7 - (index % 8));
    return bitarray[byte] & offset_mask;
}

inline void bitarray_set(BYTE *bitarray, size_t index) {
    size_t byte = index / 8;
    size_t offset_mask = 1 << (7 - (index % 8));
    bitarray[byte] |= offset_mask;
}
void naive_sieve(uint64_t upper_bound, uint64_t **primes, uint64_t *prime_count) {
    BYTE *is_prime = create_bitarray(upper_bound);
    uint64_t total_primes = upper_bound - 2;
    for (uint64_t p = 2; (p * p) < upper_bound; p++) {
        if (bitarray_get(is_prime, p) == 0) {
            for (uint64_t i = p * p; i < upper_bound; i += p) {
                if (bitarray_get(is_prime, i) == 0) {
                    total_primes--;
                    bitarray_set(is_prime, i);
                }
            }
        }
    }

    *prime_count = total_primes;
    *primes = (uint64_t *) malloc(sizeof(uint64_t) * total_primes);
    size_t i = 0;
    for (uint64_t p = 2; p < upper_bound; p++) {
        if (bitarray_get(is_prime, p) == 0) (*primes)[i++] = p;
    }

    free(is_prime);
}

int main(void) {
  printf("Hello World\n");
  uint64_t chunk_size = 1e9;
  uint64_t *seed_primes;
  uint64_t seed_prime_count;
  naive_sieve(chunk_size, &seed_primes, &seed_prime_count);
  printf("%lu ",seed_prime_count);
  return 0;
}
