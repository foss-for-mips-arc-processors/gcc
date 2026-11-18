typedef unsigned char v4qi __attribute__ ((vector_size (4)));
typedef unsigned char v8qi __attribute__ ((vector_size (8)));
typedef unsigned short v2hi __attribute__ ((vector_size (4)));
typedef unsigned short v4hi __attribute__ ((vector_size (8)));
typedef unsigned int v2si __attribute__ ((vector_size (8)));

v4qi __attribute__ ((noipa))
and_bytes (v4qi x)
{
  return x & (v4qi) { 127, 0, 0, 0 };
}

v2hi __attribute__ ((noipa))
or_halfwords (v2hi x)
{
  return x | (v2hi) { 2047, 0 };
}

v4qi __attribute__ ((noipa))
xor_bytes (v4qi x)
{
  return x ^ (v4qi) { 128, 255, 255, 255 };
}

v2si __attribute__ ((noipa))
and_words (v2si x)
{
#if __riscv_xlen == 32
  return x & (v2si) { -2048u, 2047 };
#else
  return x & (v2si) { 2047, 0 };
#endif
}

v4hi __attribute__ ((noipa))
or_wide_halfwords (v4hi x)
{
#if __riscv_xlen == 32
  return x | (v4hi) { 127, 0, 15, 0 };
#else
  return x | (v4hi) { 63488, 65535, 65535, 65535 };
#endif
}

v8qi __attribute__ ((noipa))
xor_wide_bytes (v8qi x)
{
#if __riscv_xlen == 32
  return x ^ (v8qi) { 128, 255, 255, 255, 16, 0, 0, 0 };
#else
  return x ^ (v8qi) { 128, 255, 255, 255, 255, 255, 255, 255 };
#endif
}
