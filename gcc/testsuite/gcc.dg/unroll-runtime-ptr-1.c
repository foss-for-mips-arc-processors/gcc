/* { dg-do run } */
/* { dg-options "-O2 -funroll-all-loops -fno-tree-vectorize" } */

#define MAXN 80

short as[MAXN];
int ai[MAXN];
long long al[MAXN];

__attribute__((noipa)) int
sum_s (short *p, short *e)
{
  int s = 0;
  do
    s += *p * 3 + 1;
  while (++p != e);
  return s;
}

__attribute__((noipa)) int
sum_i (int *p, int *e)
{
  int s = 0;
  do
    s += *p * 5 - 2;
  while (++p != e);
  return s;
}

__attribute__((noipa)) long long
sum_l (long long *p, long long *e)
{
  long long s = 0;
  do
    s += *p * 7 + 3;
  while (++p != e);
  return s;
}

__attribute__((noipa)) int
sum_idx (unsigned n, short *a)
{
  int s = 0;
  for (unsigned k = 0; k < n; k++)
    s += a[k] * 3 + 1;
  return s;
}

int
main (void)
{
  for (int i = 0; i < MAXN; i++)
    {
      as[i] = i + 1;
      ai[i] = 2 * i - 7;
      al[i] = 3LL * i + 11;
    }

  for (unsigned off = 0; off < 4; off++)
    for (unsigned n = 1; n + off <= 70; n++)
      {
	int es = 0, ei = 0;
	long long el = 0;
	for (unsigned k = off; k < off + n; k++)
	  {
	    es += as[k] * 3 + 1;
	    ei += ai[k] * 5 - 2;
	    el += al[k] * 7 + 3;
	  }
	if (sum_s (as + off, as + off + n) != es
	    || sum_i (ai + off, ai + off + n) != ei
	    || sum_l (al + off, al + off + n) != el
	    || sum_idx (n, as + off) != es)
	  __builtin_abort ();
      }
  return 0;
}
