/* { dg-do compile } */
/* { dg-options "-O3 -fno-tree-vectorize -fdump-tree-linterchange-details --param loop-interchange-size-threshold=1" } */

/* Threshold forced to 1KB, so it does not fit.  Interchange.  */

#define N 20
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

/* { dg-final { scan-tree-dump-times "Loop_pair<outer:., inner:.> is interchanged" 1 "linterchange" } } */
