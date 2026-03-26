/* { dg-do compile } */
/* { dg-options "-Ofast -funroll-all-loops -friscv-fold-mem" } */
void
matrix_mul_matrix(unsigned int N, int *C, short *A, short *B)
{
    unsigned int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            C[i * N + j] = 0;
            
            /* unroll paragma to generate the 8 sequential 
               short array accesses (8 elements * 2 bytes = 16 byte range) */
            #pragma GCC unroll 8
            for (k = 0; k < N; k++)
            {
                C[i * N + j] += (int)A[i * N + k] * (int)B[k * N + j];
            }
        }
    }
}

/* check for the exact offsets (0, 2, 4, 6, 8, 10, 12, 14).  */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,0\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,2\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,4\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,6\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,8\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,10\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,12\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,14\\(\[a-x0-9\]+\\)" } } */
