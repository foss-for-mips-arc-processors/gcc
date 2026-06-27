/* { dg-do compile } */
/* { dg-options "-mcpu=hs5x -O2" } */

#include <stdint.h>

uint64_t
__umul128(const uint64_t a, const uint64_t b, uint64_t * const productHi)
{
    const uint32_t aLo = (uint32_t)a;
    const uint32_t aHi = (uint32_t)(a >> 32);
    const uint32_t bLo = (uint32_t)b;
    const uint32_t bHi = (uint32_t)(b >> 32);

    const uint64_t b00 = (uint64_t)aLo * bLo;
    const uint64_t b01 = (uint64_t)aLo * bHi;
    const uint64_t b10 = (uint64_t)aHi * bLo;
    const uint64_t b11 = (uint64_t)aHi * bHi;

    const uint32_t b00Lo = (uint32_t)b00;
    const uint32_t b00Hi = (uint32_t)(b00 >> 32);

    const uint64_t mid1 = b10 + b00Hi;
    const uint32_t mid1Lo = (uint32_t)(mid1);
    const uint32_t mid1Hi = (uint32_t)(mid1 >> 32);

    const uint64_t mid2 = b01 + mid1Lo;
    const uint32_t mid2Lo = (uint32_t)(mid2);
    const uint32_t mid2Hi = (uint32_t)(mid2 >> 32);

    const uint64_t pHi = b11 + mid1Hi + mid2Hi;
    const uint64_t pLo = ((uint64_t)mid2Lo << 32) | b00Lo;

    *productHi = pHi;
    return pLo;
}

/* Check that the compiler generates vadd2+macdu */
/* { dg-final { scan-assembler "vadd23" } } */
/* { dg-final { scan-assembler "macdu" } } */

