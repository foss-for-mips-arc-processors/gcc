/* { dg-do compile } */
/* { dg-options "-O" } */

extern void side_op (int, int);
#pragma intrinsic (side_op, "sideop", 10, "XD", "side_effect")

void
test (int a, int b)
{
  side_op (a, b);
  side_op (a, b);
}

/* { dg-final { scan-assembler-times ".extInstruction" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction sideop,10,XD" 1 } } */
/* { dg-final { scan-assembler-times "sideop\ta\[0-9\],a\[0-9\]" 2 } } */
