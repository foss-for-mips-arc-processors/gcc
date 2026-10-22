/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -funwind-tables -fomit-frame-pointer" } */
/* { dg-skip-if "" { *-*-* } {"-O0" "-O2" "-O3" "-Og" "-Os" "-Oz" "-flto"} } */
/* { dg-final { check-function-bodies "**" "" } } */

#if __SANITIZE_SHADOW_CALL_STACK__ != 1
#error "__SANITIZE_SHADOW_CALL_STACK__ is not defined to 1"
#endif

int g (int);

/*
**f1:
**	li	a0,0
**	ret
*/
int f1 (void) { return 0; }

/*
**f2:
**	addi	gp,gp,[48]
**...
**	s[wd]	ra,-[48]\(gp\)
**...
**	l[wd]	t0,-[48]\(gp\)
**...
**	addi	gp,gp,-[48]
**	jr	t0
*/
int f2 (void) { asm volatile ("":::"ra"); return 0; }

/*
**f3:
**	addi	gp,gp,[48]
**...
**	s[wd]	ra,-[48]\(gp\)
**...
**	call	g
**...
**	l[wd]	t0,-[48]\(gp\)
**...
**	addi	gp,gp,-[48]
**	jr	t0
*/
int f3 (int a) { return g (a) + 1; }

/*
**f4:
**	addi	sp,sp,-16
**	s[wd]	ra,(8|12)\(sp\)
**	call	g
**	addiw?	a0,a0,1
**	l[wd]	ra,(8|12)\(sp\)
**	addi	sp,sp,16
**	jr	ra
*/
int __attribute__((no_sanitize("shadow-call-stack"))) f4 (int a)
{
  return g (a) + 1;
}

/*
**f5:
*/
void __attribute__((naked)) f5 (void) {}

/* { dg-final { scan-assembler-times {\.cfi_escape 0x16,0x3,0x2,0x73,0x7[c8]} 2 } } */
/* { dg-final { scan-assembler-times {\.cfi_restore 3} 2 } } */
