#include "gift_config.h"

void stringToByte(u8* byteArray, const char* hexString);

void byteToWord(u32* dst, const u8* src, const size_t byteLen);
void wordToByte(u8* dst, const u32* src, const size_t wordLen);

void printByteData(u8* data, size_t byteLen);