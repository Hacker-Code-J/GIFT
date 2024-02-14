#include "gift_config.h"

#ifndef _GIFT_GENERATE_H
#define _GIFT_GENERATE_H

void generate_round_constants(u8 rCon[48]);

void generate_sbox(u8 S[16]);
void generate_permBits64_box(u8 permBits[64]);
void generate_permBits128_box(u8 perBbits[128]);

#endif /* _GIFT_GENERATE_H */