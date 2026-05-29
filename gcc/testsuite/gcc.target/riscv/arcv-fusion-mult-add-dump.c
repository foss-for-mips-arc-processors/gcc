/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

int
fuse_mult_add_op0 (int a, int b, int c, int d)
{
  int m = a * b;
  return m + c + m + d;
}

int
fuse_mult_add_op1 (int a, int b, int c)
{
  int m = a * b;
  return a + m + c + m;
}

/* { dg-final { scan-rtl-dump "RISCV_FUSE_MULT_ADD \\(op0\\)" "sched2" } } */
/* { dg-final { scan-rtl-dump "RISCV_FUSE_MULT_ADD \\(op1\\)" "sched2" } } */
