/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=sifive-p600-series -mcmodel=medany -mexplicit-relocs -fno-section-anchors -fdump-rtl-sched1" } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-rtl-dump "RISCV_FUSE_AUIPC_ADDI" "sched1" } } */
/* { dg-final { scan-assembler "auipc\ta0,%pcrel_hi\\(x\\)" } } */

/*
**foo:
**	addi	a0,a0,%pcrel_lo\(\.LA[0-9]+\)
**	tail	use
*/
extern void use(long *);
void foo(void) {
  extern long x;
  use(&x);
}
