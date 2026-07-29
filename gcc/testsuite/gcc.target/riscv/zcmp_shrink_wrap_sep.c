/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32imac_zicsr_zifencei_zcmp -mabi=ilp32 -fshrink-wrap-separate" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Og" "-O3" "-Oz" "-flto" } } */

/* Verify that Zcmp cm.push is NOT used when shrink-wrap-separate is 
   actively moving individual callee-saved registers.  */
void
foo (int a)
{
  if (a == 1)
    {
      register int s0 asm ("s0") = 1;
      asm volatile ("" : : "r" (s0));
      return;
    }
  register int s1 asm ("s1") = 2;
  asm volatile ("" : : "r" (s1));
}

/* { dg-final { scan-assembler-not "cm\\.push" } } */
/* { dg-final { scan-assembler-not "cm\\.pop" } } */
