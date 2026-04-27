/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

int
fuse_li_branch (int x)
{
  while (x <= 3)
    ;
  return x;
}

/* { dg-final { scan-rtl-dump "RISCV_FUSE_LI_BRANCH" "sched2" } } */
