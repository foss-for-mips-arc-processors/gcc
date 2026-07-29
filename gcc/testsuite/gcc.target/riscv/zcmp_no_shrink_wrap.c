/* { dg-do compile } */ 
/* { dg-options "-O2 -march=rv32imac_zicsr_zifencei_zcmp -mabi=ilp32 -fshrink-wrap" } */
/* { dg-skip-if "" { *-*-* } {"-O0" "-O1" "-Os" "-Og" "-O3" "-Oz" "-flto"} } */

extern void
bar (int);

/* Verify that Zcmp cm.push is used at -O2 when shrink-wrapping is 
   active but no early return exists.  */
void
foo (int a)
{
  bar (a);
  bar (a);
}

/* { dg-final { scan-assembler "cm\\.push" } } */
/* { dg-final { scan-assembler "cm\\.pop" } } */
