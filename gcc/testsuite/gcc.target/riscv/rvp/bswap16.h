typedef unsigned char v4qi __attribute__ ((vector_size (4)));
typedef unsigned char v8qi __attribute__ ((vector_size (8)));

unsigned int
swap16_word (unsigned int input)
{
  union { unsigned int word; v4qi bytes; } value = { .word = input };
  value.bytes = __builtin_shufflevector (value.bytes, value.bytes, 1, 0, 3, 2);
  return value.word;
}

#if __riscv_xlen == 64
unsigned long long
swap16_doubleword (unsigned long long input)
{
  union { unsigned long long word; v8qi bytes; } value = { .word = input };
  value.bytes = __builtin_shufflevector (value.bytes, value.bytes,
				       1, 0, 3, 2, 5, 4, 7, 6);
  return value.word;
}
#endif

void
swap16_loop (unsigned short *restrict out, const unsigned short *restrict in,
	     unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = __builtin_bswap16 (in[i]);
}
