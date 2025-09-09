/* { dg-do compile } */

extern int foo (int, int);
#pragma intrinsic (foo, "FOP", 15)

int
main (int argc, const char **argv)
{
  return foo (argc,-2048);
}

/* { dg-final { scan-assembler-times ".extInstruction" 2 } } */
/* { dg-final { scan-assembler-times ".extInstruction fop,15,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction fopi,15,XS,XC" 1 } } */

/* { dg-final { scan-assembler-times "fopi\ta\[0-9\],a\[0-9\],-2048" 1 } } */