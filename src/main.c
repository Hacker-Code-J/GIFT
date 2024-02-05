#include "gift_generate.h"

int main(void) {
    u8 SBOX[16];
    u8 permbits[64];

    generate_sbox(SBOX);
    generate_permbits64_box(permbits);

    for (u8 i = 0; i < 16; i++) {
        printf("S[%u] = %x\n", i, SBOX[i]);
    }
    puts("");
    for (u8 i = 0; i < 64; i++) {
        printf("PermBits[%u] = %u\n", i, permbits[i]);
    }
    return 0;
}