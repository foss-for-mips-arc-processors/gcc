/* { dg-do compile } */
/* { dg-options "-O" } */

extern int op_all (int, int);
#pragma intrinsic (op_all, "myop_all", 5, "XD", "XS", "XC")

int
test (int a, int b)
{
  int r1 = op_all (a, b);
  int r2 = op_all (a, 7);
  return r1 + r2;
}

/* { dg-final { scan-assembler-times ".extInstruction" 2 } } */
/* { dg-final { scan-assembler-times ".extInstruction myop_all,5,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction myop_alli,5,XS,XC" 1 } } */

/* { dg-final { scan-assembler "myop_all\ta\[0-9\],a\[0-9\],a\[0-9\]" } } */
/* { dg-final { scan-assembler "myop_alli\ta\[0-9\],a\[0-9\],7" } } */
