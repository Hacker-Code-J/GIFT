#include "gift_key_schedule.h"
#include "gift_utils.h"

void gift64_getRoundKey(u8* rKey, u8* key) {
    u32 word_rKey[1];
    u32 word_key[4];

    byteToWord(word_key, key, 16);
    word_rKey[0] = word_key[0];
    wordToByte(rKey, word_rKey, 1);
}

void gift128_getRoundKey(u8* rKey, u8* key) {
    u32 word_rKey[2];
    u32 word_key[4];

    byteToWord(word_key, key, 16);
    word_rKey[0] = word_key[0];
    word_rKey[1] = word_key[2];
    wordToByte(rKey, word_rKey, 2);
}

void gift_updateKey(u8* key) {
    u32 state[4];
    u32 word_key[4];

    u8 data1 = ((key[2] & 0x3) << 6) | (key[3] >> 2);
    u8 data2 = ((key[3] & 0x3) << 6) | (key[2] >> 2);

    u8 data3 = ((key[1] & 0xF) << 4) | (key[0] >> 4);
    u8 data4 = ((key[0] & 0xF) << 4) | (key[1] >> 4);

    byteToWord(word_key, key, 16);
    state[3] = (u32)(data1 << 0x18) |
               (u32)(data2 << 0x10) |
               (u32)(data3 << 0x08) |
               (u32)(data4        );
    state[2] = word_key[3];
    state[1] = word_key[2];
    state[0] = word_key[1];
    
    wordToByte(key, state, 4);
}