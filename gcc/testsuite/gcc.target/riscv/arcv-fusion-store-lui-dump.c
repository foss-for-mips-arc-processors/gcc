/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

volatile int g1, g2, g3;

void
fuse_store_lui (volatile int *p, int val)
{
  *p = val;
  g1 = val;
  p[1] = val;
  g2 = val;
  p[2] = val;
  g3 = val;
}

/* { dg-final { scan-rtl-dump "RISCV_FUSE_LUI_ST \\(prev, curr\\)" "sched2" } } */
/* { dg-final { scan-rtl-dump "RISCV_FUSE_LUI_ST \\(curr, prev\\)" "sched2" } } */
