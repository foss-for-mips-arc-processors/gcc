/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

/* Keep the input alive across the count without an unnecessary copy.  */
/*
** count_word:
**  sw\s+a0,0\(a1\)
**  clsw\s+a0,a0
**  ret
*/
int
count_word (int input, int *saved)
{
  *saved = input;
  return __builtin_clrsb (input);
}

/* The input's upper word is arbitrary; the result fills the whole GPR.  */
/*
** count_low_word:
**  sd\s+a0,0\(a1\)
**  clsw\s+a0,a0
**  ret
*/
unsigned long long
count_low_word (unsigned long long input, unsigned long long *saved)
{
  *saved = input;
  return __builtin_clrsb ((int) input);
}

/* The full-width operation must remain CLS rather than CLSW.  */
/*
** count_doubleword:
**  sd\s+a0,0\(a1\)
**  cls\s+a0,a0
**  ret
*/
int
count_doubleword (long long input, long long *saved)
{
  *saved = input;
  return __builtin_clrsbll (input);
}
