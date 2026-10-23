/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -fno-omit-frame-pointer -foptimize-sibling-calls" } */
/* { dg-skip-if "" { *-*-* } {"-O0" "-O2" "-O3" "-Og" "-Os" "-Oz" "-flto"} } */
/* { dg-final { check-function-bodies "**" "" } } */

int g (int);

/*
**f1:
**	addi	gp,gp,[48]
**...
**	s[wd]	ra,-[48]\(gp\)
**...
**	l[wd]	ra,-[48]\(gp\)
**...
**	addi	gp,gp,-[48]
**	tail	g
*/
int f1 (int a) { return g (a); }

/*
**f2:
**	addi	gp,gp,[48]
**...
**	s[wd]	ra,-[48]\(gp\)
**...
**	l[wd]	ra,-[48]\(gp\)
**...
**	addi	gp,gp,-[48]
**	mret
*/
__attribute__((interrupt("machine"))) void f2 (void)
{
  asm volatile ("":::"ra");
}

/*
**f3:
**	addi	gp,gp,[48]
**...
**	s[wd]	ra,-[48]\(gp\)
**...
**	l[wd]	ra,-[48]\(gp\)
**...
**	addi	gp,gp,-[48]
**	sret
*/
__attribute__((interrupt("supervisor"))) void f3 (void)
{
  asm volatile ("":::"ra");
}
