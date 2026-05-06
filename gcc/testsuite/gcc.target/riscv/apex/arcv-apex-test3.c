/* { dg-do compile } */

extern int _foo (int, int);
#pragma intrinsic (_foo, "FOO", 100)

int
test (int a, int b)
{
  return _foo (a,b);
}

/* { dg-final { scan-assembler-times ".extInstruction" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction foo,100,XD" 1 } } */

/* { dg-final { scan-assembler "foo\ta\[0-9\],a\[0-9\],a\[0-9\]" } } */
