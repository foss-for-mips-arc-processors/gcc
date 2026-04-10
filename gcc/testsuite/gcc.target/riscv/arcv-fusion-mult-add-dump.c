/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -mno-arc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

int
fuse_mult_add (int a, int b, int c, int d, int e, int g, int h)
{
  return g + a * b + h + c * d;
}

/* { dg-final { scan-rtl-dump "ARCV_FUSE_MULT_ADD \\(op0\\)" "sched2" } } */
/* { dg-final { scan-rtl-dump "ARCV_FUSE_MULT_ADD \\(op1\\)" "sched2" } } */
