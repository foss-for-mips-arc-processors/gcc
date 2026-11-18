/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

long long
add_pair (long long a, long long b)
{
  return a + b;
}

/* A single RV32 ADD loses the carry and leaves the high result undefined.  */
/* { dg-final { scan-assembler {\maddd\M} } } */
