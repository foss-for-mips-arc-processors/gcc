/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */

/* Test PLI/PLUI for scalar SI mode constants (RV32).
   These constants would previously be loaded via lui+addi or from
   the constant pool (.rodata). Now they should use pli.b/pli.h/plui.h.  */

typedef unsigned int uint32_t;

/* pli.b: replicated byte patterns */
uint32_t pli_b_01 (void) { return 0x01010101U; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,1} } } */

uint32_t pli_b_55 (void) { return 0x55555555U; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,85} } } */

uint32_t pli_b_aa (void) { return 0xAAAAAAAAU; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,-86} } } */

/* pli.h: replicated halfword patterns (simm10) */
uint32_t pli_h_0001 (void) { return 0x00010001U; }
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,1} } } */

uint32_t pli_h_01ff (void) { return 0x01FF01FFU; }
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,511} } } */

uint32_t pli_h_fe00 (void) { return 0xFE00FE00U; }
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,-512} } } */

/* plui.h: replicated halfword with 6-bit shift (simm10 << 6)
   The halfword value must NOT fit in simm10 [-512, 511], but
   (hw >> 6) must fit in simm10, and (hw & 0x3f) must be 0.
   Also, the full 32-bit value must not be loadable by lui alone.  */
uint32_t plui_h_0800 (void) { return 0x08000800U; }  /* 2048 >> 6 = 32 */
/* { dg-final { scan-assembler {plui\.h\t[a-x0-9]+,32} } } */

uint32_t plui_h_0c00 (void) { return 0x0C000C00U; }  /* 3072 >> 6 = 48 */
/* { dg-final { scan-assembler {plui\.h\t[a-x0-9]+,48} } } */

/* Constants that should NOT use PLI (prefer li/lui) */
uint32_t li_0 (void) { return 0x00000000U; }
uint32_t li_minus1 (void) { return 0xFFFFFFFFU; }
uint32_t lui_simple (void) { return 0x12345000U; }

/* Total: 8 pli/plui instructions */
/* { dg-final { scan-assembler-times {pli\.b} 3 } } */
/* { dg-final { scan-assembler-times {pli\.h} 3 } } */
/* { dg-final { scan-assembler-times {plui\.h} 2 } } */
