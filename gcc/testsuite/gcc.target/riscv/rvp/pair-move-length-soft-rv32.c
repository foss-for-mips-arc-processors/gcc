/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32imacp -mabi=ilp32 -mlittle-endian -dp" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

double
copy_double (double input)
{
  register double copy asm ("a4") = input;
  asm volatile ("" : "+r" (copy));
  return copy;
}

/* Compression does not shorten the native register-pair copies.  */
/* { dg-final { scan-assembler-times {\taddd\t[^\n]*l=4\][^\n]*\*movdf_softfloat} 2 } } */
/* { dg-final { scan-assembler-not {\taddd\t[^\n]*l=8\]} } } */
