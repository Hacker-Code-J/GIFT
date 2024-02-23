#include "gift_generate.h"
#include "gift_key_schedule.h"
#include "gift_utils.h"
#include "gift.h"

// void assign_rand_byte(u8* dst, size_t byteLen) {
//     // Cast the destination pointer to a pointer to u8 (unsigned 8-bit integer)
//     u8* p = (u8*)dst;
    
//     // Calculate the total number of bytes to be filled
//     u32 cnt = byteLen * sizeof(u8);

//     // Loop until all bytes are filled
//     while (cnt > 0) {
//         *p = rand() & 0xff; // Assign a random byte (0 to 255) to the current location pointed by p
//         p++;                // Move to the next byte
//         cnt--;
//     }
// }

int main(int argc, char** argv) {
    // // ====== GIFT-64-128 ======
    // // // Test Vector 1
    // // const char* keyString = "00000000000000000000000000000000";
    // // const char* intputString = "0000000000000000";
    
    // // // Test Vector 2
    // // const char* keyString = "fedcba9876543210fedcba9876543210";
    // // const char* intputString = "fedcba9876543210";
    
    // // Test Vector 3
    // const char* keyString = "bd91731eb6bc2713a1f9f6ffc75044e7";
    // const char* intputString = "c450c7727a9b8a7d";
    
    // u8 MK[16] = { 0x00, };
    // u8 PT[8] = { 0x00, };
    // u8 CT[8] = { 0x00, };

    // stringToByte(MK, keyString);
    // stringToByte(PT, intputString);

    // printByteData(PT, 8);
    // gift64_encryption(CT, PT, MK);
    // printByteData(CT, 8);

    // ====== GIFT-64-128 ======
    // // Test Vector 1
    // const char* keyString = "00000000000000000000000000000000";
    // const char* intputString = "00000000000000000000000000000000";
    
    // // Test Vector 2
    // const char* keyString = "fedcba9876543210fedcba9876543210";
    // const char* intputString = "fedcba9876543210fedcba9876543210";
    
    // Test Vector 3
    const char* keyString = "d0f5c59a7700d3e799028fa9f90ad837";
    const char* intputString = "e39c141fa57dba43f08a85b6a91f86c1";
    
    u8 MK[16] = { 0x00, };
    u8 PT[16] = { 0x00, };
    u8 CT[16] = { 0x00, };

    stringToByte(MK, keyString);
    stringToByte(PT, intputString);

    printByteData(MK, 16);
    printByteData(PT, 16);
    gift128_encryption(CT, PT, MK);
    printByteData(CT, 16);


    // for (int i = 0; i < 1000; i++) {
    //     measure_cpu_cycle(gift64_encryption, CT, PT, MK);
    //     printf("0\n");
    // }
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

    // u64 cycles;
    // for (u32 i = 0; i < 12000; i++) {
    //     assign_rand_byte(MK, 16);
    //     assign_rand_byte(PT, 8);
    //     // assign_rand(src2, SIZE);
    //     cycles = measure_cpu_cycle(gift64_encryption, CT, PT, MK);
    //     if (i >= 1000 && i < 11000) {
    //         printf("%" PRIu64 "\n", cycles);
    //         // printf("%" PRIu64 "\n", cycles / (u64)(SIZE * 2));
    //     }
    // }

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