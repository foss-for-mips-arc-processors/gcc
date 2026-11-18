/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gp -mabi=ilp32d -mlittle-endian -dp" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

unsigned long long
copy_integer (unsigned long long input)
{
  register unsigned long long copy asm ("a4") = input;
  asm volatile ("" : "+r" (copy));
  return copy;
}

double
copy_double (double input)
{
  register double first asm ("a2") = input;
  asm volatile ("" : "+r" (first));
  register double second asm ("a4") = first;
  asm volatile ("" : "+r" (second));
  return second;
}

/* Native copies are four bytes, including DF values held in GPRs.  */
/* { dg-final { scan-assembler-times {\taddd\t[^\n]*l=4\][^\n]*\*movdi_32bit} 2 } } */
/* { dg-final { scan-assembler-times {\taddd\t[^\n]*l=4\][^\n]*\*movdf_hardfloat_rv32} 1 } } */
/* { dg-final { scan-assembler-not {\taddd\t[^\n]*l=8\]} } } */
