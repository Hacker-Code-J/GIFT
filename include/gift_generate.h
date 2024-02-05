#include "gift_config.h"

#ifndef _GIFT_GENERATE_H
#define _GIFT_GENERATE_H

void generate_sbox(u8 S[16]);
void generate_permbits64_box(u8 permbits[64]);
void generate_permbits128_box(u8 permbits[128]);

#endif /* _GIFT_GENERATE_H */