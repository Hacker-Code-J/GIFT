#include "gift_generate.h"
#include "gift_key_schedule.h"
#include "gift_utils.h"
#include "gift.h"

// // Function to measure the encryption time in CPU cycles
// unsigned long long measure_cycles(uint8_t *dst, const uint8_t *src, const uint8_t *key, size_t num_bytes) {
//     unsigned int ui;
//     unsigned long long start, end;
    
//     // Warm up the cache and the function
//     gift64_encryption(dst, src, key);

//     // Start time
//     start = __rdtsc();

//     // Run the encryption function
//     for (size_t i = 0; i < num_bytes; i += 8) { // Assuming gift64 processes 8 bytes at a time
//         gift64_encryption(dst + i, src + i, key);
//     }

//     // End time
//     end = __rdtscp(&ui); // Use __rdtscp to serialize instruction execution

//     return end - start;
// }

int main(int argc, char** argv) {
    // // Test Vector 1
    // const char* keyString = "00000000000000000000000000000000";
    // const char* intputString = "0000000000000000";
    
    // // Test Vector 2
    // const char* keyString = "fedcba9876543210fedcba9876543210";
    // const char* intputString = "fedcba9876543210";
    
    // Test Vector 3
    const char* keyString = "bd91731eb6bc2713a1f9f6ffc75044e7";
    const char* intputString = "c450c7727a9b8a7d";
    
    u8 MK[16] = { 0x00, };
    u8 PT[8] = { 0x00, };
    u8 CT[8] = { 0x00, };

    stringToByte(MK, keyString);
    stringToByte(PT, intputString);

    printByteData(PT, 8);
    gift64_encryption(CT, PT, MK);
    printByteData(CT, 8);

    // const size_t num_bytes = 8; // Change this based on your requirement
    // uint8_t src[num_bytes], dst[num_bytes], key[16]; // Adjust key size according to the algorithm requirement

    // // Initialize src and key with some values
    // for (size_t i = 0; i < num_bytes; i++) {
    //     src[i] = (uint8_t)i; // Just an example initialization
    // }
    // for (size_t i = 0; i < 16; i++) {
    //     key[i] = (uint8_t)(i + 1); // Example key initialization
    // }

    // unsigned long long cycles = measure_cycles(dst, src, key, num_bytes);
    // double cycles_per_byte = (double)cycles / num_bytes;

    // printf("Total cycles: %llu\n", cycles);
    // printf("Cycles per byte: %.2f\n", cycles_per_byte);

#if 0
    u8 SBOX[16];
    u8 permBits[64];
    u8 invPermBits[64];
    u8 rCon[48];

    generate_round_constants(rCon);
    generate_sbox(SBOX);
    generate_permBits64_box(permBits);

    for (u8 i = 0; i < 48; i++) {
        if (i % 8 == 0) puts("");
        printf("0x%02XU, ", rCon[i]);
    } puts("");

    for (u8 i = 0; i < 16; i++) {
        if (i % 8 == 0) puts("");
        printf("0x%02XU, ", SBOX[i]);
    } puts("");

    for (u8 i = 0; i < 64; i++) {
        if (i % 8 == 0) puts("");
        printf("0x%02XU, ", permBits[i]);
    } puts("");

    for (u8 i = 0; i < 64; i++) {
        invPermBits[permBits[i]] = i;
    }

    for (u8 i = 0; i < 64; i++) {
        if (i % 8 == 0) puts("");
        printf("0x%02XU, ", invPermBits[i]);
    } puts("");
#endif
    return 0;
}