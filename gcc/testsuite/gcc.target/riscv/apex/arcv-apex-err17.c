/* { dg-do compile } */
/* { dg-options "-mabi=ilp32d -march=rv32gc" }*/

struct S {int a,b,c,d; };

int foo (long long a, int b);
#pragma intrinsic (foo,"FOP",10, XD,XS) /* { dg-error "pragma intrinsic: APEX function 'foo' contains a parameter of a non-scalar type, or one that exceeds 4 bytes" } */

int
main (void)
{
  return foo (0xdeadbeefcafebabeULL, 100);
}