/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>

uint64_t
test_mulu_w00_u64 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_mulu_w00_u64 (rs1, rs2);
}

uint64_t
test_mulu_w01_u64 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_mulu_w01_u64 (rs1, rs2);
}

uint64_t
test_mulu_w11_u64 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_mulu_w11_u64 (rs1, rs2);
}

/* { dg-final { scan-assembler-times {mulu\.w00} 1 } } */
/* { dg-final { scan-assembler-times {mulu\.w01} 1 } } */
/* { dg-final { scan-assembler-times {mulu\.w11} 1 } } */
