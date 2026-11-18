/* Scalar bit containers keep the vector argument ABI out of this test.
   Shuffle indices always name logical lanes, independent of endianness.  */
typedef unsigned char v4qi __attribute__ ((vector_size (4)));
typedef unsigned short v2hi __attribute__ ((vector_size (4)));
typedef unsigned char v8qi __attribute__ ((vector_size (8)));
typedef unsigned short v4hi __attribute__ ((vector_size (8)));
typedef unsigned int v2si __attribute__ ((vector_size (8)));
typedef unsigned int u32;
typedef unsigned long long u64;

#define PERMUTE(V, U, NAME, KIND, FIRST, SECOND, ...)                   \
  __attribute__ ((noipa)) U                                           \
  perm_##V##_##NAME##_##KIND (U first, U second)                       \
  {                                                                  \
    union { V vector; U bits; } a = { .bits = first };                 \
    union { V vector; U bits; } b = { .bits = second }, result;        \
    result.vector = __builtin_shufflevector (FIRST, SECOND,           \
					    __VA_ARGS__);                     \
    return result.bits;                                              \
  }

#define CASES(V, U, NAME, ...)                                        \
  PERMUTE (V, U, NAME, normal, a.vector, b.vector, __VA_ARGS__)         \
  PERMUTE (V, U, NAME, swapped, b.vector, a.vector, __VA_ARGS__)        \
  PERMUTE (V, U, NAME, same, a.vector, a.vector, __VA_ARGS__)

/* For two lanes, zip/unzip and same-input reversal are also pair cases.  */
#define PAIRS2(V, U)                                                 \
  CASES (V, U, pair00, 0, 2)                                        \
  CASES (V, U, pair01, 0, 3)                                        \
  CASES (V, U, pair10, 1, 2)                                        \
  CASES (V, U, pair11, 1, 3)

#define PAIRS4(V, U)                                                 \
  CASES (V, U, pair00, 0, 4, 2, 6)                                  \
  CASES (V, U, pair01, 0, 5, 2, 7)                                  \
  CASES (V, U, pair10, 1, 4, 3, 6)                                  \
  CASES (V, U, pair11, 1, 5, 3, 7)

#define PAIRS8(V, U)                                                 \
  CASES (V, U, pair00, 0, 8, 2, 10, 4, 12, 6, 14)                   \
  CASES (V, U, pair01, 0, 9, 2, 11, 4, 13, 6, 15)                   \
  CASES (V, U, pair10, 1, 8, 3, 10, 5, 12, 7, 14)                   \
  CASES (V, U, pair11, 1, 9, 3, 11, 5, 13, 7, 15)

#define EXTRA4(V, U)                                                 \
  CASES (V, U, zip0, 0, 4, 1, 5)                                    \
  CASES (V, U, zip1, 2, 6, 3, 7)                                    \
  CASES (V, U, unzip0, 0, 2, 4, 6)                                  \
  CASES (V, U, unzip1, 1, 3, 5, 7)                                  \
  CASES (V, U, reverse, 3, 2, 1, 0)                                 \
  CASES (V, U, half_reverse, 2, 3, 0, 1)

#define EXTRA8(V, U)                                                 \
  CASES (V, U, zip0, 0, 8, 1, 9, 2, 10, 3, 11)                      \
  CASES (V, U, zip1, 4, 12, 5, 13, 6, 14, 7, 15)                    \
  CASES (V, U, unzip0, 0, 2, 4, 6, 8, 10, 12, 14)                   \
  CASES (V, U, unzip1, 1, 3, 5, 7, 9, 11, 13, 15)                   \
  CASES (V, U, reverse, 7, 6, 5, 4, 3, 2, 1, 0)                     \
  CASES (V, U, half_reverse, 6, 7, 4, 5, 2, 3, 0, 1)

PAIRS4 (v4qi, u32)
EXTRA4 (v4qi, u32)
CASES (v4qi, u32, bswap16, 1, 0, 3, 2)
PAIRS2 (v2hi, u32)
PAIRS8 (v8qi, u64)
EXTRA8 (v8qi, u64)
CASES (v8qi, u64, bswap16, 1, 0, 3, 2, 5, 4, 7, 6)
CASES (v8qi, u64, bswap32, 3, 2, 1, 0, 7, 6, 5, 4)
PAIRS4 (v4hi, u64)
EXTRA4 (v4hi, u64)
PAIRS2 (v2si, u64)

/* The original RV64 big-endian loop ICE, with address arithmetic kept in
   pointer precision.  The interleaved subtraction/addition needs a shuffle.  */
__attribute__ ((noipa)) void
perm_complex_u16 (unsigned short *restrict out,
		  const unsigned short *restrict a,
		  const unsigned short *restrict b, unsigned int n)
{
  for (__SIZE_TYPE__ i = 0; i < n; ++i)
    {
      out[2 * i] = a[2 * i] - b[2 * i + 1];
      out[2 * i + 1] = a[2 * i + 1] + b[2 * i];
    }
}

#undef EXTRA8
#undef EXTRA4
#undef PAIRS8
#undef PAIRS4
#undef PAIRS2
#undef CASES
#undef PERMUTE
