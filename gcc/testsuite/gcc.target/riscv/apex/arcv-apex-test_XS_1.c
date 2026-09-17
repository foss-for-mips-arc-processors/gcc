/* { dg-do compile } */
/* { dg-options "-O" }*/

#define OPCODE_0 0

int instname_XS (int, int);
#pragma intrinsic (instname_XS, "__instname_XS", OPCODE_0, "XS")

int
main (void)
{
  int a = 123;
  int xs_max = instname_XS (a, 127);
  int xs_min = instname_XS (a, -128);
  return xs_min + xs_max;
}

/* { dg-final { scan-assembler-times ".extInstruction" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction __instname_xs,0,XS" 1 } } */

/* { dg-final { scan-assembler-times "__instname_xs\ta\[0-5\],a\[0-5\],127" 1 } } */
/* { dg-final { scan-assembler-times "__instname_xs\ta\[0-5\],a\[0-5\],-128" 1 } } */
