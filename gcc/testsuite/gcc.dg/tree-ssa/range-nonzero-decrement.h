/* Unsigned decrement comparisons at zero, small and overflowing bounds.  */
#define FN(NAME, TYPE, OP, BOUND)                                      \
int __attribute__ ((noipa))                                          \
NAME (unsigned long long input)                                     \
{                                                                  \
  TYPE x = input;                                                   \
  if (x == 0)                                                      \
    return -1;                                                     \
  return x - 1 OP (TYPE) (BOUND);                                  \
}

#define GROUP(TYPE, PREFIX, SUFFIX, BOUND)                            \
  FN (PREFIX ## _lt_ ## SUFFIX, TYPE, <, BOUND)                      \
  FN (PREFIX ## _le_ ## SUFFIX, TYPE, <=, BOUND)                     \
  FN (PREFIX ## _gt_ ## SUFFIX, TYPE, >, BOUND)                      \
  FN (PREFIX ## _ge_ ## SUFFIX, TYPE, >=, BOUND)

GROUP (unsigned int, u32, zero, 0)
GROUP (unsigned int, u32, small, 2)
GROUP (unsigned int, u32, high, (~0U - 1))
GROUP (unsigned int, u32, top, ~0U)
GROUP (unsigned long long, u64, zero, 0)
GROUP (unsigned long long, u64, small, 2)
GROUP (unsigned long long, u64, high, (~0ULL - 1))
GROUP (unsigned long long, u64, top, ~0ULL)

#undef GROUP
#undef FN
