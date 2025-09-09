/* { dg-do compile } */
/* { dg-options "-O" }*/

extern int foo (int, int);
#pragma intrinsic (foo, "fop", 10)

int
test (int a, int b)
{
  return foo (a, b) + foo (a, b) + foo (a, b);
}

/* { dg-final { scan-assembler-times ".extInstruction" 2 } } */
/* { dg-final { scan-assembler-times ".extInstruction fop,10,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction fopi,10,XS,XC" 1 } } */

/* { dg-final { scan-assembler-times "fop\ta\[0-5\],a\[0-5\],a\[0-5\]" 1 } } */
