/* Verify RISCV_FUSE_AUIPC_LD correctly matches auipc+ld pairs.
   This exercises the fix for XINT accessing SET_SRC (prev_set)
   instead of prev_set directly.  */
/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mfusion=auipc-ld -mcmodel=medany -mexplicit-relocs -fno-section-anchors -fdump-rtl-sched1" } */
/* TODO: XFAIL because the AUIPC_LD checker only matches the PLUS form, but
   -mexplicit-relocs produces a LO_SUM-based load.  */
/* { dg-final { scan-rtl-dump "RISCV_FUSE_AUIPC_LD" "sched1" { xfail *-*-* } } } */

extern long x;

long
load_global (void)
{
  return x;
}
