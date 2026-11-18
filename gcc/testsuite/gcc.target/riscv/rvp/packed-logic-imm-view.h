typedef unsigned char v8qi __attribute__ ((vector_size (8)));
typedef unsigned short v4hi __attribute__ ((vector_size (8)));
typedef unsigned int v2si __attribute__ ((vector_size (8)));

#define BYTE_MASK 255, 7, 0, 0, 0, 248, 255, 255
#define HALF_MASK 2047, 0, 63488, 65535
#define WORD_MASK 2047, -2048u

#define DEFINE_VIEW(TYPE, NAME, OP, MASK) \
void __attribute__ ((noipa)) \
NAME (unsigned char *out, const unsigned char *in) \
{ \
  TYPE value; \
  __builtin_memcpy (&value, in, sizeof (value)); \
  TYPE masked = value OP (TYPE) { MASK }; \
  __builtin_memcpy (out, &masked, sizeof (masked)); \
  __builtin_memcpy (out + sizeof (value), &value, sizeof (value)); \
}

DEFINE_VIEW (v8qi, bytes_and, &, BYTE_MASK)
DEFINE_VIEW (v8qi, bytes_or, |, BYTE_MASK)
DEFINE_VIEW (v8qi, bytes_xor, ^, BYTE_MASK)
DEFINE_VIEW (v4hi, halves_and, &, HALF_MASK)
DEFINE_VIEW (v4hi, halves_or, |, HALF_MASK)
DEFINE_VIEW (v4hi, halves_xor, ^, HALF_MASK)
DEFINE_VIEW (v2si, words_and, &, WORD_MASK)
DEFINE_VIEW (v2si, words_or, |, WORD_MASK)
DEFINE_VIEW (v2si, words_xor, ^, WORD_MASK)

#undef DEFINE_VIEW
#undef BYTE_MASK
#undef HALF_MASK
#undef WORD_MASK
