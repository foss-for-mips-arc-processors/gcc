/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -fomit-frame-pointer" } */
/* { dg-skip-if "" { *-*-* } {"-O0" "-O1" "-O2" "-O3" "-Og" "-Oz" "-flto"} } */
/* { dg-additional-options "-march=rv32imac_zcmp -mabi=ilp32" { target rv32 } } */
/* { dg-additional-options "-march=rv64imac_zcmp -mabi=lp64" { target rv64 } } */
/* { dg-final { check-function-bodies "**" "" } } */

/*
**f1:
**	addi	gp,gp,[48]
**...
**	s[wd]	ra,-[48]\(gp\)
**...
**	cm\.push	\{ra\}, -16
**...
**	cm\.pop	\{ra\}, 16
**...
**	l[wd]	ra,-[48]\(gp\)
**...
**	addi	gp,gp,-[48]
**	jr	ra
*/
int f1 (int a) { asm volatile ("":::"ra"); return a; }
