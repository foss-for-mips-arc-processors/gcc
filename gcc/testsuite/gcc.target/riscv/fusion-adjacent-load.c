/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

int
fuse_adjacent_load (int *p)
{
  return p[0] + p[1];
}

/* { dg-final { scan-rtl-dump "RISCV_FUSE_ADJACENT_LOAD" "sched2" } } */
