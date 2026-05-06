/* { dg-do compile } */
/* { dg-options "-O0" } */

int foo (int);
#pragma intrinsic (foo, FOP, 10, "XI")

int
main (void)
{
  int x = 12;
  return foo (x); /* { dg-error "argument to 'foo' must be a constant integer" } */
}
