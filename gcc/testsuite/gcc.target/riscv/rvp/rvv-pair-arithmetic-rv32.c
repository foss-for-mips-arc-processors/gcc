/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcpv -mabi=ilp32d -mlittle-endian" } */

typedef unsigned long long u64;
typedef unsigned char v8qi __attribute__ ((vector_size (8)));

#define KERNEL(NAME, EXPR) \
  u64 __attribute__ ((noipa)) \
  NAME (const u64 *input, u64 *original, u64 initial) \
  { \
    v8qi values[8]; \
    __builtin_memcpy (values, input, sizeof (values)); \
    u64 result = initial; \
    for (unsigned int i = 0; i < 8; ++i) \
      { \
	union { u64 word; v8qi bytes; } value = { .bytes = values[i] }; \
	original[i] = value.word; \
	value.bytes = __builtin_shufflevector (value.bytes, value.bytes, \
					     3, 2, 1, 0, 7, 6, 5, 4); \
	result = (EXPR); \
      } \
    return result; \
  }

KERNEL (add_left, value.word + result)
KERNEL (add_right, result + value.word)
KERNEL (sub_left, value.word - result)
KERNEL (sub_right, result - value.word)
KERNEL (xor_words, result ^ value.word)
KERNEL (or_words, result | value.word)
KERNEL (and_words, result & value.word)
KERNEL (neg_words, -value.word + result)
