typedef short v2hi __attribute__ ((vector_size (4)));
typedef int v2si __attribute__ ((vector_size (8)));
#define FN __attribute__ ((noipa))
#define PAIR(NAME, PRODUCT, ROUND, SHIFT, LIMIT)                         \
v2hi FN                                                               \
NAME (v2hi a, v2hi b)                                                  \
{                                                                     \
  v2hi out;                                                           \
  for (unsigned int i = 0; i < 2; ++i)                                 \
    {                                                                 \
      int product = (PRODUCT);                                       \
      int result = (product + (ROUND)) >> (SHIFT);                     \
      out[i] = result > (LIMIT) ? (LIMIT) : result;                     \
    }                                                                 \
  return out;                                                         \
}

PAIR (exact, (int) a[i] * b[i], 0, 15, 32767)
PAIR (rounding, (int) a[i] * b[i], 16384, 15, 32767)
PAIR (wrong_limit, (int) a[i] * b[i], 0, 15, 32766)
PAIR (wrong_round, (int) a[i] * b[i], 16383, 15, 32767)
PAIR (wrong_shift, (int) a[i] * b[i], 0, 16, 32767)
PAIR (unclamped, (int) a[i] * b[i], 0, 15, 2147483647)
PAIR (narrowed, (short) ((int) a[i] * b[i]), 0, 15, 32767)
PAIR (mixed, (int) (unsigned short) a[i] * b[i], 0, 15, 32767)

v2si FN
wide (v2hi a, v2hi b)
{
  v2si out;
  for (unsigned int i = 0; i < 2; ++i)
    {
      int result = ((int) a[i] * b[i]) >> 15;
      out[i] = result > 32767 ? 32767 : result;
    }
  return out;
}

v2si FN
wide_round (v2hi a, v2hi b)
{
  v2si out;
  for (unsigned int i = 0; i < 2; ++i)
    {
      int result = ((int) a[i] * b[i] + 16384) >> 15;
      out[i] = result > 32767 ? 32767 : result;
    }
  return out;
}

v2hi FN
shared (v2hi a, v2hi b, v2si *saved)
{
  v2hi out;
  v2si products;
  for (unsigned int i = 0; i < 2; ++i)
    {
      int product = (int) a[i] * b[i];
      int result = product >> 15;
      products[i] = product;
      out[i] = result > 32767 ? 32767 : result;
    }
  *saved = products;
  return out;
}

v2hi FN
shared_round (v2hi a, v2hi b, v2si *saved)
{
  v2hi out;
  v2si products;
  for (unsigned int i = 0; i < 2; ++i)
    {
      int product = (int) a[i] * b[i];
      int result = (product + 16384) >> 15;
      products[i] = product;
      out[i] = result > 32767 ? 32767 : result;
    }
  *saved = products;
  return out;
}
