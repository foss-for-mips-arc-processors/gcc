/* Verify that a fused ALU+MEM macro-op blocked on the busy memory pipe does
   not needlessly end the cycle: the scheduler keeps looking for a pure-ALU
   insn to dual-issue on the free ALU pipe.

   Group under test:
     FSS (fused store pair) + FLUI (fused lui+load ALU+MEM pair)
     + A (unfused ALU op) + A (unfused ALU op)

   RHX-100 issues two units per cycle (slot A and slot B); a unit is either
   one unfused insn or one fused macro-op pair occupying the fuse0/fuse1
   sub-slots.  Memory ops exist only on slot B (single DMP) and the multiplier
   is reachable only through slot A fuse0 (single MPY), so one cycle holds at
   most two units, at most one of which is a memory unit and at most one of
   which is a multiply unit.

   The two fused pairs both need slot B, so they issue in different cycles; the
   two ALU ops fill slot A of each.  When the store pair has taken slot B and
   the FLUI pair sits at the head of the ready list it cannot issue (slot B is
   busy), but slot A is free -- so an ALU op must be dual-issued there rather
   than stalling the cycle.  This group must issue in 2 cycles; if the blocked
   FLUI ended the cycle instead, an ALU op would slip to a needless third.  */

/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" } */

extern int g0;

void
f_fss_flui_a_a (int *p0, int x1, int x2)
{
  int s0, s1;

  asm volatile ("" : "=r"(s0), "=r"(s1));
  p0[16] = s0; p0[17] = s1;
  int r0 = g0;
  int r1 = x1 ^ 4;
  int r2 = x2 ^ 5;
  asm volatile ("" :: "r"(r0), "r"(r1), "r"(r2) : "memory");
}

/* Store pair on slot B of cycle 1, with an ALU op dual-issued alongside it.  */
/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \[\S+\+0x40\]=\S+[^\n]*\n;;\s+1--> b\s+\d+: i\s+\d+ \[\S+\+0x44\]=\S+} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\S+\^0x[0-9a-f]+} "sched2" } } */
/* FLUI pair on slot B of cycle 2, with the other ALU op alongside it.  */
/* { dg-final { scan-rtl-dump {;;\s+2--> b\s+\d+: i\s+\d+ \S+=high\(`g0'\)[^\n]*\n;;\s+2--> b\s+\d+: i\s+\d+ \S+=\[\S+\+low\(`g0'\)\]} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+2--> b\s+\d+: i\s+\d+ \S+=\S+\^0x[0-9a-f]+} "sched2" } } */
