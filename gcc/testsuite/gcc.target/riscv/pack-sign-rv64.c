/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gc_zbkb -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

/* Check the generic sign-comparison simplification without P.  */

/*
** product_sign:
**  slli\s+[a-z][0-9]+,a1,48
**  srli\s+a0,[a-z][0-9]+,63
**  ret
*/
unsigned int
product_sign (unsigned int a, unsigned int b, unsigned int c)
{
  return (int) ((unsigned short) (a * c) | (b << 16)) < 0;
}
