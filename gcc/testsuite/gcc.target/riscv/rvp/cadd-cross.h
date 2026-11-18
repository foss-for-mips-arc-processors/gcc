/* Interleaved complex pairs.  Fixed-size cases use aligned inputs to avoid
   unaligned packed accesses.  The same-lane controls deliberately omit the
   second operand's adjacent-lane exchange.  */

#ifdef CADD_SAME_LANE
#define CADD_SWAP 0
#else
#define CADD_SWAP 1
#endif

#define CADD_PAIR_AND_LOOP(NAME, TYPE, EVEN_OP, ODD_OP) \
void __attribute__ ((noipa)) \
NAME##_pair (TYPE *restrict d, const TYPE *restrict a, \
	     const TYPE *restrict b) \
{ \
  d = __builtin_assume_aligned (d, 8); \
  a = __builtin_assume_aligned (a, 8); \
  b = __builtin_assume_aligned (b, 8); \
  d[0] = a[0] EVEN_OP b[CADD_SWAP]; \
  d[1] = a[1] ODD_OP b[1 - CADD_SWAP]; \
} \
void __attribute__ ((noipa)) \
NAME##_loop (TYPE *restrict d, const TYPE *restrict a, \
	     const TYPE *restrict b, __SIZE_TYPE__ pairs) \
{ \
  for (__SIZE_TYPE__ i = 0; i < pairs; ++i) \
    { \
      d[2 * i] = a[2 * i] EVEN_OP b[2 * i + CADD_SWAP]; \
      d[2 * i + 1] = a[2 * i + 1] ODD_OP b[2 * i + 1 - CADD_SWAP]; \
    } \
}

#define CADD_FOUR(NAME, TYPE, EVEN_OP, ODD_OP) \
void __attribute__ ((noipa)) \
NAME##_four (TYPE *restrict d, const TYPE *restrict a, \
	     const TYPE *restrict b) \
{ \
  d = __builtin_assume_aligned (d, 8); \
  a = __builtin_assume_aligned (a, 8); \
  b = __builtin_assume_aligned (b, 8); \
  d[0] = a[0] EVEN_OP b[CADD_SWAP]; \
  d[1] = a[1] ODD_OP b[1 - CADD_SWAP]; \
  d[2] = a[2] EVEN_OP b[2 + CADD_SWAP]; \
  d[3] = a[3] ODD_OP b[3 - CADD_SWAP]; \
}

CADD_PAIR_AND_LOOP (cadd90_u16, unsigned short, -, +)
CADD_PAIR_AND_LOOP (cadd270_u16, unsigned short, +, -)
CADD_FOUR (cadd90_u16, unsigned short, -, +)
CADD_FOUR (cadd270_u16, unsigned short, +, -)

#if __riscv_xlen == 64
CADD_PAIR_AND_LOOP (cadd90_u32, unsigned int, -, +)
CADD_PAIR_AND_LOOP (cadd270_u32, unsigned int, +, -)
#endif

#undef CADD_FOUR
#undef CADD_PAIR_AND_LOOP
#undef CADD_SWAP
