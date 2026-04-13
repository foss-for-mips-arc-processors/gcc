/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

int
fuse_ls_update (int *p, int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

/* { dg-final { scan-rtl-dump "ARCV_FUSE_LS_UPDATE" "sched2" } } */
