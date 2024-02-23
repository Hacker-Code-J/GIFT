#include "gift.h"
#include "gift_key_schedule.h"
#include "gift_utils.h"

void gift64_encryption(u8* dst, const u8* src, const u8* key) {
    u8 r, i;
    
    u8 state[8];
    bool bit[64], perm_bit[64];
    
    u8 uKey[16];
    memcpy(uKey, key, 16);

    u8 rKey[4];

    memcpy(state, src, 8);
    for (r = 0; r < 28; r++) {
        // SubCells
        for (i = 0; i < 8; i++)
            state[i] = (GS[state[i] >> 4] << 4) | GS[state[i] & 0xF];
        
        // PermBits
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
        for (i = 0; i < 64; i++)
            perm_bit[permBits64[i]] = bit[i];
        
        // AddRoundKeys
        gift64_getRoundKey(rKey, uKey);  
        perm_bit[ 0] ^= (rKey[0]     ) & 1;
        perm_bit[ 4] ^= (rKey[0] >> 1) & 1;
        perm_bit[ 8] ^= (rKey[0] >> 2) & 1;
        perm_bit[12] ^= (rKey[0] >> 3) & 1;
        perm_bit[16] ^= (rKey[0] >> 4) & 1;
        perm_bit[20] ^= (rKey[0] >> 5) & 1;
        perm_bit[24] ^= (rKey[0] >> 6) & 1;
        perm_bit[28] ^= (rKey[0] >> 7) & 1;

        perm_bit[32] ^= (rKey[1]     ) & 1;
        perm_bit[36] ^= (rKey[1] >> 1) & 1;
        perm_bit[40] ^= (rKey[1] >> 2) & 1;
        perm_bit[44] ^= (rKey[1] >> 3) & 1;
        perm_bit[48] ^= (rKey[1] >> 4) & 1;
        perm_bit[52] ^= (rKey[1] >> 5) & 1;
        perm_bit[56] ^= (rKey[1] >> 6) & 1;
        perm_bit[60] ^= (rKey[1] >> 7) & 1;

        perm_bit[ 1] ^= (rKey[2]     ) & 1;;
        perm_bit[ 5] ^= (rKey[2] >> 1) & 1;
        perm_bit[ 9] ^= (rKey[2] >> 2) & 1;
        perm_bit[13] ^= (rKey[2] >> 3) & 1;
        perm_bit[17] ^= (rKey[2] >> 4) & 1;
        perm_bit[21] ^= (rKey[2] >> 5) & 1;
        perm_bit[25] ^= (rKey[2] >> 6) & 1;
        perm_bit[29] ^= (rKey[2] >> 7) & 1;

        perm_bit[33] ^= (rKey[3]     ) & 1;
        perm_bit[37] ^= (rKey[3] >> 1) & 1;
        perm_bit[41] ^= (rKey[3] >> 2) & 1;
        perm_bit[45] ^= (rKey[3] >> 3) & 1;
        perm_bit[49] ^= (rKey[3] >> 4) & 1;
        perm_bit[53] ^= (rKey[3] >> 5) & 1;
        perm_bit[57] ^= (rKey[3] >> 6) & 1;
        perm_bit[61] ^= (rKey[3] >> 7) & 1;

        // Round Constants
        perm_bit[ 3] ^= (gift_rCon[r]     ) & 1;
        perm_bit[ 7] ^= (gift_rCon[r] >> 1) & 1;
        perm_bit[11] ^= (gift_rCon[r] >> 2) & 1;
        perm_bit[15] ^= (gift_rCon[r] >> 3) & 1;
        perm_bit[19] ^= (gift_rCon[r] >> 4) & 1;
        perm_bit[23] ^= (gift_rCon[r] >> 5) & 1;
        perm_bit[63] ^= 1;

        for (i = 0; i < 8; i++) {
            state[i] = 0;
            state[i] |= perm_bit[i * 8 + 0] ? (1 << 0) : 0;
            state[i] |= perm_bit[i * 8 + 1] ? (1 << 1) : 0;
            state[i] |= perm_bit[i * 8 + 2] ? (1 << 2) : 0;
            state[i] |= perm_bit[i * 8 + 3] ? (1 << 3) : 0;
            state[i] |= perm_bit[i * 8 + 4] ? (1 << 4) : 0;
            state[i] |= perm_bit[i * 8 + 5] ? (1 << 5) : 0;
            state[i] |= perm_bit[i * 8 + 6] ? (1 << 6) : 0;
            state[i] |= perm_bit[i * 8 + 7] ? (1 << 7) : 0;
        }
        gift_updateKey(uKey);
    }

    memcpy(dst, state, 8);
}
void gift64_decryption(u8* dst, const u8* src, const u8* key);

void gift128_encryption(u8* dst, const u8* src, const u8* key) {
    u8 r, i;
    
    u8 state[16];
    bool bit[128], perm_bit[128];
    
    u8 uKey[16];
    memcpy(uKey, key, 16);

    u8 rKey[8];

    memcpy(state, src, 16);
    for (r = 0; r < 40; r++) {
        // SubCells
        for (i = 0; i < 16; i++)
            state[i] = (GS[state[i] >> 4] << 4) | GS[state[i] & 0xF];
        
        // // PermBits
        for (u8 byteIndex = 0; byteIndex < 16; byteIndex++) {
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
        for (i = 0; i < 128; i++)
            perm_bit[permBits128[i]] = bit[i];
        
        // AddRoundKeys
        gift128_getRoundKey(rKey, uKey);  
        perm_bit[  0] ^= (rKey[0]     ) & 1;
        perm_bit[  4] ^= (rKey[0] >> 1) & 1;
        perm_bit[  8] ^= (rKey[0] >> 2) & 1;
        perm_bit[ 12] ^= (rKey[0] >> 3) & 1;
        perm_bit[ 16] ^= (rKey[0] >> 4) & 1;
        perm_bit[ 20] ^= (rKey[0] >> 5) & 1;
        perm_bit[ 24] ^= (rKey[0] >> 6) & 1;
        perm_bit[ 28] ^= (rKey[0] >> 7) & 1;

        perm_bit[ 32] ^= (rKey[1]     ) & 1;
        perm_bit[ 36] ^= (rKey[1] >> 1) & 1;
        perm_bit[ 40] ^= (rKey[1] >> 2) & 1;
        perm_bit[ 44] ^= (rKey[1] >> 3) & 1;
        perm_bit[ 48] ^= (rKey[1] >> 4) & 1;
        perm_bit[ 52] ^= (rKey[1] >> 5) & 1;
        perm_bit[ 56] ^= (rKey[1] >> 6) & 1;
        perm_bit[ 60] ^= (rKey[1] >> 7) & 1;

        perm_bit[  1] ^= (rKey[2]     ) & 1;;
        perm_bit[  5] ^= (rKey[2] >> 1) & 1;
        perm_bit[  9] ^= (rKey[2] >> 2) & 1;
        perm_bit[ 13] ^= (rKey[2] >> 3) & 1;
        perm_bit[ 17] ^= (rKey[2] >> 4) & 1;
        perm_bit[ 21] ^= (rKey[2] >> 5) & 1;
        perm_bit[ 25] ^= (rKey[2] >> 6) & 1;
        perm_bit[ 29] ^= (rKey[2] >> 7) & 1;

        perm_bit[ 33] ^= (rKey[3]     ) & 1;
        perm_bit[ 37] ^= (rKey[3] >> 1) & 1;
        perm_bit[ 41] ^= (rKey[3] >> 2) & 1;
        perm_bit[ 45] ^= (rKey[3] >> 3) & 1;
        perm_bit[ 49] ^= (rKey[3] >> 4) & 1;
        perm_bit[ 53] ^= (rKey[3] >> 5) & 1;
        perm_bit[ 57] ^= (rKey[3] >> 6) & 1;
        perm_bit[ 61] ^= (rKey[3] >> 7) & 1;

        perm_bit[ 64] ^= (rKey[4]     ) & 1;
        perm_bit[ 68] ^= (rKey[4] >> 1) & 1;
        perm_bit[ 72] ^= (rKey[4] >> 2) & 1;
        perm_bit[ 76] ^= (rKey[4] >> 3) & 1;
        perm_bit[ 80] ^= (rKey[4] >> 4) & 1;
        perm_bit[ 84] ^= (rKey[4] >> 5) & 1;
        perm_bit[ 88] ^= (rKey[4] >> 6) & 1;
        perm_bit[ 92] ^= (rKey[4] >> 7) & 1;
 
        perm_bit[  96] ^= (rKey[5]     ) & 1;
        perm_bit[ 100] ^= (rKey[5] >> 1) & 1;
        perm_bit[ 104] ^= (rKey[5] >> 2) & 1;
        perm_bit[ 108] ^= (rKey[5] >> 3) & 1;
        perm_bit[ 112] ^= (rKey[5] >> 4) & 1;
        perm_bit[ 116] ^= (rKey[5] >> 5) & 1;
        perm_bit[ 120] ^= (rKey[5] >> 6) & 1;
        perm_bit[ 124] ^= (rKey[5] >> 7) & 1;

        perm_bit[ 65] ^= (rKey[6]     ) & 1;;
        perm_bit[ 69] ^= (rKey[6] >> 1) & 1;
        perm_bit[ 73] ^= (rKey[6] >> 2) & 1;
        perm_bit[ 77] ^= (rKey[6] >> 3) & 1;
        perm_bit[ 81] ^= (rKey[6] >> 4) & 1;
        perm_bit[ 85] ^= (rKey[6] >> 5) & 1;
        perm_bit[ 89] ^= (rKey[6] >> 6) & 1;
        perm_bit[ 93] ^= (rKey[6] >> 7) & 1;

        perm_bit[ 97] ^= (rKey[7]     ) & 1;
        perm_bit[101] ^= (rKey[7] >> 1) & 1;
        perm_bit[105] ^= (rKey[7] >> 2) & 1;
        perm_bit[109] ^= (rKey[7] >> 3) & 1;
        perm_bit[113] ^= (rKey[7] >> 4) & 1;
        perm_bit[117] ^= (rKey[7] >> 5) & 1;
        perm_bit[121] ^= (rKey[7] >> 6) & 1;
        perm_bit[125] ^= (rKey[7] >> 7) & 1;

        // Round Constants
        perm_bit[  3] ^= (gift_rCon[r]     ) & 1;
        perm_bit[  7] ^= (gift_rCon[r] >> 1) & 1;
        perm_bit[ 11] ^= (gift_rCon[r] >> 2) & 1;
        perm_bit[ 15] ^= (gift_rCon[r] >> 3) & 1;
        perm_bit[ 19] ^= (gift_rCon[r] >> 4) & 1;
        perm_bit[ 23] ^= (gift_rCon[r] >> 5) & 1;
        perm_bit[127] ^= 1;

        for (i = 0; i < 16; i++) {
            state[i] = 0;
            state[i] |= perm_bit[i * 8 + 0] ? (1 << 0) : 0;
            state[i] |= perm_bit[i * 8 + 1] ? (1 << 1) : 0;
            state[i] |= perm_bit[i * 8 + 2] ? (1 << 2) : 0;
            state[i] |= perm_bit[i * 8 + 3] ? (1 << 3) : 0;
            state[i] |= perm_bit[i * 8 + 4] ? (1 << 4) : 0;
            state[i] |= perm_bit[i * 8 + 5] ? (1 << 5) : 0;
            state[i] |= perm_bit[i * 8 + 6] ? (1 << 6) : 0;
            state[i] |= perm_bit[i * 8 + 7] ? (1 << 7) : 0;
        }
        gift_updateKey(uKey);
    }

    memcpy(dst, state, 16);
}
void gift128_decryption(u8* dst, const u8* src, const u8* key);

/* ==== Development Version ====*/
void gift64_encryption_dev(u8* dst, const u8* src, const u8* key) {
    u8 r, i;
    // u8 j;
    
    u8 state[8];
    bool bit[64], perm_bit[64];
    
    u8 uKey[16];
    u8 rKey[4];
    memcpy(uKey, key, 16);

    memcpy(state, src, 8);
    for (r = 0; r < 28; r++) {
        printf("\nRound %02u\n", r);
        // SubCells
        printf("SubCells:\n");
        for (i = 0; i < 8; i++)
            state[i] = (GS[state[i] >> 4] << 4) | GS[state[i] & 0xF];
        printByteData(state, 8);

        // PermBits
        printf("PermBits:\n");
        // for (i = 0; i < 8; i++) {
        //     for (j = 0; j < 8; j++) {
        //         bit[i * 8 + j] = (state[i] >> j) & 1;
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

        for (i = 0; i < 64; i++)
            perm_bit[permBits64[i]] = bit[i];

        // for (i = 0; i < 8; i++) { // Iterate over each group of 8 bits
        //     state[i] = 0; // Initialize the byte
        //     for (j = 0; j < 8; j++) { // Iterate over each bit in the group
        //         if (perm_bit[i * 8 + j]) {
        //             state[i] |= (1 << j);
        //         }
        //     }
        // }

        for (i = 0; i < 8; i++) { // Iterate over each group of 8 bits
            state[i] = 0; // Initialize the byte
            // Manually unroll the loop over each bit in the group
            state[i] |= perm_bit[i * 8 + 0] ? (1 << 0) : 0;
            state[i] |= perm_bit[i * 8 + 1] ? (1 << 1) : 0;
            state[i] |= perm_bit[i * 8 + 2] ? (1 << 2) : 0;
            state[i] |= perm_bit[i * 8 + 3] ? (1 << 3) : 0;
            state[i] |= perm_bit[i * 8 + 4] ? (1 << 4) : 0;
            state[i] |= perm_bit[i * 8 + 5] ? (1 << 5) : 0;
            state[i] |= perm_bit[i * 8 + 6] ? (1 << 6) : 0;
            state[i] |= perm_bit[i * 8 + 7] ? (1 << 7) : 0;
        }
        printByteData(state, 8);
        
        // AddRoundKeys
        printf("AddRoundKeys:\n");
        gift64_getRoundKey(rKey, uKey);
        // bool rk_bit = rKey[0] & 1;
        // rKey[0] >> 1;
        // perm_bit[0] ^= rk_bit;
        
        // rk_bit = rKey[0] & 1;
        // rKey[0] >> 1;
        // perm_bit[4] ^= rk_bit;
        
        for (i = 0; i < 8; i++) {
            bool rk_bit = rKey[0] & 1;
            rKey[0] >>= 1;
            perm_bit[4 * i] ^= rk_bit;
        }
        for (i = 0; i < 8; i++) {
            bool rk_bit = rKey[1] & 1;
            rKey[1] >>= 1;
            perm_bit[32 + (4 * i)] ^= rk_bit;
        }
        for (i = 0; i < 8; i++) {
            bool rk_bit = rKey[2] & 1;
            rKey[2] >>= 1;
            perm_bit[4 * i + 1] ^= rk_bit;
        }
        for (i = 0; i < 8; i++) {
            bool rk_bit = rKey[3] & 1;
            rKey[3] >>= 1;
            perm_bit[32 + (4 * i) + 1] ^= rk_bit;
        }

        perm_bit[ 3] ^= (gift_rCon[r]     ) & 1;
        perm_bit[ 7] ^= (gift_rCon[r] >> 1) & 1;
        perm_bit[11] ^= (gift_rCon[r] >> 2) & 1;
        perm_bit[15] ^= (gift_rCon[r] >> 3) & 1;
        perm_bit[19] ^= (gift_rCon[r] >> 4) & 1;
        perm_bit[23] ^= (gift_rCon[r] >> 5) & 1;
        perm_bit[63] ^= 1;

        for (i = 0; i < 8; i++) { // Iterate over each group of 8 bits
            state[i] = 0; // Initialize the byte
            // Manually unroll the loop over each bit in the group
            state[i] |= perm_bit[i * 8 + 0] ? (1 << 0) : 0;
            state[i] |= perm_bit[i * 8 + 1] ? (1 << 1) : 0;
            state[i] |= perm_bit[i * 8 + 2] ? (1 << 2) : 0;
            state[i] |= perm_bit[i * 8 + 3] ? (1 << 3) : 0;
            state[i] |= perm_bit[i * 8 + 4] ? (1 << 4) : 0;
            state[i] |= perm_bit[i * 8 + 5] ? (1 << 5) : 0;
            state[i] |= perm_bit[i * 8 + 6] ? (1 << 6) : 0;
            state[i] |= perm_bit[i * 8 + 7] ? (1 << 7) : 0;
        }
        printByteData(state, 8);

        gift_updateKey(uKey);
        printf("Updated Key:\n");
        printByteData(uKey, 16);
    }

    memcpy(dst, state, 8);
}