/* { dg-do compile } */
/* { dg-options "-O" } */

extern int op_xd_xs (int, int);
#pragma intrinsic (op_xd_xs, "myop_xd_xs", 20, "XD", "XS")

int
test (int a, int b)
{
  int r1 = op_xd_xs (a, b);
  int r2 = op_xd_xs (a, 42);
  return r1 + r2;
}

/* { dg-final { scan-assembler-times ".extInstruction" 2 } } */
/* { dg-final { scan-assembler-times ".extInstruction myop_xd_xs,20,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction myop_xd_xsi,20,XS" 1 } } */

/* { dg-final { scan-assembler "myop_xd_xs\ta\[0-9\],a\[0-9\],a\[0-9\]" } } */
/* { dg-final { scan-assembler "myop_xd_xsi\ta\[0-9\],a\[0-9\],42" } } */
