/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-Og" } } */

/* Test WSUBA (widening signed subtract accumulate) instruction */

long long widen_sub_accumulate(long long a, int b, int c)
{
    return (a + ((long long)b - (long long)c));
}

/* Test WSUBAU (widening unsigned subtract accumulate) instruction */

unsigned long long widen_sub_accumulate_unsigned(unsigned long long a, unsigned int b, unsigned int c)
{
    return (a + ((unsigned long long)b - (unsigned long long)c));
}

/* { dg-final { scan-assembler-times {\mwsuba\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwsubau\M} 1 } } */
