/* Verify that the RHX-100 scheduler does not end a cycle in the middle of
   a fused macro-op.

   Group under test:
     FLL (fused adjacent-load pair) + FSS (fused adjacent-store pair)

   RHX-100 issues two units per cycle (slot A and slot B); a unit is either
   one unfused insn or one fused macro-op pair occupying the fuse0/fuse1
   sub-slots.  Memory ops exist only on slot B (single DMP) and the multiplier
   is reachable only through slot A fuse0 (single MPY), so one cycle holds at
   most two units, at most one of which is a memory unit and at most one of
   which is a multiply unit.

   Both units are fused pairs, so they compete for the two slots of a single
   cycle.  Which pair wins slot A is a packing choice and is deliberately not
   checked here; what is checked is that each pair issues as one op, with both
   halves in the same cycle.  A pair whose halves straddle a cycle boundary is
   not fused at all in hardware, so the schedule is strictly worse than the
   unfused one.  */

/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" } */

void
f_fll_fss (void)
{
  int * p0;
  int * p1;
  int x1;
  int y1;

  asm volatile ("" : "=r"(p0), "=r"(p1), "=r"(x1), "=r"(y1));
  int r0a = p0[16], r0b = p0[17];
  p1[32] = x1; p1[33] = y1;
  asm volatile ("" :: "r"(r0a), "r"(r0b) : "memory");
}

/* { dg-final { scan-rtl-dump {(?:;;\s+1--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]0\][^\n]*\n;;\s+1--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]4\]|;;\s+2--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]0\][^\n]*\n;;\s+2--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]4\]|;;\s+3--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]0\][^\n]*\n;;\s+3--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]4\]|;;\s+4--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]0\][^\n]*\n;;\s+4--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]4\]|;;\s+5--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]0\][^\n]*\n;;\s+5--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]4\]|;;\s+6--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]0\][^\n]*\n;;\s+6--> b\s+\d+: i\s+\d+ \S+=\[\S+\+0x[48]4\])} "sched2" } } */
/* { dg-final { scan-rtl-dump {(?:;;\s+1--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]0\]=\S+[^\n]*\n;;\s+1--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]4\]=\S+|;;\s+2--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]0\]=\S+[^\n]*\n;;\s+2--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]4\]=\S+|;;\s+3--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]0\]=\S+[^\n]*\n;;\s+3--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]4\]=\S+|;;\s+4--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]0\]=\S+[^\n]*\n;;\s+4--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]4\]=\S+|;;\s+5--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]0\]=\S+[^\n]*\n;;\s+5--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]4\]=\S+|;;\s+6--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]0\]=\S+[^\n]*\n;;\s+6--> b\s+\d+: i\s+\d+ \[\S+\+0x[48]4\]=\S+)} "sched2" } } */
