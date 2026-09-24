/* { dg-do compile } */
/* { dg-options "-march=rv64gc_zbb_p0p21 -mabi=lp64 -O2" } */

/* Test USATI pattern recognition via RTL combine.
   When Zbb is enabled, min(max(x, 0), (1 << N) - 1) is recognized
   as smin(smax(x, 0), maxval) and converted to USATI.  */

static inline long max64(long a, long b) { return a > b ? a : b; }
static inline long min64(long a, long b) { return a < b ? a : b; }

long sat_u4(long x) { return min64(15, max64(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,4} } } */

long sat_u8(long x) { return min64(255, max64(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,8} } } */

long sat_u12(long x) { return min64(4095, max64(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,12} } } */

long sat_u16(long x) { return min64(65535, max64(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,16} } } */

long sat_u24(long x) { return min64(16777215, max64(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,24} } } */

long sat_u32(long x) { return min64(4294967295L, max64(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,32} } } */

/* Non-power-of-2 should NOT use usati, should use max+min */
long sat_not_pow2(long x) { return min64(100, max64(0, x)); }

/* Total: 6 usati instructions */
/* { dg-final { scan-assembler-times {\tusati\t} 6 } } */

