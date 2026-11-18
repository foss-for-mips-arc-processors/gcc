/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

/* The rounding-bit rewrite would add work when both original terms have
   other uses.  Include conversions around the quotient and the bit.  */

unsigned long
unsigned_shared (unsigned long x, unsigned long *r)
{
  unsigned long q = x >> 4;
  unsigned long bit = (x >> 3) & 1;
  r[0] = q;
  r[1] = bit;
  return q + bit;
}

long
signed_shared (long x, long *r)
{
  long q = x >> 4;
  long bit = (x >> 3) & 1;
  r[0] = q;
  r[1] = bit;
  return q + bit;
}

unsigned long
converted_quotient (long x, unsigned long *r)
{
  long q = x >> 4;
  unsigned long bit = ((unsigned long) x >> 3) & 1;
  r[0] = q;
  r[1] = bit;
  return (unsigned long) q + bit;
}

unsigned long
converted_bit (long x, unsigned long *r)
{
  long q = x >> 4;
  long bit = (x >> 3) & 1;
  r[0] = q;
  r[1] = bit;
  return (unsigned long) q + (unsigned long) bit;
}

/* The extraction shift can also be shared with a different signedness
   from the quotient.  Recomputing an arithmetic shift would add work.  */
unsigned long
shared_mixed_shift (long x, unsigned long *r)
{
  long q = x >> 4;
  unsigned long shifted = (unsigned long) x >> 3;
  r[0] = q;
  r[1] = shifted;
  return (unsigned long) q + (shifted & 1);
}

/* { dg-final { scan-tree-dump-not " \\+ 1;" "optimized" } } */
