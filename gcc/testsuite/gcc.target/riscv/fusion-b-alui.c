/* Verify RISCV_FUSE_B_ALUI correctly matches sub+smax (abs) pattern.
   This exercises the removal of the redundant CONST_INT_P check.  */
/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-options "-march=rv64gc_zbb -mabi=lp64d -mfusion=b-alui -fdump-rtl-sched1" } */
/* { dg-final { scan-rtl-dump "RISCV_FUSE_B_ALUI" "sched1" } } */

long
abs_val (long x)
{
  return x < 0 ? -x : x;
}
