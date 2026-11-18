/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

int
dot (int *restrict d, const short *restrict a, const short *restrict b,
     unsigned int n)
{
  int sum = 0;
  for (unsigned int i = 0; i < n; ++i)
    {
      int p = (int) a[i] * b[i];
      d[i] = p;
      sum += p;
    }
  return sum;
}

/* The independently stored product must still be costed.  */
/* { dg-final { scan-tree-dump "Scalar iteration cost: 5" "vect" } } */
