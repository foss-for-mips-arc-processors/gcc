/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>

#define TEST_SHIFT(NAME, TYPE_IN, TYPE_OUT, INTRINSIC) \
TYPE_OUT test_##NAME##_imm (TYPE_IN rs1)                 \
{                                                        \
  return INTRINSIC (rs1, 8);                             \
}                                                        \
                                                         \
TYPE_OUT test_##NAME##_reg (TYPE_IN rs1, unsigned shamt) \
{                                                        \
  return INTRINSIC (rs1, shamt);                         \
}

TEST_SHIFT (pnclipu_u8, uint16x4_t, uint8x4_t,
	    __riscv_pnclipu_s_u8x4)
TEST_SHIFT (pnclipu_u16, uint32x2_t, uint16x2_t,
	    __riscv_pnclipu_s_u16x2)
TEST_SHIFT (pnclipru_u8, uint16x4_t, uint8x4_t,
	    __riscv_pnclipru_s_u8x4)
TEST_SHIFT (pnclipru_u16, uint32x2_t, uint16x2_t,
	    __riscv_pnclipru_s_u16x2)
TEST_SHIFT (pnclip_i8, int16x4_t, int8x4_t, __riscv_pnclip_s_i8x4)
TEST_SHIFT (pnclip_i16, int32x2_t, int16x2_t, __riscv_pnclip_s_i16x2)
TEST_SHIFT (pnclipr_i8, int16x4_t, int8x4_t, __riscv_pnclipr_s_i8x4)
TEST_SHIFT (pnclipr_i16, int32x2_t, int16x2_t, __riscv_pnclipr_s_i16x2)

/* { dg-final { scan-assembler-times {psrli\.h} 1 } } */
/* { dg-final { scan-assembler-times {psrli\.w} 1 } } */
/* { dg-final { scan-assembler-times {psrl\.hs} 1 } } */
/* { dg-final { scan-assembler-times {psrl\.ws} 1 } } */
/* { dg-final { scan-assembler-times {psshlr\.hs} 2 } } */
/* { dg-final { scan-assembler-times {psshlr\.ws} 2 } } */
/* { dg-final { scan-assembler-times {pnclipup\.b} 4 } } */
/* { dg-final { scan-assembler-times {pnclipup\.h} 4 } } */
/* { dg-final { scan-assembler-times {psrai\.h} 1 } } */
/* { dg-final { scan-assembler-times {psrai\.w} 1 } } */
/* { dg-final { scan-assembler-times {psra\.hs} 1 } } */
/* { dg-final { scan-assembler-times {psra\.ws} 1 } } */
/* { dg-final { scan-assembler-times {psrari\.h} 1 } } */
/* { dg-final { scan-assembler-times {psrari\.w} 1 } } */
/* { dg-final { scan-assembler-times {psshar\.hs} 1 } } */
/* { dg-final { scan-assembler-times {psshar\.ws} 1 } } */
/* { dg-final { scan-assembler-times {pnclipp\.b} 4 } } */
/* { dg-final { scan-assembler-times {pnclipp\.h} 4 } } */
/* { dg-final { scan-assembler-times {andi} 4 } } */
/* { dg-final { scan-assembler-times {negw} 4 } } */
/* { dg-final { scan-assembler-not {li\s+[^,]+,0} } } */
