/* { dg-do compile } */
/* { dg-options "-mabi=lp64d -march=rv64gc" }*/

struct S {int a,b,c,d; };

long long foo (struct S *a, int b);
#pragma intrinsic (foo,"FOP",10, XD,XS)

int
main (void)
{
  struct S s = {1,2,3,4};
  return foo (&s, 100);
}