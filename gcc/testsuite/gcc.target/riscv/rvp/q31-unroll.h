/* Loop-control and address-stream cases for rounded Q31 multiplication.  */
#define Q31_RESULT(A, B)                                               \
  ({ long long x = ((long long) (A) * (B) + 1073741824) >> 31;          \
     (int) (x > 2147483647 ? 2147483647 : x); })
#define FN __attribute__ ((noipa))

void FN
q31u_plain (int *__restrict out, const int *__restrict a,
	    const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = Q31_RESULT (a[i], b[i]);
}

void FN
q31u_square (int *__restrict out, const int *__restrict a,
	     const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = Q31_RESULT (a[i], a[i]);
}

void FN
q31u_adjacent (int *__restrict out, const int *__restrict a,
	       const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = Q31_RESULT (a[i], a[i + 1]);
}

void FN
q31u_strided (int *__restrict out, const int *__restrict a,
	      const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = Q31_RESULT (a[i], b[2 * i]);
}

void FN
q31u_reverse (int *__restrict out, const int *__restrict a,
	      const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = Q31_RESULT (a[n - 1 - i], b[i]);
}

void FN
q31u_no_unroll (int *__restrict out, const int *__restrict a,
		const int *__restrict b, unsigned int n)
{
#pragma GCC unroll 1
  for (unsigned int i = 0; i < n; ++i)
    out[i] = Q31_RESULT (a[i], b[i]);
}

void FN
q31u_alias (int *out, const int *a, const int *b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = Q31_RESULT (a[i], b[i]);
}

void FN
q31u_fixed (int *__restrict out, const int *__restrict a,
	    const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < 4; ++i)
    out[i] = Q31_RESULT (a[i], b[i]);
}

#undef Q31_RESULT
#undef FN
