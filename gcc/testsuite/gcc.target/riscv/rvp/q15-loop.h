/* Ordinary C Q15 arithmetic and semantic controls.  */
#define FN __attribute__ ((noipa))

#define PRODUCT_LOOP(NAME, ROUND, SHIFT, LIMIT)                         \
void FN                                                               \
NAME (short *__restrict out, const short *__restrict a,                 \
      const short *__restrict b, unsigned int n)                       \
{                                                                     \
  for (unsigned int i = 0; i < n; ++i)                                 \
    {                                                                 \
      int product = (int) a[i] * b[i];                                 \
      int scaled = (product + (ROUND)) >> (SHIFT);                     \
      out[i] = scaled > (LIMIT) ? (LIMIT) : scaled;                     \
    }                                                                 \
}

PRODUCT_LOOP (q15, 0, 15, 32767)
PRODUCT_LOOP (q15_round, 16384, 15, 32767)
PRODUCT_LOOP (q15_wrong_limit, 0, 15, 32766)
PRODUCT_LOOP (q15_wrong_round, 16383, 15, 32767)
PRODUCT_LOOP (q15_shift16, 0, 16, 32767)

void FN
q15_unclamped (short *__restrict out, const short *__restrict a,
	       const short *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = ((int) a[i] * b[i]) >> 15;
}

void FN
q15_shared_product (short *__restrict out, int *__restrict saved,
		    const short *__restrict a, const short *__restrict b,
		    unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      int product = (int) a[i] * b[i];
      int scaled = product >> 15;
      saved[i] = product;
      out[i] = scaled > 32767 ? 32767 : scaled;
    }
}

void FN
q15_narrowed_product (short *__restrict out, const short *__restrict a,
		      const short *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      short product = (int) a[i] * b[i];
      out[i] = product >> 15;
    }
}
