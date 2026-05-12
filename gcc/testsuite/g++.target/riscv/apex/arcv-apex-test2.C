/* { dg-do compile } */

extern "C" int cfoo (int, int);
#pragma intrinsic (cfoo, "cfop", 20)

int
main (void)
{
  return cfoo (3, 4);
}

/* { dg-final { scan-assembler-times ".extInstruction" 2 } } */
/* { dg-final { scan-assembler-times ".extInstruction cfop,20,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction cfopi,20,XS,XC" 1 } } */
