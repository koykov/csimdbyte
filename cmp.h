#ifndef CSIMDBYTE_CMP_H
#define CSIMDBYTE_CMP_H

#include "stdbool.h"
#include "stdint.h"

typedef bool (*cmpfn)(const char*, const char*);

bool cmp0(const char *a, const char *b) { return true; }

bool cmp1(const char *a, const char *b) { return a[0] == b[0]; }

bool cmp2(const char *a, const char *b) {
    return *(uint16_t*)(a) ==  *(uint16_t*)(b);
}

bool cmp3(const char *a, const char *b) {
    uint32_t a1 = *(uint16_t*)(a);
    uint32_t b1 = *(uint16_t*)(b);
    return a1 == b1 && a[2] == b[2];
}

bool cmp4(const char *a, const char *b) {
    uint32_t a1 = *(uint32_t*)(a);
    uint32_t b1 = *(uint32_t*)(b);
    return a1 == b1;
}

bool cmp5(const char *a, const char *b) {
    const uint32_t a1 = *(uint32_t*)(a);
    const uint32_t b1 = *(uint32_t*)(b);
    return a1 == b1 && a[4] == b[4];
}

bool cmp6(const char *a, const char *b) {
    const uint64_t a1 = *(uint64_t*)(a);
    const uint64_t b1 = *(uint64_t*)(b);
    return ((a1 ^ b1) & 0x0000fffffffffffflu) == 0;
}

bool cmp7(const char *a, const char *b) {
    const uint64_t a1 = *(uint64_t*)(a);
    const uint64_t b1 = *(uint64_t*)(b);
    return ((a1 ^ b1) & 0x00fffffffffffffflu) == 0;
}

bool cmp8(const char *a, const char *b) {
    const uint64_t a1 = *(uint64_t*)(a);
    const uint64_t b1 = *(uint64_t*)(b);
    return a1 == b1;
}

bool cmp9(const char *a, const char *b) {
    const uint64_t a1 = *(uint64_t*)(a);
    const uint64_t b1 = *(uint64_t*)(b);
    return a1 == b1 && a[8] == b[8];
}

bool cmp10(const char *a, const char *b) {
    const uint64_t al = *(uint64_t*)(a);
    const uint64_t bl = *(uint64_t*)(b);
    const uint16_t ah = *(uint16_t*)(a + 8);
    const uint16_t bh = *(uint16_t*)(b + 8);
    return (al == bl) & (ah == bh);
}

bool cmp11(const char *a, const char *b) {
    const uint64_t al = *(uint64_t*)(a);
    const uint64_t bl = *(uint64_t*)(b);
    const uint32_t ah = *(uint32_t*)(a + 8);
    const uint32_t bh = *(uint32_t*)(b + 8);
    return (al == bl) & ((ah & 0x00ffffff) == (bh & 0x00ffffff));
}

bool cmp12(const char *a, const char *b) {
    const uint64_t al = *(uint64_t*)(a);
    const uint64_t bl = *(uint64_t*)(b);
    const uint32_t ah = *(uint32_t*)(a + 8);
    const uint32_t bh = *(uint32_t*)(b + 8);
    return (al == bl) & (ah == bh);
}

#endif //CSIMDBYTE_CMP_H
