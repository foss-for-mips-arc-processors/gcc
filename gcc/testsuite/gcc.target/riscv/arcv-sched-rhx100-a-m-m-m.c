/* Verify that the RHX-100 scheduler attributes every instruction of a
   four-instruction group to the correct issue cycle.

   Group under test:
     A (unfused ALU op) + M (unfused memory op) + M (unfused memory op) + M (unfused memory op)

   RHX-100 issues two units per cycle (slot A and slot B); a unit is either
   one unfused insn or one fused macro-op pair occupying the fuse0/fuse1
   sub-slots.  Memory ops exist only on slot B (single DMP) and the multiplier
   is reachable only through slot A fuse0 (single MPY), so one cycle holds at
   most two units, at most one of which is a memory unit and at most one of
   which is a multiply unit.  This group must issue in 3 cycles.

   Cycle 0 of the dump is the seeding asm; the group starts at cycle 1.  */

/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" } */

void
f_a_m_m_m (void)
{
  int x0;
  int * p1;
  int * p2;
  int * p3;

  asm volatile ("" : "=r"(x0), "=r"(p1), "=r"(p2), "=r"(p3));
  int r0 = x0 ^ 3;
  int r1 = p1[128];
  int r2 = p2[192];
  int r3 = p3[256];
  asm volatile ("" :: "r"(r0), "r"(r1), "r"(r2), "r"(r3) : "memory");
}

/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\S+\^0x[0-9a-f]+} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[1-4]00\]} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+2--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[1-4]00\]} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+3--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[1-4]00\]} "sched2" } } */
