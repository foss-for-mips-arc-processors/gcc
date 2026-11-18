/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian -fno-tree-vectorize" } */

typedef unsigned char v4qi __attribute__ ((vector_size (4)));

/* A constant byte keeps this on the scalar packing path.  The highest
   variable byte should provide the word's sign extension with SLLIW.  */
unsigned int
truncate_bytes (unsigned int a, unsigned int b, unsigned int d)
{
  union { v4qi lanes; unsigned int raw; } value = {
    .lanes = { a, b, 0x81, d }
  };
  return value.raw;
}

/* { dg-final { scan-assembler-times {\tslliw\t} 1 } } */
/* { dg-final { scan-assembler-not {\tsext\.w\t} } } */
