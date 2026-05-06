/* { dg-do compile } */
/* { dg-options "-O" }*/

#define OPCODE 15

int instname_XC (int, int);
#pragma intrinsic (instname_XC, "__instname_XC", OPCODE, "XC")

int
main (void)
{
  int a = 0x0BADCAFE;
  int xc_max = instname_XC (a,2047);
  int xc_min = instname_XC (a,-2048);
  return xc_min + xc_max;
}

/* { dg-final { scan-assembler-times ".extInstruction" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction __instname_xc,15,XC" 1 } } */

/* { dg-final { scan-assembler-times "__instname_xc\ta\[0-9\],a\[0-9\],2047" 1 } } */
/* { dg-final { scan-assembler-times "__instname_xc\ta\[0-9\],a\[0-9\],-2048" 1 } } */
