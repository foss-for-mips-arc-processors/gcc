/* { dg-do compile } */
/* { dg-options "-O" } */

extern int custom_add (int, int);
#pragma intrinsic (custom_add, "myadd", 42, "XD")

template <typename T>
T apply (T a, T b)
{
  return custom_add (a, b);
}

int
main (void)
{
  return apply (10, 20);
}

/* { dg-final { scan-assembler-times ".extInstruction" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction myadd,42,XD" 1 } } */
/* { dg-final { scan-assembler "myadd\ta\[0-9\],a\[0-9\],a\[0-9\]" } } */
