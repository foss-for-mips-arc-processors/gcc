/* { dg-do compile } */
/* { dg-require-effective-target hs6x } */
/* { dg-options "-O1" } */

/* We have to use "main()" to enable some sort of constant folding.
 * Otherwise, the potential bug won't be triggered.  */
int main()
{
  volatile char match = 1;

  volatile unsigned long *sram64 = (volatile unsigned long *) 0x8000000000UL;
  volatile unsigned long *addr = &sram64[512];

  if (match)
    *addr = 0x1234;
  else
    *addr = 0x4321;

  return 0;
}

/* { dg-final { scan-assembler "stl\\s+.+,\\\[r.\\\]" } } */
/* { dg-final { scan-assembler-not "stl\\s+.+,\\\[\[0-9\]+\\\]" } } */
