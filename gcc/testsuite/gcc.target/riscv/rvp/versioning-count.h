#define MAC(NAME, S, U, W) \
  void NAME (W *restrict d, const S *restrict a, const U *restrict b, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] += (W) ((long long) a[i] * b[i]); \
  }

MAC (byte_mac, signed char, unsigned char, unsigned short)
MAC (half_mac, short, unsigned short, unsigned)

#undef MAC
