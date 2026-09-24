/* { dg-do compile } */
/* { dg-options "-march=rv32gc_zbb_p0p21 -mabi=ilp32 -O2" } */

/* Test USATI pattern recognition via RTL combine for RV32.
   When Zbb is enabled, min(max(x, 0), (1 << N) - 1) is recognized
   as smin(smax(x, 0), maxval) and converted to USATI.  */

static inline int max32(int a, int b) { return a > b ? a : b; }
static inline int min32(int a, int b) { return a < b ? a : b; }

int sat_u4(int x) { return min32(15, max32(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,4} } } */

int sat_u8(int x) { return min32(255, max32(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,8} } } */

int sat_u12(int x) { return min32(4095, max32(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,12} } } */

int sat_u16(int x) { return min32(65535, max32(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,16} } } */

int sat_u24(int x) { return min32(16777215, max32(0, x)); }
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,24} } } */

/* Non-power-of-2 should NOT use usati, should use max+min */
int sat_not_pow2(int x) { return min32(100, max32(0, x)); }

/* Total: 5 usati instructions */
/* { dg-final { scan-assembler-times {\tusati\t} 5 } } */

