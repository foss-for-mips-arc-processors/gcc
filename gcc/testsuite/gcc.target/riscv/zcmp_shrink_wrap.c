/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32imac_zicsr_zifencei_zcmp -mabi=ilp32 -fshrink-wrap" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Og" "-O3" "-Oz" "-flto" } } */

extern void 
bar (int);

/* Verify that Zcmp cm.push is used at -O2 even when a simple 
   shrink-wrap early return is present.  */
void
foo (int a)
{
  if (a == 0)
    return;
  bar (a);
  bar (a);
}

/* { dg-final { scan-assembler "cm\\.push" } } */
/* { dg-final { scan-assembler "cm\\.pop" } } */
