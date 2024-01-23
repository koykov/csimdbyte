#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include "index_avx2.h"
#include "cmp.h"

inline int64_t __attribute__((always_inline)) index_avx2_long(const char* s, int64_t sz, const char* ss, int64_t ssz) {
    const __m256i first = _mm256_set1_epi8(ss[0]);
    const __m256i last  = _mm256_set1_epi8(ss[ssz - 1]);

    for (int64_t i = 0; i < sz; i += 32) {
        const __m256i block_first = _mm256_loadu_si256((const __m256i*)(s + i));
        const __m256i block_last  = _mm256_loadu_si256((const __m256i*)(s + i + ssz - 1));

        const __m256i eq_first = _mm256_cmpeq_epi8(first, block_first);
        const __m256i eq_last  = _mm256_cmpeq_epi8(last, block_last);

        uint32_t mask = _mm256_movemask_epi8(_mm256_and_si256(eq_first, eq_last));
        while (mask != 0) {
            int bitpos = __builtin_ctz(mask);
            if (memcmp(s + i + bitpos + 1, ss + 1, ssz - 2) == 0) {
                return i + bitpos;
            }
            mask = mask & (mask - 1);
        }
    }

    return -1;
}

inline int64_t __attribute__((always_inline)) index_2_avx2(const char* s, int64_t sz, const char* ss, int64_t ssz) {
    __m256i broadcasted[ssz];
    for (unsigned i=0; i < ssz; i++) {
        broadcasted[i] = _mm256_set1_epi8(ss[i]);
    }

    __m256i curr = _mm256_loadu_si256((const __m256i*)(s));
    for (int64_t i = 0; i < sz; i += 32) {
        const __m256i next = _mm256_loadu_si256((const __m256i*)(s + i + 32));
        __m256i eq = _mm256_cmpeq_epi8(curr, broadcasted[0]);
        __m256i next1;
        next1 = _mm256_inserti128_si256(next1, _mm256_extracti128_si256(curr, 1), 0); // b
        next1 = _mm256_inserti128_si256(next1, _mm256_extracti128_si256(next, 0), 1); // c
        for (int64_t j=1; j < ssz; j++) {
            const __m256i substring = _mm256_alignr_epi8(next1, curr, (int)j);
            eq = _mm256_and_si256(eq, _mm256_cmpeq_epi8(substring, broadcasted[j]));
        }
        curr = next;

        const uint32_t mask = _mm256_movemask_epi8(eq);
        if (mask != 0) {
            return i + __builtin_ctzl(mask);
        }
    }

    return -1;
}

inline int64_t __attribute__((always_inline)) index_avx2_cmpfn(const char* s, int64_t sz, const char* ss, int64_t ssz, cmpfn fn) {
    const __m256i first = _mm256_set1_epi8(ss[0]);
    const __m256i last  = _mm256_set1_epi8(ss[ssz - 1]);

    for (int64_t i = 0; i < sz; i += 32) {
        const __m256i block_first = _mm256_loadu_si256((const __m256i*)(s + i));
        const __m256i block_last  = _mm256_loadu_si256((const __m256i*)(s + i + ssz - 1));

        const __m256i eq_first = _mm256_cmpeq_epi8(first, block_first);
        const __m256i eq_last  = _mm256_cmpeq_epi8(last, block_last);

        uint32_t mask = _mm256_movemask_epi8(_mm256_and_si256(eq_first, eq_last));
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

int64_t index_avx2(const char *s, int64_t sz, const char *ss, int64_t ssz) {
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
            pos = index_2_avx2(s, sz, ss, ssz);
            break;
        case 3:
            pos = index_avx2_cmpfn(s, sz, ss, ssz, cmp1);
            break;
        case 4:
            pos = index_avx2_cmpfn(s, sz, ss, ssz, cmp2);
            break;
        case 5:
        case 6:
            pos = index_avx2_cmpfn(s, sz, ss, ssz, cmp4);
            break;
        case 7:
            pos = index_avx2_cmpfn(s, sz, ss, ssz, cmp5);
            break;
        case 8:
            pos = index_avx2_cmpfn(s, sz, ss, ssz, cmp6);
            break;
        case 9:
        case 10:
            pos = index_avx2_cmpfn(s, sz, ss, ssz, cmp8);
            break;
        case 11:
            pos = index_avx2_cmpfn(s, sz, ss, ssz, cmp9);
            break;
        case 12:
            pos = index_avx2_cmpfn(s, sz, ss, ssz, cmp10);
            break;
        default:
            pos = index_avx2_long(s, sz, ss, ssz);
            break;
    }
    if (pos > sz-ssz) pos = -1;
    return pos;
}
