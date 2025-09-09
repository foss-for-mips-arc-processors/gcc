/* { dg-do compile } */
/* { dg-options "-mabi=ilp32d -march=rv32gc" }*/

struct S {int a,b,c,d; };

long long foo (struct S *a, int b);
#pragma intrinsic (foo,"FOP",10, XD,XS) /* { dg-error "pragma intrinsic: APEX function 'foo' must return void or a scalar type that does not exceed 4 bytes" } */

int
main (void)
{
  struct S s = {1,2,3,4};
  return foo (&s, 100);
}