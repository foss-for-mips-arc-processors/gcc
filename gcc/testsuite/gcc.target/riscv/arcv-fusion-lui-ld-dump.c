/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

extern int g1, g2;
extern volatile int g3, g4;

int
fuse_lui_ld (void)
{
  return g1 + g2;
}

int
fuse_lui_ld_rev (volatile int *p, int val)
{
  int a = *p;
  int b = g3;
  int c = p[1];
  int d = g4;
  return a + b + c + d + val;
}

/* { dg-final { scan-rtl-dump "RISCV_FUSE_LUI_LD" "sched2" } } */
/* { dg-final { scan-rtl-dump "RISCV_FUSE_LUI_LD_REV" "sched2" } } */
