/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=sifive-p600-series -fdump-rtl-sched1" } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-rtl-dump "RISCV_FUSE_LUI_ADDI" "sched1" } } */

/*
**foo:
**	li	a0,305418240
**	addi	a0,a0,1656
**	ret
*/
long foo(void) {
  return 0x12345678L;
}
