/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gc_zbb -mabi=lp64d -mfusion=b-alui -fno-lto -fdump-rtl-sched1" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_B_ALUI" 1 "sched1" } } */
/* TODO: only neg+max fires; orc.b+not and ctz+andi require relaxing
   riscv_fusion_same_dest_p for RISCV_FUSE_B_ALUI.  */
/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_B_ALUI" 3 "sched1" { xfail *-*-* } } } */

struct foo {
  long long a;
};

void oof (struct foo *, long long a);

void fubar (long long a)
{
  struct foo f;
  f.a = __builtin_riscv_orc_b_64 (a);
  oof (&f, ~f.a);
}

void fubar2 (long long a)
{
  struct foo f;
  f.a = __builtin_riscv_ctz_64 (a);
  oof (&f, f.a & 63);
}

long long fubar3 (long long a)
{
  long long b = -a;
  return a > b ? a : b;
}
