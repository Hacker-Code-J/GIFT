#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <x86intrin.h> // for __rdtscp and __rdtsc

#ifndef _GIFT_CONFIG_H
#define _GIFT_CONFIG_H

typedef int8_t i8;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

#define GIFT64 (u8)64
#define GIFT128 (u8)128

#endif /* _GIFT_CONFIG_H */