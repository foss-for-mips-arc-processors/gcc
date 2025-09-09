/* { dg-do compile } */
/* { dg-options "-O" }*/

#define OPCODE 123

int instname_XD (int, int);
#pragma intrinsic (instname_XD, "__instname_XD", OPCODE, "XD")

int
main (void)
{
  int a = 123;
  int xd_large = instname_XD (a, 0XFFFF);
  int xd_255   = instname_XD (a, 255);
  int xd_1     = instname_XD (a, 1);
  return xd_1 + xd_255 + xd_large;
}

/* { dg-final { scan-assembler-times ".extInstruction" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction __instname_xd,123,XD" 1 } } */

/* { dg-final { scan-assembler-times "__instname_xd\ta\[0-5\],a\[0-5\],a\[0-5\]" 3 } } */
