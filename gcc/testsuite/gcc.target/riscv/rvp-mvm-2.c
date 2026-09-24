/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */

typedef unsigned int uint32_t;

/* Bitwise select operations using MVM/MVMN on RV32. */

uint32_t test_select_1 (uint32_t rd, uint32_t rs1, uint32_t mask)
{
  return (~mask & rd) | (mask & rs1);
}

uint32_t test_select_2 (uint32_t rd, uint32_t rs1, uint32_t mask)
{
  return (mask & rd) | (~mask & rs1);
}

/* { dg-final { scan-assembler "\\tmvmn?\\t" } } */
