/* { dg-do compile } */

extern int _foo (int, int);
#pragma intrinsic (_foo, "FOO", 15)

extern int bar (int);
#pragma intrinsic (bar, "barop", 14)

int
main (void)
{
  return _foo (1, 2) + bar (10);
}

/* { dg-final { scan-assembler-times ".extInstruction" 4 } } */
/* { dg-final { scan-assembler-times ".extInstruction foo,15,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction fooi,15,XS,XC" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction barop,14,XD,no_src1" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction baropi,14,XI" 1 } } */

/* { dg-final { scan-assembler "baropi\ta\[0-9\],10" } } */
/* { dg-final { scan-assembler "fooi\ta\[0-9\],a\[0-9\],2" } } */
