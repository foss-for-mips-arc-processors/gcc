/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

void
fuse_li_store (int *p)
{
  *p = 42;
}

/* { dg-final { scan-rtl-dump "ARCV_FUSE_LI_STORE" "sched2" } } */
