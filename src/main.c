#include "gift_generate.h"
#include "gift_key_schedule.h"
#include "gift_utils.h"
#include "gift.h"

int main(int argc, char** argv) {
    const char* keyString = "fedcba9876543210fedcba9876543210";
    const char* intputString = "fedcba9876543210";
    u8 MK[16] = { 0x00, };
    u8 PT[8] = { 0x00, };
    u8 CT[8] = { 0x00, };

    stringToByte(MK, keyString);
    stringToByte(PT, intputString);

    printByteData(PT, 8);
    gift64_encryption(CT, PT, MK);


    // u8 RK_64[4] = { 0x00, };
    // stringToByte(MK, keyString);
    // printByteData(MK, 16);

    // gift64_getRoundKey(RK_64, MK);
    // // printByteData(RK_64, 4);
    // gift_updateKey(MK);
    // printByteData(MK, 16);

    // 3f b7 a9 8b fe dc ba 98 76 54 32 10 fe dc ba 98 
    // 3f:b7:a9:8b:fe:dc:ba:98:76:54:32:10:fe:dc:ba:98:
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