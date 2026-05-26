/* { dg-do compile } */
/* { dg-options "-Ofast -march=rv64gc_zba -mabi=lp64d -funroll-all-loops -friscv-fold-mem -friscv-matrix-opt" } */
/* { dg-skip-if "skip debug info" { *-*-* } { "-g" } { "" } } */
void
matrix_mul_matrix(unsigned int N, int *C, short *A, short *B)
{
    unsigned int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            C[i * N + j] = 0;
            
            #pragma GCC unroll 8
            for (k = 0; k < N; k++)
            {
                C[i * N + j] += (int)A[i * N + k] * (int)B[k * N + j];
            }
        }
    }
}

/* Verify that leftt shift calacution is hoisted into the loop preheader
   letting only a single base address scaling sh1add.uw at entry of the inner loop. */
/* { dg-final { scan-assembler "sh1add\\.uw\\s+\[a-z0-9\]+,\[a-z0-9\]+,\[a-z0-9\]+\\s*\\n\\s*slli\\s+\[a-z0-9\]+,\[a-z0-9\]+,1\\s*\\n\\.L\[0-9\]+:\\s*\\n\\s*sh1add\\.uw\\s+\[a-z0-9\]+,\[a-z0-9\]+,\[a-z0-9\]+"   } } */

/* check for the exact offsets (0, 2, 4, 6, 8, 10, 12, 14).  */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,0\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,2\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,4\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,6\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,8\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,10\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,12\\(\[a-x0-9\]+\\)" } } */
/* { dg-final { scan-assembler "lh\t\[a-x0-9\]+,14\\(\[a-x0-9\]+\\)" } } */
