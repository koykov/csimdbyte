#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include "index_sse2.h"
#include "cmp.h"

inline int __attribute__((always_inline)) index_sse2_long(const char *s, int sz, const char *ss, int ssz) {
    const __m128i first = _mm_set1_epi8(ss[0]);
    const __m128i last  = _mm_set1_epi8(ss[ssz - 1]);

    for (int i = 0; i < sz; i += 16) {
        const __m128i block_first = _mm_loadu_si128((__m128i*)(s + i));
        const __m128i block_last  = _mm_loadu_si128((__m128i*)(s + i + ssz - 1));

        const __m128i eq_first = _mm_cmpeq_epi8(first, block_first);
        const __m128i eq_last  = _mm_cmpeq_epi8(last, block_last);

        uint16_t mask = _mm_movemask_epi8(_mm_and_si128(eq_first, eq_last));
        while (mask != 0) {
            int bitpos = __builtin_ctz(mask);
            if (memcmp(s + i + bitpos + 1, ss + 1, ssz - 2) == 0) {
                return i + bitpos;
            }
            mask = mask & (mask - 1);
        }
    }
}

inline int __attribute__((always_inline)) index_sse2_cmpfn(const char* s, int sz, const char* ss, int ssz, cmpfn fn) {
    const __m128i first = _mm_set1_epi8(ss[0]);
    const __m128i last  = _mm_set1_epi8(ss[ssz - 1]);

    for (int i = 0; i < sz; i += 16) {
        const __m128i block_first = _mm_loadu_si128((__m128i*)(s + i));
        const __m128i block_last  = _mm_loadu_si128((__m128i*)(s + i + ssz - 1));

        const __m128i eq_first = _mm_cmpeq_epi8(first, block_first);
        const __m128i eq_last  = _mm_cmpeq_epi8(last, block_last);

        uint32_t mask = _mm_movemask_epi8(_mm_and_si128(eq_first, eq_last));
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

int index_sse2(const char *s, int sz, const char *ss, int ssz) {
    if (sz < ssz) { return -1; }
    int pos;
    switch (ssz) {
        case 0:
            return 0;
        case 1: {
            const char *res = (const char *) (strchr(s, ss[0]));
            return (res != NULL) ? (int)(res - s) : -1;
        }
        case 2:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp0);
            break;
        case 3:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp1);
            break;
        case 4:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp2);
            break;
        case 5:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp3);
            break;
        case 6:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp4);
            break;
        case 7:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp5);
            break;
        case 8:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp6);
            break;
        case 9:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp7);
            break;
        case 10:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp8);
            break;
        case 11:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp9);
            break;
        case 12:
            pos = index_sse2_cmpfn(s, sz, ss, ssz, cmp10);
            break;
        default:
            pos = index_sse2_long(s, sz, ss, ssz);
            break;
    }
    if (pos > sz-ssz) pos = -1;
    return pos;
}
