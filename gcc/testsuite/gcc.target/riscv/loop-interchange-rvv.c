/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcv -mabi=ilp32 -fdump-tree-linterchange-details" } */
/* { dg-skip-if "" { *-*-* } { "-fno-fat-lto-objects" } { "" } } */

/* Small nest, but vector mode is available.  Interchange.  */

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

/* { dg-final { scan-tree-dump "Loop_pair<outer:., inner:.> is interchanged" "linterchange" } } */
