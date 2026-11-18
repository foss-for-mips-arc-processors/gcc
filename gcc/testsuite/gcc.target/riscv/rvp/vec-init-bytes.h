typedef unsigned char v4qi __attribute__ ((vector_size (4)));
typedef unsigned char v8qi __attribute__ ((vector_size (8)));

unsigned int
make_bytes4 (unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
  union { v4qi lanes; unsigned int raw; } value = {
    .lanes = { a, b, c, d }
  };
  return value.raw;
}

unsigned long long
make_bytes8 (unsigned int a, unsigned int b, unsigned int c, unsigned int d,
	     unsigned int e, unsigned int f, unsigned int g, unsigned int h)
{
  union { v8qi lanes; unsigned long long raw; } value = {
    .lanes = { a, b, c, d, e, f, g, h }
  };
  return value.raw;
}
