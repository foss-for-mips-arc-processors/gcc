/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

void
q31_epilogue (int *__restrict out, const int *__restrict a,
	      const int *__restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    {
      long long result = ((long long) a[i] * b[i]) >> 31;
      out[i] = result > 2147483647 ? 2147483647 : result;
    }
}

/* Reuse both input pointers and the output pointer, including on the path
   that skips the vector loop.  The original bases need not be saved.  */
/* { dg-final { scan-tree-dump-times {reusing vector data pointer in scalar epilogue} 3 "vect" } } */
/* { dg-final { scan-assembler-not {addi\s+sp,sp,-} } } */
/* { dg-final { scan-assembler {\tmulq\s} } } */
