#include "gift_generate.h"

void generate_sbox(u8 S[16]) {
    bool buffer[4], tmp;

    for (u8 i = 0; i < 16; i++) {
        buffer[0] = (i >> 0) & 1;
        buffer[1] = (i >> 1) & 1;
        buffer[2] = (i >> 2) & 1;
        buffer[3] = (i >> 3) & 1;

        buffer[1] = buffer[1] ^ (buffer[0] & buffer[2]);
        tmp       = buffer[0] ^ (buffer[1] & buffer[3]);
        buffer[2] = buffer[2] ^ (tmp       | buffer[1]);
        buffer[0] = buffer[3] ^ buffer[2];
        buffer[1] = buffer[1] ^ buffer[0];
        buffer[0] = !(buffer[0]);
        buffer[2] = buffer[2] ^ (tmp       & buffer[1]);
        buffer[3] = tmp;

        S[i] = (u8)buffer[3] << 3 |
               (u8)buffer[2] << 2 |
               (u8)buffer[1] << 1 |
               (u8)buffer[0];
    }
}


void generate_permbits64_box(u8 permbits[64]) {
    for (u8 i = 0; i < 64; i++) {
        permbits[i] = 4 * (i / 16) + 16 * ((3 * ((i % 16) / 4) + (i % 4)) % 4) + (i % 4);
    }
}
void generate_permbits128_box(u8 permbits[128]) {
    for (u8 i = 0; i < 128; i++) {
        permbits[i] = 4 * (i / 16) + 32 * ((3 * ((i % 16) / 4) + (i % 4)) % 4) + (i % 4);
    }
}