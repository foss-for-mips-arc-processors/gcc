/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>

uint16x4_t
test_pwsll_u16_imm (uint8x4_t rs1)
{
  return __riscv_pwsll_s_u16x4 (rs1, 3);
}

uint16x4_t
test_pwsll_u16_reg (uint8x4_t rs1, unsigned int shamt)
{
  return __riscv_pwsll_s_u16x4 (rs1, shamt);
}

uint32x2_t
test_pwsll_u32_imm (uint16x2_t rs1)
{
  return __riscv_pwsll_s_u32x2 (rs1, 5);
}

uint32x2_t
test_pwsll_u32_reg (uint16x2_t rs1, unsigned int shamt)
{
  return __riscv_pwsll_s_u32x2 (rs1, shamt);
}

int16x4_t
test_pwsla_i16_right_imm (int8x4_t rs1)
{
  return __riscv_pwsla_s_i16x4 (rs1, 3);
}

int16x4_t
test_pwsla_i16_left_imm (int8x4_t rs1)
{
  return __riscv_pwsla_s_i16x4 (rs1, 12);
}

int16x4_t
test_pwsla_i16_reg (int8x4_t rs1, unsigned int shamt)
{
  return __riscv_pwsla_s_i16x4 (rs1, shamt);
}

int32x2_t
test_pwsla_i32_right_imm (int16x2_t rs1)
{
  return __riscv_pwsla_s_i32x2 (rs1, 3);
}

int32x2_t
test_pwsla_i32_left_imm (int16x2_t rs1)
{
  return __riscv_pwsla_s_i32x2 (rs1, 20);
}

int32x2_t
test_pwsla_i32_reg (int16x2_t rs1, unsigned int shamt)
{
  return __riscv_pwsla_s_i32x2 (rs1, shamt);
}

uint8x4_t
test_pnsrl_u8_imm (uint16x4_t rs1)
{
  return __riscv_pnsrl_s_u8x4 (rs1, 8);
}

uint8x4_t
test_pnsrl_u8_reg (uint16x4_t rs1, unsigned int shamt)
{
  return __riscv_pnsrl_s_u8x4 (rs1, shamt);
}

uint16x2_t
test_pnsrl_u16_imm (uint32x2_t rs1)
{
  return __riscv_pnsrl_s_u16x2 (rs1, 16);
}

uint16x2_t
test_pnsrl_u16_reg (uint32x2_t rs1, unsigned int shamt)
{
  return __riscv_pnsrl_s_u16x2 (rs1, shamt);
}

int8x4_t
test_pnsra_i8_imm (int16x4_t rs1)
{
  return __riscv_pnsra_s_i8x4 (rs1, 8);
}

int8x4_t
test_pnsra_i8_reg (int16x4_t rs1, unsigned int shamt)
{
  return __riscv_pnsra_s_i8x4 (rs1, shamt);
}

int16x2_t
test_pnsra_i16_imm (int32x2_t rs1)
{
  return __riscv_pnsra_s_i16x2 (rs1, 16);
}

int16x2_t
test_pnsra_i16_reg (int32x2_t rs1, unsigned int shamt)
{
  return __riscv_pnsra_s_i16x2 (rs1, shamt);
}

int8x4_t
test_pnsrar_i8_imm (int16x4_t rs1)
{
  return __riscv_pnsrar_s_i8x4 (rs1, 8);
}

int8x4_t
test_pnsrar_i8_reg (int16x4_t rs1, unsigned int shamt)
{
  return __riscv_pnsrar_s_i8x4 (rs1, shamt);
}

int16x2_t
test_pnsrar_i16_imm (int32x2_t rs1)
{
  return __riscv_pnsrar_s_i16x2 (rs1, 16);
}

int16x2_t
test_pnsrar_i16_reg (int32x2_t rs1, unsigned int shamt)
{
  return __riscv_pnsrar_s_i16x2 (rs1, shamt);
}

/* { dg-final { scan-assembler-times {\mzip8p\M} 5 } } */
/* { dg-final { scan-assembler-times {\mzip16p\M} 5 } } */
/* { dg-final { scan-assembler-times {\munzip8p\M} 6 } } */
/* { dg-final { scan-assembler-times {\munzip16p\M} 6 } } */
/* { dg-final { scan-assembler-times {\mpsext\.h\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsext\.w\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpslli\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsll\.hs\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpslli\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsll\.ws\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsrli\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrl\.hs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrli\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrl\.ws\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrai\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsra\.hs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrai\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsra\.ws\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsshar\.hs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsshar\.ws\M} 1 } } */
/* { dg-final { scan-assembler-times {\mandi\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnegw\M} 2 } } */
