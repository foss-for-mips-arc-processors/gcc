/* { dg-do compile } */
/* { dg-require-effective-target int32 } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

int __attribute__ ((noipa))
unguarded (unsigned int x)
{
  return x - 1 <= 2;
}

int __attribute__ ((noipa))
zero_possible (unsigned int x)
{
  if (x == 1)
    return -1;
  return x - 1 <= 2;
}

int __attribute__ ((noipa))
shared (unsigned int x, unsigned int *saved)
{
  if (x == 0)
    return -1;
  unsigned int y = x - 1;
  *saved = y;
  return y <= 2;
}

int __attribute__ ((noipa))
unguarded64 (unsigned long long x)
{
  return x - 1 <= 2;
}

int __attribute__ ((noipa))
zero_possible64 (unsigned long long x)
{
  if (x == 1)
    return -1;
  return x - 1 <= 2;
}

int __attribute__ ((noipa))
shared64 (unsigned long long x, unsigned long long *saved)
{
  if (x == 0)
    return -1;
  unsigned long long y = x - 1;
  *saved = y;
  return y <= 2;
}

/* Zero must still wrap, and a saved decrement must remain available.  */
/* { dg-final { scan-tree-dump-times { \+ 4294967295;} 3 "optimized" } } */
/* { dg-final { scan-tree-dump-times { \+ 18446744073709551615;} 3 "optimized" } } */
