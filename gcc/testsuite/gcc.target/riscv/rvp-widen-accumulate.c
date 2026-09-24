/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" } } */

/* Test WADDA (widening signed accumulate) instruction */

long long widen_accumulate(long long a, int b, int c)
{
    return (a + ((long long)b + (long long)c));
}

/* Test WADDAU (widening unsigned accumulate) instruction */

unsigned long long widen_accumulate_unsigned(unsigned long long a, unsigned int b, unsigned int c)
{
    return (a + ((unsigned long long)b + (unsigned long long)c));
}

/* Test WADDA with x0 operand */

long long widen_accumulate_zero(long long a, int b)
{
    return a + (long long)b;
}

/* Test WADDAU with x0 operand */

unsigned long long widen_accumulate_zero_unsigned(unsigned long long a, unsigned int b)
{
    return a + (unsigned long long)b;
}

/* { dg-final { scan-assembler-times {\mwadda\M} 2 } } */
/* { dg-final { scan-assembler-times {\mwaddau\M} 2 } } */
