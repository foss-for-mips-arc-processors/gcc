/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d" } */
/* { dg-final { check-function-bodies "**" "" } } */

/* The sign of a word is independent of the upper word.  Taking a DI
   absolute value before truncation is a different operation.  */

typedef int v2si __attribute__ ((vector_size (8)));

/*
** abs_low_word:
**  ...
**  absw\t[^\n]+
**  ...
*/
int __attribute__ ((noipa))
abs_low_word (long long x)
{
  return __builtin_abs ((int) x);
}

/*
** abs_then_word:
**  ...
**  abs\t[^\n]+
**  ...
*/
long long __attribute__ ((noipa))
abs_then_word (long long x)
{
  return (int) __builtin_llabs (x);
}

/* Use pointers so this checks packed lane lowering, not a vector argument
   or result ABI.  All runtime inputs avoid INT_MIN.  */
void __attribute__ ((noipa))
abs_packed_words (const v2si *input, v2si *output)
{
  v2si value = *input;
  v2si sign = value >> 31;
  *output = (value + sign) ^ sign;
}
