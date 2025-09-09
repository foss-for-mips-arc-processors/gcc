/* { dg-do compile } */
/* { dg-options "-O" }*/

#define OPCODE_7 0x7

int instname_XI (int);
#pragma intrinsic (instname_XI, "__instname_XI", OPCODE_7, "XI")

int
main (void)
{
  int xi_max = instname_XI (2047);
  int xi_min = instname_XI (-2048);
  return xi_min + xi_max;
}

/* { dg-final { scan-assembler-times ".extInstruction" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction __instname_xi,7,XI" 1 } } */

/* { dg-final { scan-assembler-times "__instname_xi\ta\[0-9\],2047" 1 } } */
/* { dg-final { scan-assembler-times "__instname_xi\ta\[0-9\],-2048" 1 } } */
