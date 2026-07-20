/* Verify that the RHX-100 scheduler attributes every instruction of a
   four-instruction group to the correct issue cycle.

   Group under test:
     FLL (fused adjacent-load pair) + A (unfused ALU op) + A (unfused ALU op)

   RHX-100 issues two units per cycle (slot A and slot B); a unit is either
   one unfused insn or one fused macro-op pair occupying the fuse0/fuse1
   sub-slots.  Memory ops exist only on slot B (single DMP) and the multiplier
   is reachable only through slot A fuse0 (single MPY), so one cycle holds at
   most two units, at most one of which is a memory unit and at most one of
   which is a multiply unit.  This group must issue in 2 cycles.

   Cycle 0 of the dump is the seeding asm; the group starts at cycle 1.  */

/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" } */

void
f_fll_a_a (void)
{
  int * p0;
  int x1;
  int x2;

  asm volatile ("" : "=r"(p0), "=r"(x1), "=r"(x2));
  int r0a = p0[16], r0b = p0[17];
  int r1 = x1 ^ 4;
  int r2 = x2 ^ 5;
  asm volatile ("" :: "r"(r0a), "r"(r0b), "r"(r1), "r"(r2) : "memory");
}

/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\S+\^0x[0-9a-f]+} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]0\][^\n]*\n;;\s+1--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]4\]} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+2--> b\s+\d+: i\s+\d+ \S+=\S+\^0x[0-9a-f]+} "sched2" } } */
