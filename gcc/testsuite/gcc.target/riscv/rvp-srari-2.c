/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef int int32_t;

/* SRARI: rounding arithmetic shift right by immediate
   rd = (rs1 + (1 << (shamt-1))) >> shamt
   RV32 supports shift amounts 1-31 (uimm5) */

int32_t test_srari_4 (int32_t a)
{
  return (a + (1 << 3)) >> 4;
}

int32_t test_srari_8 (int32_t a)
{
  return (a + (1 << 7)) >> 8;
}

int32_t test_srari_16 (int32_t a)
{
  return (a + (1 << 15)) >> 16;
}

/* Test maximum shift amount (31) */
int32_t test_srari_31 (int32_t a)
{
  return (a + (1 << 30)) >> 31;
}

/* { dg-final { scan-assembler-times "\\tsrari\\t" 4 } } */
