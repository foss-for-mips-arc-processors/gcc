/* { dg-do compile } */
/* { dg-options "-O3 -fno-tree-vectorize -fdump-tree-linterchange-details" } */

/* Large nest, does not fit under the size threshold.  Interchange.  */

#define N 128
typedef long matrix[N][N];
matrix A, B, Res;

void
mul (void)
{
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      {
	Res[i][j] = 0;
	for (int k = 0; k < N; ++k)
	  Res[i][j] += A[i][k] * B[k][j] + (A[i][k] >> 1);
      }
}

/* { dg-final { scan-tree-dump "Loop_pair<outer:., inner:.> is interchanged" "linterchange" } } */
