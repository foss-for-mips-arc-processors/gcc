/* { dg-do compile } */
/* { dg-options "-O2 -msimd -ftree-vectorize" } */


struct{
  unsigned short x1;
  unsigned short x2;
} vara, varb;

void foo (void)
{
  vara.x1 = varb.x2;
  vara.x2 = varb.x1;
}
/* { dg-final { scan-assembler "swap" } } */
