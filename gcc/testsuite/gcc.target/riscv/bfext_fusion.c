/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gc -mabi=lp64d -mfusion=bfext -fno-lto -fdump-rtl-sched2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_BFEXT" 1 "sched2" } } */

void oof (unsigned long a, unsigned long val);

void fubar (unsigned long a)
{
  unsigned long val = 0;

  val = a << 5;
  val >>= 6;

  oof (a, val);
}
