/* PR target/125180 */
/* { dg-do compile } */
/* { dg-options "-O2 -masm=att" } */
/* { dg-final { scan-assembler "\ttestl\t\\\$1, \\\(" } } */
/* { dg-final { scan-assembler-not "\ttestb\t\\\$1, \\\(" } } */

void foo (void);

void
bar (unsigned volatile *x)
{
  if (*x & 1)
    foo ();
}
