typedef unsigned char v4qi __attribute__ ((vector_size (4)));
typedef unsigned char v8qi __attribute__ ((vector_size (8)));
typedef unsigned short v4hi __attribute__ ((vector_size (8)));

unsigned int
repeat_bytes4 (unsigned char a, unsigned char b)
{
  union { v4qi lanes; unsigned int raw; } value = {
    .lanes = { a, b, a, b }
  };
  return value.raw;
}

unsigned long long
repeat_bytes8 (unsigned char a, unsigned char b)
{
  union { v8qi lanes; unsigned long long raw; } value = {
    .lanes = { a, b, a, b, a, b, a, b }
  };
  return value.raw;
}

unsigned long long
repeat_halfwords (unsigned short a, unsigned short b)
{
  union { v4hi lanes; unsigned long long raw; } value = {
    .lanes = { a, b, a, b }
  };
  return value.raw;
}
