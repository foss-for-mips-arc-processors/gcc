/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned char v8qi __attribute__ ((vector_size (8)));

unsigned long long
swap16_pair (unsigned long long input)
{
  union { unsigned long long word; v8qi bytes; } value = { .word = input };
  value.bytes = __builtin_shufflevector (value.bytes, value.bytes,
				       1, 0, 3, 2, 5, 4, 7, 6);
  return value.word;
}

unsigned long long
swap16_distinct_pair (unsigned long long input)
{
  union { unsigned long long word; v8qi bytes; } value = { .word = input };
  register v8qi first asm ("a2") = value.bytes;
  asm volatile ("" : "+r" (first));
  register v8qi second asm ("a4")
    = __builtin_shufflevector (first, first, 1, 0, 3, 2, 5, 4, 7, 6);
  asm volatile ("" : "+r" (second));
  value.bytes = second;
  return value.word;
}

/*
** swap16_pair:
**  ppairoe\.db\s+a0,\s*a0,\s*a0
**  ret
*/
/*
** swap16_distinct_pair:
**  ...
**  ppairoe\.db\s+a4,\s*a2,\s*a2
**  ...
*/
