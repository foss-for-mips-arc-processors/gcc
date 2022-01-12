/* Check if the call is made using JL instruction.  */
/* { dg-do compile } */
/* { dg-options "-O -mcmodel=large" } */

extern int long_call(int a);

int test (int a)
{
  return 3 * long_call(a + 1);
}

/* { dg-final { scan-assembler "movhl" } } */
/* { dg-final { scan-assembler "orl" } } */
/* { dg-final { scan-assembler "jl_s.*\[r\d+\]" } } */
