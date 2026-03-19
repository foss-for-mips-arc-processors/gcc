/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

typedef unsigned int ee_u32;
typedef short MATDAT;
typedef int MATRES;

void
matrix_mul (ee_u32 N, MATRES *C, MATDAT *A, MATDAT *B)
{
  ee_u32 i, j, k;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      {
	C[i * N + j] = 0;
	for (k = 0; k < N; k++)
	  C[i * N + j] += (MATRES) A[i * N + k] * (MATRES) B[k * N + j];
      }
}

/* { dg-final { scan-tree-dump "Successfully versioned loop" "ivbound" } } */
/* { dg-final { scan-tree-dump "recorded bound 32767 on loop" "ivbound" } } */
