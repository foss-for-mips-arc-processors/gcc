/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" { target { rv32 } } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv64im -mabi=lp64 -fdump-rtl-sched2" { target { rv64 } } } */

int *
fuse_ls_update_move (int *p, int *q, int x)
{
  *q = x;
  return q;
}

/* { dg-final { scan-rtl-dump "RISCV_FUSE_LS_UPDATE" "sched2" } } */
