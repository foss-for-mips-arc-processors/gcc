/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */

/* Test PLI/PLUI for scalar DI mode constants (RV64).
   These constants would previously be loaded from the constant pool (.rodata).
   Now they should use pli.b/pli.h/pli.w/plui.h/plui.w.

   Note: On RV64, 32-bit values like 0x01010101 CANNOT use PLI because
   pli.b produces 0x0101010101010101 (64-bit broadcast), not 0x0000000001010101
   (zero-extended 32-bit). Only fully replicated 64-bit values can use PLI.  */

typedef unsigned long long uint64_t;

/* pli.b: replicated byte patterns (64-bit) */
uint64_t pli_b_01 (void) { return 0x0101010101010101ULL; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,1} } } */

uint64_t pli_b_55 (void) { return 0x5555555555555555ULL; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,85} } } */

uint64_t pli_b_aa (void) { return 0xAAAAAAAAAAAAAAAAULL; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,-86} } } */

/* pli.h: replicated halfword patterns (64-bit, simm10) */
uint64_t pli_h_0001 (void) { return 0x0001000100010001ULL; }
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,1} } } */

uint64_t pli_h_01ff (void) { return 0x01FF01FF01FF01FFULL; }
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,511} } } */

uint64_t pli_h_fe00 (void) { return 0xFE00FE00FE00FE00ULL; }
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,-512} } } */

/* pli.w: replicated word patterns (64-bit only, simm10) */
uint64_t pli_w_00000001 (void) { return 0x0000000100000001ULL; }
/* { dg-final { scan-assembler {pli\.w\t[a-x0-9]+,1} } } */

uint64_t pli_w_000001ff (void) { return 0x000001FF000001FFULL; }
/* { dg-final { scan-assembler {pli\.w\t[a-x0-9]+,511} } } */

uint64_t pli_w_fffffe00 (void) { return 0xFFFFFE00FFFFFE00ULL; }
/* { dg-final { scan-assembler {pli\.w\t[a-x0-9]+,-512} } } */

/* plui.h: replicated halfword with 6-bit shift (simm10 << 6)
   The halfword value must NOT fit in simm10 [-512, 511].  */
uint64_t plui_h_0800 (void) { return 0x0800080008000800ULL; }  /* 2048 >> 6 = 32 */
/* { dg-final { scan-assembler {plui\.h\t[a-x0-9]+,32} } } */

uint64_t plui_h_0c00 (void) { return 0x0C000C000C000C00ULL; }  /* 3072 >> 6 = 48 */
/* { dg-final { scan-assembler {plui\.h\t[a-x0-9]+,48} } } */

/* plui.w: replicated word with 22-bit shift (simm10 << 22, 64-bit only)
   The word value must NOT fit in simm10 [-512, 511], and
   (word & 0x3fffff) must be 0, and (word >> 22) in [-512, 511].  */
uint64_t plui_w_00400000 (void) { return 0x0040000000400000ULL; }  /* 4194304 >> 22 = 1 */
/* { dg-final { scan-assembler {plui\.w\t[a-x0-9]+,1} } } */

uint64_t plui_w_00c00000 (void) { return 0x00C0000000C00000ULL; }  /* 12582912 >> 22 = 3 */
/* { dg-final { scan-assembler {plui\.w\t[a-x0-9]+,3} } } */

/* Constants that should NOT use PLI (prefer li/lui) */
uint64_t li_0 (void) { return 0x0000000000000000ULL; }
uint64_t li_minus1 (void) { return 0xFFFFFFFFFFFFFFFFULL; }

/* 32-bit values cannot use PLI on RV64 */
uint64_t no_pli_32bit (void) { return 0x0000000001010101ULL; }

/* Total counts */
/* { dg-final { scan-assembler-times {pli\.b} 3 } } */
/* { dg-final { scan-assembler-times {pli\.h} 3 } } */
/* { dg-final { scan-assembler-times {pli\.w} 3 } } */
/* { dg-final { scan-assembler-times {plui\.h} 2 } } */