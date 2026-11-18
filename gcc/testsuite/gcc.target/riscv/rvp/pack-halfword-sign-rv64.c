/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

/* A discarded low halfword must not keep its producer alive.  */

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

/*
** logic_sign:
**  slli\s+[a-z][0-9]+,a1,48
**  srli\s+a0,[a-z][0-9]+,63
**  ret
*/
unsigned int
logic_sign (unsigned int a, unsigned int b, unsigned int c)
{
  unsigned int low = ((a << 3) ^ (c >> 5)) + a * c;
  return (int) ((unsigned short) low | (b << 16)) < 0;
}
