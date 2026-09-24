/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */

/* Test PLUI.W instruction for P-extension (RV64 only).
   PLUI.W loads (imm10 << 22) to all word positions.  */

typedef unsigned long long uint64_t;

/* Valid PLUI.W patterns: (imm10 << 22) where imm10 in [-512, 511].  */
uint64_t plui_w_511 (void) { return 0x7FC000007FC00000ULL; }
uint64_t plui_w_1 (void) { return 0x0040000000400000ULL; }
uint64_t plui_w_neg512 (void) { return 0x8000000080000000ULL; }
uint64_t plui_w_16 (void) { return 0x0400000004000000ULL; }
uint64_t plui_w_neg16 (void) { return 0xFC000000FC000000ULL; }

/* Lower 22 bits not zero: should NOT use plui.w directly.  */
uint64_t not_plui_w_1 (void) { return 0x7FC000017FC00001ULL; }

/* Verify the specific patterns we expect.  Using scan-assembler for
   individual immediates rather than a total count, as optimization
   may use plui.w as an intermediate step for constructing other values.  */
/* { dg-final { scan-assembler {plui\.w\t[a-x0-9]+,511} } } */
/* { dg-final { scan-assembler {plui\.w\t[a-x0-9]+,1} } } */
/* { dg-final { scan-assembler {plui\.w\t[a-x0-9]+,-512} } } */
/* { dg-final { scan-assembler {plui\.w\t[a-x0-9]+,16} } } */
/* { dg-final { scan-assembler {plui\.w\t[a-x0-9]+,-16} } } */
