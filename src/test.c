#include <stdio.h>
#include <stdint.h> // for uint8_t definitions
#include <x86intrin.h> // for __rdtscp and __rdtsc

// Assume gift64_encryption is defined elsewhere or include its definition here.
void gift64_encryption(uint8_t* dst, const uint8_t* src, const uint8_t* key);

// Function to measure the encryption time in CPU cycles
unsigned long long measure_cycles(uint8_t *dst, const uint8_t *src, const uint8_t *key, size_t num_bytes) {
    unsigned int ui;
    unsigned long long start, end;
    
    // Warm up the cache and the function
    gift64_encryption(dst, src, key);

    // Start time
    start = __rdtsc();

    // Run the encryption function
    for (size_t i = 0; i < num_bytes; i += 8) { // Assuming gift64 processes 8 bytes at a time
        gift64_encryption(dst + i, src + i, key);
    }

    // End time
    end = __rdtscp(&ui); // Use __rdtscp to serialize instruction execution

    return end - start;
}

int main() {
    const size_t num_bytes = 1024; // Change this based on your requirement
    uint8_t src[num_bytes], dst[num_bytes], key[16]; // Adjust key size according to the algorithm requirement

    // Initialize src and key with some values
    for (size_t i = 0; i < num_bytes; i++) {
        src[i] = (uint8_t)i; // Just an example initialization
    }
    for (size_t i = 0; i < 16; i++) {
        key[i] = (uint8_t)(i + 1); // Example key initialization
    }

    unsigned long long cycles = measure_cycles(dst, src, key, num_bytes);
    double cycles_per_byte = (double)cycles / num_bytes;

    printf("Total cycles: %llu\n", cycles);
    printf("Cycles per byte: %.2f\n", cycles_per_byte);

    return 0;
}