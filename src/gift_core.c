#include "gift.h"
#include "gift_utils.h"

void gift64_encryption(u8* dst, const u8* src, const u8* key) {
    u8 i, j, k;
    
    u8 state[8];
    bool bit[64], perm_bit[64];

    memcpy(state, src, 8);
    for (i = 0; i < 28; i++) {
        printf("\nRound %02u\n", i);
        // SubCells
        for (j = 0; j < 8; j++)
            state[j] = (GS[state[j] >> 4] << 4) | GS[state[j] & 0xF];

        printf("SubCells:\n");
        printByteData(state, 8);

        // for (j = 0; j < 8; j++) {
        //     for (k = 0; k < 8; k++) {
        //         bit[j * 8 + k] = (state[j] >> k) & 1;
        //     }
        // }
        for (u8 byteIndex = 0; byteIndex < 8; byteIndex++) {
            u8 bitIndex = byteIndex * 8;
            bit[bitIndex]     = (state[byteIndex] & 0x01) != 0;
            bit[bitIndex + 1] = (state[byteIndex] & 0x02) != 0;
            bit[bitIndex + 2] = (state[byteIndex] & 0x04) != 0;
            bit[bitIndex + 3] = (state[byteIndex] & 0x08) != 0;
            bit[bitIndex + 4] = (state[byteIndex] & 0x10) != 0;
            bit[bitIndex + 5] = (state[byteIndex] & 0x20) != 0;
            bit[bitIndex + 6] = (state[byteIndex] & 0x40) != 0;
            bit[bitIndex + 7] = (state[byteIndex] & 0x80) != 0;
        }

        for (j = 0; j < 64; j++)
            perm_bit[permBits64[j]] = bit[j];

        // for (j = 0; j < 8; j++) { // Iterate over each group of 8 bits
        //     state[j] = 0; // Initialize the byte
        //     for (k = 0; k < 8; k++) { // Iterate over each bit in the group
        //         if (perm_bit[j * 8 + k]) {
        //             state[j] |= (1 << k);
        //         }
        //     }
        // }

        for (j = 0; j < 8; j++) { // Iterate over each group of 8 bits
            state[j] = 0; // Initialize the byte
            // Manually unroll the loop over each bit in the group
            state[j] |= perm_bit[j * 8 + 0] ? (1 << 0) : 0;
            state[j] |= perm_bit[j * 8 + 1] ? (1 << 1) : 0;
            state[j] |= perm_bit[j * 8 + 2] ? (1 << 2) : 0;
            state[j] |= perm_bit[j * 8 + 3] ? (1 << 3) : 0;
            state[j] |= perm_bit[j * 8 + 4] ? (1 << 4) : 0;
            state[j] |= perm_bit[j * 8 + 5] ? (1 << 5) : 0;
            state[j] |= perm_bit[j * 8 + 6] ? (1 << 6) : 0;
            state[j] |= perm_bit[j * 8 + 7] ? (1 << 7) : 0;
        }

        printf("PermBits:\n");
        printByteData(state, 8);
    }
}
void gift64_decryption(u8* dst, const u8* src, const u8* key);

void gift128_encryption(u8* dst, const u8* src, const u8* key);
void gift128_decryption(u8* dst, const u8* src, const u8* key);