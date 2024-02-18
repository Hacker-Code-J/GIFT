#include "gift_generate.h"
#include "gift_key_schedule.h"
#include "gift_utils.h"
#include "gift.h"

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