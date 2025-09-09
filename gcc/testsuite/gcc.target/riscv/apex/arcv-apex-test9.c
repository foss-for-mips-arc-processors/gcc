/* { dg-do compile } */
/* { dg-options "-O" }*/

extern int foo (int, int);
#pragma intrinsic (foo, "fop", 10)

int
test (int n)
{
  int sum = 0;
  for (unsigned i = 0; i < n; ++i)
    sum += foo(n, n); /* should be pulled out of the loop.  */
  return sum;
}

/* { dg-final { scan-assembler-times ".extInstruction" 2 } } */
/* { dg-final { scan-assembler-times ".extInstruction fop,10,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction fopi,10,XS,XC" 1 } } */

/* { dg-final { scan-assembler-times "fop\ta\[0-5\],a\[0-5\],a\[0-5\]" 1 } } */
