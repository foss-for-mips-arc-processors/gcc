/* Ordinary Q31 arithmetic and semantic controls.  */
#define FN __attribute__ ((noipa))

#define PRODUCT_LOOP(NAME, A, B, W, ROUND, SHIFT, LIMIT)                  \
void FN                                                               \
NAME (int *__restrict out, const A *__restrict a,                      \
      const B *__restrict b, unsigned int n)                           \
{                                                                     \
  for (unsigned int i = 0; i < n; ++i)                                 \
    {                                                                 \
      W product = (W) a[i] * b[i];                                    \
      W result = (product + (ROUND)) >> (SHIFT);                       \
      out[i] = result > (LIMIT) ? (LIMIT) : result;                     \
    }                                                                 \
}

PRODUCT_LOOP (q31, int, int, long long, 0, 31, 2147483647)
PRODUCT_LOOP (q31_round, int, int, long long, 1073741824, 31, 2147483647)
PRODUCT_LOOP (q31_wrong_limit, int, int, long long, 0, 31, 2147483646)
PRODUCT_LOOP (q31_wrong_round, int, int, long long, 1073741823, 31, 2147483647)
PRODUCT_LOOP (q31_shift32, int, int, long long, 0, 32, 2147483647)
PRODUCT_LOOP (q31_unsigned, unsigned int, unsigned int, unsigned long long,
	      1073741824, 31, 2147483647)
PRODUCT_LOOP (q31_mixed, int, unsigned int, long long,
	      1073741824, 31, 2147483647)

void FN
q31_unclamped (int *__restrict out, const int *__restrict a,
	       const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = ((long long) a[i] * b[i]) >> 31;
}

void FN
q31_narrowed (int *__restrict out, const int *__restrict a,
	      const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      int product = (long long) a[i] * b[i];
      out[i] = product >> 31;
    }
}

void FN
q31_lower_clamp (int *__restrict out, const int *__restrict a,
		 const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      long long result = ((long long) a[i] * b[i]) >> 31;
      result = result < -2147483646 ? -2147483646 : result;
      out[i] = result > 2147483647 ? 2147483647 : result;
    }
}

void FN
q31_two_shifts (int *__restrict out, const int *__restrict a,
		const int *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      long long result = ((((long long) a[i] * b[i]) >> 30) + 1) >> 1;
      out[i] = result > 2147483647 ? 2147483647 : result;
    }
}

void FN
q31_shared (int *__restrict out, long long *__restrict saved,
	    const int *__restrict a, const int *__restrict b,
	    unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      long long product = (long long) a[i] * b[i];
      long long result = product >> 31;
      saved[i] = product;
      out[i] = result > 2147483647 ? 2147483647 : result;
    }
}

#define WIDE_LOOP(NAME, ROUND)                                         \
void FN                                                               \
NAME (long long *__restrict out, const int *__restrict a,              \
      const int *__restrict b, unsigned int n)                         \
{                                                                     \
  for (unsigned int i = 0; i < n; ++i)                                 \
    {                                                                 \
      long long result = ((long long) a[i] * b[i] + (ROUND)) >> 31;     \
      out[i] = result > 2147483647 ? 2147483647 : result;               \
    }                                                                 \
}

WIDE_LOOP (q31_wide, 0)
WIDE_LOOP (q31_wide_round, 1073741824)

typedef int v2si __attribute__ ((vector_size (8)));
typedef long long v2di __attribute__ ((vector_size (16)));

int FN
scalar (int a, int b)
{
  long long result = ((long long) a * b) >> 31;
  return result > 2147483647 ? 2147483647 : result;
}

int FN
rounded (int a, int b)
{
  long long result = ((long long) a * b + 1073741824) >> 31;
  return result > 2147483647 ? 2147483647 : result;
}

#define PAIR(NAME, ROUND)                                              \
v2si FN                                                               \
NAME (v2si a, v2si b)                                                  \
{                                                                     \
  v2si out;                                                           \
  for (unsigned int i = 0; i < 2; ++i)                                 \
    {                                                                 \
      long long result = ((long long) a[i] * b[i] + (ROUND)) >> 31;     \
      out[i] = result > 2147483647 ? 2147483647 : result;               \
    }                                                                 \
  return out;                                                         \
}

PAIR (pair, 0)
PAIR (pair_round, 1073741824)

#define SHARED(NAME, ROUND)                                            \
v2si FN                                                               \
NAME (v2si a, v2si b, v2di *saved)                                     \
{                                                                     \
  v2si out;                                                           \
  v2di products;                                                      \
  for (unsigned int i = 0; i < 2; ++i)                                 \
    {                                                                 \
      long long product = (long long) a[i] * b[i];                     \
      long long result = (product + (ROUND)) >> 31;                    \
      products[i] = product;                                          \
      out[i] = result > 2147483647 ? 2147483647 : result;               \
    }                                                                 \
  *saved = products;                                                   \
  return out;                                                         \
}

SHARED (shared, 0)
SHARED (shared_round, 1073741824)
