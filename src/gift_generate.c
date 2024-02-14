#include "gift_generate.h"

void generate_round_constants(u8 rCon[48]) {
    u8 state = 0b00000001; // 0x01
    rCon[0] = state;
    
    for (u8 i = 1; i < 48; i++) {
        bool new_bit = ((rCon[i-1] >> 5) & 0x01) ^ ((rCon[i-1] >> 4) & 0x01) ^ 0x01;
        state <<= 1;
        state |= new_bit;
        
        rCon[i] = state & 0x3F;
    }
}

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


void generate_permBits64_box(u8 permBits[64]) {
    for (u8 i = 0; i < 64; i++) {
        permBits[i] = 4 * (i / 16) + 16 * ((3 * ((i % 16) / 4) + (i % 4)) % 4) + (i % 4);
    }
}
void generate_permBits128_box(u8 permBits[128]) {
    for (u8 i = 0; i < 128; i++) {
        permBits[i] = 4 * (i / 16) + 32 * ((3 * ((i % 16) / 4) + (i % 4)) % 4) + (i % 4);
    }
}