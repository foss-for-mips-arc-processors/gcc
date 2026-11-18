/* The single-lane accumulator does not need a horizontal reduction.  */
#define DOT(NAME, A, B, PRODUCT, SUM) \
SUM __attribute__ ((noipa)) \
NAME (const A *a, const B *b, unsigned int n) \
{ \
  a = __builtin_assume_aligned (a, 8); \
  b = __builtin_assume_aligned (b, 8); \
  SUM sum = 0; \
  for (unsigned int i = 0; i < n; ++i) \
    sum += (PRODUCT) a[i] * (PRODUCT) b[i]; \
  return sum; \
}

DOT (dot_ss, short, short, int, long long)
DOT (dot_uu, unsigned short, unsigned short, unsigned int, unsigned long long)
DOT (dot_su, short, unsigned short, int, long long)
DOT (dot_us, unsigned short, short, int, long long)

#undef DOT
