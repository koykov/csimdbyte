#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include "index_sse4.h"
#include "cmp.h"

inline int64_t __attribute__((always_inline)) index_sse4_long(const char *s, int64_t sz, const char *ss, int64_t ssz) {
    const __m128i N = _mm_loadu_si128((__m128i*)ss);

    for (int64_t i = 0; i < sz; i += 16) {
        const int mode = _SIDD_UBYTE_OPS
                         | _SIDD_CMP_EQUAL_ORDERED;
        const __m128i D   = _mm_loadu_si128((__m128i*)(s + i));
        const __m128i res = _mm_cmpestrm(N, (int)ssz, D, (int)(sz - i), mode);
        uint64_t mask = _mm_cvtsi128_si64(res);

        while (mask != 0) {
            int bitpos = __builtin_ctz(mask);
            if (memcmp(s + i + bitpos + 1, ss + 1, ssz - 1) == 0) {
                return i + bitpos;
            }
            mask = mask & (mask - 1);
        }
    }
    return -1;
}

inline int64_t __attribute__((always_inline)) index_sse4_cmpfn(const char* s, int64_t sz, const char* ss, int64_t ssz, cmpfn fn) {
    const __m128i N = _mm_loadu_si128((__m128i*)ss);
    for (int64_t i = 0; i < sz; i += 16) {
        const int mode = _SIDD_UBYTE_OPS
                         | _SIDD_CMP_EQUAL_ORDERED;
        const __m128i D   = _mm_loadu_si128((__m128i*)(s + i));
        const __m128i res = _mm_cmpestrm(N, (int)ssz, D, (int)(sz - i), mode);
        uint64_t mask = _mm_cvtsi128_si64(res);

        while (mask != 0) {
            int bitpos = __builtin_ctz(mask);
            if (fn(s + i + bitpos + 1, ss + 1)) {
                return i + bitpos;
            }
            mask = mask & (mask - 1);
        }
    }

    return -1;
}

int64_t index_sse4(const char *s, int64_t sz, const char *ss, int64_t ssz) {
    if (sz < ssz) { return -1; }
    int64_t pos;
    switch (ssz) {
        case 0:
            return 0;
        case 1: {
            const char *res = (const char *) (strchr(s, ss[0]));
            return (res != NULL) ? (int)(res - s) : -1;
        }
        case 2:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp0);
            break;
        case 3:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp1);
            break;
        case 4:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp2);
            break;
        case 5:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp3);
            break;
        case 6:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp4);
            break;
        case 7:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp5);
            break;
        case 8:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp6);
            break;
        case 9:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp7);
            break;
        case 10:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp8);
            break;
        case 11:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp9);
            break;
        case 12:
            pos = index_sse4_cmpfn(s, sz, ss, ssz, cmp10);
            break;
        default:
            pos = index_sse4_long(s, sz, ss, ssz);
            break;
    }
    if (pos > sz-ssz) pos = -1;
    return pos;
}
