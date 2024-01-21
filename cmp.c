#ifndef CSIMDBYTE_CMP_CPP
#define CSIMDBYTE_CMP_CPP

#include "cmp.h"
#include "stdint.h"

bool cmp0(const char *a, const char *b) { return true; }

bool cmp1(const char* a, const char* b) {
    return a[0] == b[0];
}

bool cmp2(const char* a, const char* b) {
    const uint16_t A = *(const uint16_t*)(a);
    const uint16_t B = *(const uint16_t*)(b);
    return A == B;
}

bool cmp3(const char* a, const char* b) {

#ifdef USE_SIMPLE_MEMCMP
    return cmp2(a, b) && cmp1(a + 2, b + 2);
#else
    const uint32_t A = *(const uint32_t*)(a);
    const uint32_t B = *(const uint32_t*)(b);
    return (A & 0x00ffffff) == (B & 0x00ffffff);
#endif
}

bool cmp4(const char* a, const char* b) {

    const uint32_t A = *(const uint32_t*)(a);
    const uint32_t B = *(const uint32_t*)(b);
    return A == B;
}

bool cmp5(const char* a, const char* b) {

#ifdef USE_SIMPLE_MEMCMP
    return cmp4(a, b) && cmp1(a + 4, b + 4);
#else
    const uint64_t A = *(const uint64_t*)(a);
    const uint64_t B = *(const uint64_t*)(b);
    return ((A ^ B) & 0x000000fffffffffflu) == 0;
#endif
}

bool cmp6(const char* a, const char* b) {

#ifdef USE_SIMPLE_MEMCMP
    return cmp4(a, b) && cmp2(a + 4, b + 4);
#else
    const uint64_t A = *(const uint64_t*)(a);
    const uint64_t B = *(const uint64_t*)(b);
    return ((A ^ B) & 0x0000fffffffffffflu) == 0;
#endif
}

bool cmp7(const char* a, const char* b) {

#ifdef USE_SIMPLE_MEMCMP
    return cmp4(a, b) && cmp3(a + 4, b + 4);
#else
    const uint64_t A = *(const uint64_t*)(a);
    const uint64_t B = *(const uint64_t*)(b);
    return ((A ^ B) & 0x00fffffffffffffflu) == 0;
#endif
}

bool cmp8(const char* a, const char* b) {

    const uint64_t A = *(const uint64_t*)(a);
    const uint64_t B = *(const uint64_t*)(b);
    return A == B;
}

bool cmp9(const char* a, const char* b) {

    const uint64_t A = *(const uint64_t*)(a);
    const uint64_t B = *(const uint64_t*)(b);
    return (A == B) & (a[8] == b[8]);
}

bool cmp10(const char* a, const char* b) {

    const uint64_t Aq = *(const uint64_t*)(a);
    const uint64_t Bq = *(const uint64_t*)(b);
    const uint16_t Aw = *(const uint16_t*)(a + 8);
    const uint16_t Bw = *(const uint16_t*)(b + 8);
    return (Aq == Bq) & (Aw == Bw);
}

bool cmp11(const char* a, const char* b) {

#ifdef USE_SIMPLE_MEMCMP
    return cmp8(a, b) && cmp3(a + 8, b + 8);
#else
    const uint64_t Aq = *(const uint64_t*)(a);
    const uint64_t Bq = *(const uint64_t*)(b);
    const uint32_t Ad = *(const uint32_t*)(a + 8);
    const uint32_t Bd = *(const uint32_t*)(b + 8);
    return (Aq == Bq) & ((Ad & 0x00ffffff) == (Bd & 0x00ffffff));
#endif
}

bool cmp12(const char* a, const char* b) {

    const uint64_t Aq = *(const uint64_t*)(a);
    const uint64_t Bq = *(const uint64_t*)(b);
    const uint32_t Ad = *(const uint32_t*)(a + 8);
    const uint32_t Bd = *(const uint32_t*)(b + 8);
    return (Aq == Bq) & (Ad == Bd);
}

#endif //CSIMDBYTE_CMP_CPP
