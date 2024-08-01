/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32gc -mabi=ilp32d -mlong-double-64" } */

int __attribute__((noinline))
g (long double ld)
{
  return (int)ld;
}

int
f (int x)
{
  return (long double) 3.141592;
}

/* { dg-final { scan-assembler-times "__fixtfsi" 0 } } */
