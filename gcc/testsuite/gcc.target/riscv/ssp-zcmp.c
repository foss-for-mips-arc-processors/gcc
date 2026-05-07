/* { dg-do compile } */
/* { dg-options "-Os -march=rv32g_zcmp_zcmop_zicfiss -mabi=ilp32d -fcf-protection=return" } */
/* { dg-skip-if "needs -Os" { *-*-* } { "-O0" "-O1" "-O2" "-O3" "-Og" "-Oz" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-assembler-not {cm\.popret} } } */

int printf (const char *, ...);

/*
** printSomething:
**	sspush	ra
**	...
**	cm\.push	\{ra, s0-s2\}, -32
**	...
**	cm\.pop	\{ra, s0-s2\}, 32
**	sspopchk	ra
**	jr	ra
**  ...
*/
int printSomething (int arr[], int len) {
  for (int i = 0; i < len; i++)
    printf ("Val[%d]: %d\n", i, arr[i]);
  return len;
}

extern int sibcallee (int);
extern void other (void);

/*
** sibcaller:
**	sspush	ra
**	cm\.push	\{ra\}, -32
**	...
**	cm\.pop	\{ra\}, 32
**	...
**	sspopchk	ra
**	tail	sibcallee
*/
int sibcaller (int x) {
  other ();
  return sibcallee (x + 1);
}
