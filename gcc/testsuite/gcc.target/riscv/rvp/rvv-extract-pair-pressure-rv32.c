/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcpv -mabi=ilp32d -mlittle-endian" } */

typedef unsigned long long u64;
typedef unsigned char v8qi __attribute__ ((vector_size (8)));

/* Materialize RVV scalar views before P pair arithmetic reaches reload.
   Keep the input values live while accumulating their permutations.  */
u64 __attribute__ ((noipa))
extract_pair_pressure (const u64 *input, u64 *original)
{
  v8qi values[8];
  __builtin_memcpy (values, input, sizeof (values));
  u64 result = 0;
  for (unsigned int i = 0; i < 8; ++i)
    {
      union { u64 word; v8qi bytes; } value = { .bytes = values[i] };
      original[i] = value.word;
      value.bytes = __builtin_shufflevector (value.bytes, value.bytes,
					   3, 2, 1, 0, 7, 6, 5, 4);
      result += value.word;
    }
  return result;
}
