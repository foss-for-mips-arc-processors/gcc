/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef long long int64_t;
typedef int int32_t;

/* SRARI: rounding arithmetic shift right by immediate
   rd = (rs1 + (1 << (shamt-1))) >> shamt
   RV64 supports shift amounts 1-63 (uimm6) */

/* Test int64_t with various shift amounts */
int64_t test_srari_di_4 (int64_t a)
{
  return (a + (1LL << 3)) >> 4;
}

int64_t test_srari_di_8 (int64_t a)
{
  return (a + (1LL << 7)) >> 8;
}

int64_t test_srari_di_16 (int64_t a)
{
  return (a + (1LL << 15)) >> 16;
}

/* Test larger shift amounts (> 31) to exercise uimm6 range */
int64_t test_srari_di_32 (int64_t a)
{
  return (a + (1LL << 31)) >> 32;
}

int64_t test_srari_di_48 (int64_t a)
{
  return (a + (1LL << 47)) >> 48;
}

/* Test int32_t on RV64 (should generate srari with SI mode) */
int32_t test_srari_si_4 (int32_t a)
{
  return (a + (1 << 3)) >> 4;
}

int32_t test_srari_si_8 (int32_t a)
{
  return (a + (1 << 7)) >> 8;
}

/* { dg-final { scan-assembler-times "\\tsrari\\t" 7 } } */
