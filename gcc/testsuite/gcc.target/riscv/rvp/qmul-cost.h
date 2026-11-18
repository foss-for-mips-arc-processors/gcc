/* Scalar Q-format fusion costs must retain shared and wide computations.  */
#define FN __attribute__ ((noipa))
#define LOOP(NAME, NARROW, WIDE, LIMIT, EXPR, SAVE)                      \
void FN                                                               \
NAME (NARROW *__restrict out, WIDE *__restrict saved,                  \
      const NARROW *__restrict a, const NARROW *__restrict b,          \
      unsigned int n)                                                \
{                                                                    \
  for (unsigned int i = 0; i < n; ++i)                                \
    {                                                                \
      WIDE product = (WIDE) a[i] * b[i];                             \
      WIDE scaled = (EXPR);                                         \
      WIDE clipped = scaled > (LIMIT) ? (LIMIT) : scaled;             \
      out[i] = clipped;                                              \
      SAVE;                                                          \
    }                                                                \
}

LOOP (cost_q15_round, short, int, 32767,
      (product + 16384) >> 15, (void) saved)
LOOP (cost_q15_two, short, int, 32767,
      ((product >> 14) + 1) >> 1, (void) saved)
LOOP (cost_q15_product, short, int, 32767,
      (product + 16384) >> 15, saved[i] = product)
LOOP (cost_q15_scaled, short, int, 32767,
      ((product >> 14) + 1) >> 1, saved[i] = scaled)
LOOP (cost_q31_round, int, long long, 2147483647,
      (product + 1073741824) >> 31, (void) saved)
LOOP (cost_q31_two, int, long long, 2147483647,
      ((product >> 30) + 1) >> 1, (void) saved)
LOOP (cost_q31_product, int, long long, 2147483647,
      (product + 1073741824) >> 31, saved[i] = product)
LOOP (cost_q31_wide, int, long long, 2147483647,
      ((product >> 30) + 1) >> 1, saved[i] = clipped)
