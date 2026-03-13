/* { dg-do compile } */

int foo (int);
#pragma intrinsic (foo, FOP, 10, "XI")

int
main (void)
{
  int a;
  a =  foo (-2049); /* { dg-error "argument value -2049 is outside the valid range \\\[-2048, 2047\\\]" } */
  a += foo (2048); /* { dg-error "argument value 2048 is outside the valid range \\\[-2048, 2047\\\]" } */
  a += foo (1000000); /* { dg-error "argument value 1000000 is outside the valid range \\\[-2048, 2047\\\]" } */
  return a;
}
