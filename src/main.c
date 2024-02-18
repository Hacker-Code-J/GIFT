#include "gift_generate.h"
#include "gift_key_schedule.h"
#include "gift_utils.h"
#include "gift.h"

// // Function to measure the encryption time in CPU cycles
// u64 measure_cycles(u8 *dst, const u8 *src, const u8 *key, size_t num_bytes) {
//     u32 ui;
//     u64 start, end;
    
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

    // printByteData(PT, 8);
    gift64_encryption(CT, PT, MK);
    // printByteData(CT, 8);

    for (int i = 0; i < 1000; i++) {
        measure_cpu_cycle(gift64_encryption, CT, PT, MK);
        printf("0\n");
    }
    // const size_t num_bytes = 1024; // Change this based on your requirement
    // u8 src[num_bytes], dst[num_bytes], key[16]; // Adjust key size according to the algorithm requirement

    // // Initialize src and key with some values
    // for (size_t i = 0; i < num_bytes; i++) {
    //     src[i] = (u8)i; // Just an example initialization
    // }
    // for (size_t i = 0; i < 16; i++) {
    //     key[i] = (u8)(i + 1); // Example key initialization
    // }

    // u64 cycles = measure_cycles(dst, src, key, num_bytes);
    // double cycles_per_byte = (double)cycles / num_bytes;

    // printf("%.2f c/B\n", cycles_per_byte);

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