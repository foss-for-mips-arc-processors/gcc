/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32gcp0p6 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef int int32_t;

/* Shift before adding the rounding bit so the intermediate does not
   overflow.  RV32 supports shift amounts 1-31 (uimm5).  */

int32_t test_srari_4 (int32_t a)
{
  return ((a >> 3) + 1) >> 1;
}

int32_t test_srari_8 (int32_t a)
{
  return ((a >> 7) + 1) >> 1;
}

int32_t test_srari_16 (int32_t a)
{
  return ((a >> 15) + 1) >> 1;
}

/* Test maximum shift amount (31) */
int32_t test_srari_31 (int32_t a)
{
  return ((a >> 30) + 1) >> 1;
}

/* { dg-final { scan-assembler-times "\\tsrari\\t" 4 } } */
