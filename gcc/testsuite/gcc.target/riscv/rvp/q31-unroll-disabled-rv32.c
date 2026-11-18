/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

void
no_unroll (int *__restrict out, const int *__restrict a,
	   const int *__restrict b, unsigned int n)
{
#pragma GCC unroll 1
  for (unsigned int i = 0; i < n; ++i)
    {
      long long x = ((long long) a[i] * b[i] + 1073741824) >> 31;
      out[i] = x > 2147483647 ? 2147483647 : x;
    }
}

/* { dg-final { scan-tree-dump-not {Re-trying analysis for unrolling} "vect" } } */
/* { dg-final { scan-assembler-times {\tmulqr\t} 1 } } */
