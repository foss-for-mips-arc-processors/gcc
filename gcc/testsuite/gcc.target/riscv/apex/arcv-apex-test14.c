/* { dg-do compile } */
/* { dg-options "-O" } */

extern int op_xd_xc (int, int);
#pragma intrinsic (op_xd_xc, "myop_xd_xc", 10, "XD", "XC")

int
test (int a, int b)
{
  int r1 = op_xd_xc (a, b);
  int r2 = op_xd_xc (a, 100);
  return r1 + r2;
}

/* { dg-final { scan-assembler-times ".extInstruction" 2 } } */
/* { dg-final { scan-assembler-times ".extInstruction myop_xd_xc,10,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction myop_xd_xci,10,XC" 1 } } */

/* { dg-final { scan-assembler "myop_xd_xc\ta\[0-9\],a\[0-9\],a\[0-9\]" } } */
/* { dg-final { scan-assembler "myop_xd_xci\ta\[0-9\],a\[0-9\],100" } } */
