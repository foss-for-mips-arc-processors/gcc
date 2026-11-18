/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian --param=vect-epilogues-nomask=0 -fdump-tree-vect-details" } */

/* Explicit alignment avoids a scalar alignment prologue on RV64.  */
void __attribute__ ((noipa))
q31_aligned (int *__restrict d, const int *__restrict a,
	     const int *__restrict b, unsigned n)
{
  d = __builtin_assume_aligned (d, 8);
  a = __builtin_assume_aligned (a, 8);
  b = __builtin_assume_aligned (b, 8);
  for (unsigned i = 0; i < n; ++i)
    {
      long long result = ((long long) a[i] * b[i]) >> 31;
      d[i] = result > 2147483647 ? 2147483647 : result;
    }
}

/* { dg-final { scan-tree-dump-times {reusing vector data pointer in scalar epilogue} 3 "vect" } } */
/* { dg-final { scan-assembler {\tpmulq\.w\s} } } */
