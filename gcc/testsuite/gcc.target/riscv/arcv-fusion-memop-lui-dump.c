/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

extern int g1, g2;

int
fuse_memop_lui (int *p, int *q)
{
  int a = *p;
  int b = *q;
  return a + b + g1 + g2;
}

/* { dg-final { scan-rtl-dump "RISCV_FUSE_MEMOP_LUI \\(prev, curr\\)" "sched2" } } */
/* { dg-final { scan-rtl-dump "RISCV_FUSE_MEMOP_LUI \\(curr, prev\\)" "sched2" } } */
