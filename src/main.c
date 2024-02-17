#include "gift_generate.h"

int main(int argc, char** argv) {

#if 1
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