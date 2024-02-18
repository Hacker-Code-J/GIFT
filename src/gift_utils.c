#include "gift_utils.h"

void stringToByte(u8* byteArray, const char* hexString) {
    size_t length = strlen(hexString);
    for (size_t i = 0; i < length; i+=2) {
        sscanf(&hexString[i], "%2hhx", &byteArray[(length / 2 - 1) - (i / 2)]);
    }
}

// Function to convert u8 array to u32 array
// b7|b6|b5|b4|b3|b2|b1|b0 <=> byte[8] = { b0, b1, b2, b3, b4, b5, b6, b7 }
// -> word[0] = b3 | b2 | b1 | b0 = w0
// -> word[1] = b7 | b6 | b5 | b4 = w1
void byteToWord(u32* dst, const u8* src, const size_t byteLen) {
    for (size_t i = 0; i < byteLen / 4; i++) {
        dst[i] = (u32)src[4 * i + 3] << 0x18 |
                 (u32)src[4 * i + 2] << 0x10 |
                 (u32)src[4 * i + 1] << 0x08 |
                 (u32)src[4 * i    ];
    }
}

// Function to convert u32 array to u8 array
// w1|w0 <=> word[2] = { w0, w1 }
// -> byte[0] = (w0 >> 0x00) & 0xFF = b0
// -> byte[1] = (w0 >> 0x08) & 0xFF = b1
// -> byte[2] = (w0 >> 0x10) & 0xFF = b2
// -> byte[3] = (w0 >> 0x18) & 0xFF = b3
void wordToByte(u8* dst, const u32* src, const size_t wordLen) {
    for (size_t i = 0; i < wordLen; i++) {
        dst[4 * i    ] = (u8)((src[i]        ) & 0xFF);
        dst[4 * i + 1] = (u8)((src[i] >> 0x08) & 0xFF);
        dst[4 * i + 2] = (u8)((src[i] >> 0x10) & 0xFF);
        dst[4 * i + 3] = (u8)((src[i] >> 0x18) & 0xFF);
    }
}

void printByteData(u8* data, size_t byteLen) {
    for (i32 i = byteLen - 1; i >=0; i--) {
        printf("%02x:", data[i]);
    } puts("");
}

// Function to measure CPU cycle used by a function
void measure_cpu_cycle(void (*func)(u8*, const u8*, const u8*), u8* dst, const u8* src, const u8* key) {
    u32 ui;
    u64 start, end;
    const u64 num_runs = 10000;
    func(dst, src, key);

    start = __rdtsc();
    for (int i = 0; i < num_runs; i++)
        func(dst, src, key);
    end = __rdtscp(&ui);
    
    printf("%ld\n", (end - start) / num_runs);
}

// Function to measure CPU time used by a function
void measure_cpu_time(void (*func)(u8*, const u8*, const u8*), u8* dst, const u8* src, const u8* key) {
    struct timespec start, end;
    const long num_runs = 10000;

    func(dst, src, key);
    // Start time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    // Call the function
    for (i32 i = 0; i < num_runs; i++) {
        func(dst, src, key);
    }

    // End time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    // Calculate and print the CPU time used in nanoseconds
    u64 ns = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
    printf("%ld\n", ns / num_runs);
}