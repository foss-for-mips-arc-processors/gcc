/* { dg-do compile } */
/* { dg-options "-mabi=lp64d -march=rv64gc" } */

struct S {int a,b,c,d; };

int foo (long long a, int b);
#pragma intrinsic (foo,"FOP",10, XD,XS)

int
main (void)
{
  return foo (0xdeadbeefcafebabeULL, 100);
}
