/* Verify that the RHX-100 scheduler attributes every instruction of a
   four-instruction group to the correct issue cycle.

   Group under test:
     FLSU (fused load + address-update add (MEM+ALU) pair)
     + A (unfused ALU op) + A (unfused ALU op)

   This is the RISCV_FUSE_LS_UPDATE case: a genuine arithmetic add fused with
   a memory op, complementing the lui+load pairing already covered by the flui
   tests.  It is the other fused ALU+MEM shape and, unlike lui+load, is formed
   opportunistically by the reorder2 hook rather than by sched_fusion.

   RHX-100 issues two units per cycle (slot A and slot B); a unit is either
   one unfused insn or one fused macro-op pair occupying the fuse0/fuse1
   sub-slots.  Memory ops exist only on slot B (single DMP) and the multiplier
   is reachable only through slot A fuse0 (single MPY), so one cycle holds at
   most two units, at most one of which is a memory unit and at most one of
   which is a multiply unit.  The fused pair contains a memory op, so it takes
   slot B as a single unit; this group must issue in 2 cycles.

   Cycle 0 of the dump is the seeding asm; the group starts at cycle 1.  */

/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" } */

void
f_flsu_a_a (void)
{
  int * p0;
  int x1;
  int x2;

  asm volatile ("" : "=r"(p0), "=r"(x1), "=r"(x2));
  int r0 = p0[0];
  p0 += 8;
  int r1 = x1 ^ 4;
  int r2 = x2 ^ 5;
  asm volatile ("" :: "r"(r0), "r"(p0), "r"(r1), "r"(r2) : "memory");
}

/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\S+\^0x[0-9a-f]+} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\[\S+\][^\n]*\n;;\s+1--> b\s+\d+: i\s+\d+ \S+=\S+\+0x[0-9a-f]+} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+2--> b\s+\d+: i\s+\d+ \S+=\S+\^0x[0-9a-f]+} "sched2" } } */
