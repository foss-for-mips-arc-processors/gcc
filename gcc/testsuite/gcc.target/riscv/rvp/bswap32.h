typedef unsigned long long u64;
typedef unsigned char v8qi __attribute__ ((vector_size (8)));

u64
swap32_first (u64 first, u64 second)
{
  union { u64 word; v8qi bytes; } a = { .word = first };
  union { u64 word; v8qi bytes; } b = { .word = second };
  a.bytes = __builtin_shufflevector (a.bytes, b.bytes,
				   3, 2, 1, 0, 7, 6, 5, 4);
  return a.word;
}

u64
swap32_second (u64 first, u64 second)
{
  union { u64 word; v8qi bytes; } a = { .word = first };
  union { u64 word; v8qi bytes; } b = { .word = second };
  a.bytes = __builtin_shufflevector (a.bytes, b.bytes,
				   11, 10, 9, 8, 15, 14, 13, 12);
  return a.word;
}
