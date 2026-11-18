/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p6 -mabi=lp64 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef long long int64_t;
typedef int int32_t;

/* Shift before adding the rounding bit so the intermediate does not
   overflow.  RV64 supports shift amounts 1-63 (uimm6).  */

/* Test int64_t with various shift amounts */
int64_t test_srari_di_4 (int64_t a)
{
  return ((a >> 3) + 1) >> 1;
}

int64_t test_srari_di_8 (int64_t a)
{
  return ((a >> 7) + 1) >> 1;
}

int64_t test_srari_di_16 (int64_t a)
{
  return ((a >> 15) + 1) >> 1;
}

/* Test larger shift amounts (> 31) to exercise uimm6 range */
int64_t test_srari_di_32 (int64_t a)
{
  return ((a >> 31) + 1) >> 1;
}

int64_t test_srari_di_48 (int64_t a)
{
  return ((a >> 47) + 1) >> 1;
}

/* Widen before rounding a 32-bit value on RV64.  */
int32_t test_srari_si_4 (int32_t a)
{
  return (((int64_t) a >> 3) + 1) >> 1;
}

int32_t test_srari_si_8 (int32_t a)
{
  return (((int64_t) a >> 7) + 1) >> 1;
}

/* { dg-final { scan-assembler-times "\\tsrari\\t" 7 } } */
