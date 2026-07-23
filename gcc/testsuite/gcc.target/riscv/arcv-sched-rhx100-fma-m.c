/* Verify that a fused ALU macro-op does not block the memory pipe: a fused
   ALU+ALU pair issues on the ALU pipe, leaving slot B free for a load, so the
   two units co-issue in a single cycle.

   Group under test:
     FMA (fused mul-add ALU+ALU macro-op) + M (unfused load)

   RHX-100 issues two units per cycle (slot A and slot B); a unit is either
   one unfused insn or one fused macro-op pair occupying the fuse0/fuse1
   sub-slots.  Memory ops exist only on slot B (single DMP) and the multiplier
   is reachable only through slot A fuse0 (single MPY), so one cycle holds at
   most two units, at most one of which is a memory unit and at most one of
   which is a multiply unit.

   The fused pair uses the multiplier on slot A, so slot B stays free for the
   load; the two units are independent, so this group must issue in 1 cycle.
   If the fused pair were wrongly placed on slot B it would collide with the
   load's DMP and push the load into a second cycle.  */

/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" } */

void
f_fma_m (void)
{
  int x0;
  int y0;
  int z0;
  int * p1;

  asm volatile ("" : "=r"(x0), "=r"(y0), "=r"(z0), "=r"(p1));
  int m0 = x0 * y0; int r0 = m0 + z0;
  int r1 = p1[128];
  asm volatile ("" :: "r"(r0), "r"(r1) : "memory");
}

/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\S+\*\S+[^\n]*\n;;\s+1--> b\s+\d+: i\s+\d+ \S+=\S+\+[a-z]+[0-9]} "sched2" } } */
/* { dg-final { scan-rtl-dump {;;\s+1--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x200\]} "sched2" } } */
