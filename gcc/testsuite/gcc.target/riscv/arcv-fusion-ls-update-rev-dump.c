/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" { target rv32 } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im -mabi=lp64 -fdump-rtl-sched2" { target rv64 } } */

void
fuse_ls_update_rev (int *p, int n, int val)
{
  for (int i = 0; i < n; i++)
    {
      p++;
      *p = val;
    }
}

/* { dg-final { scan-rtl-dump "ARCV_FUSE_LS_UPDATE \\(curr, prev\\)" "sched2" } } */
