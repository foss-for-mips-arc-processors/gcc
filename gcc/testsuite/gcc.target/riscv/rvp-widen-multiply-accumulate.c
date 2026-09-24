/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Og" } } */

/* Test WMACC (widening signed multiply-accumulate) instruction */

long long widen_mult_accumulate(long long a, int b, int c)
{
    return (a + (long long)b * (long long)c);
}

/* Test WMACCU (widening unsigned multiply-accumulate) instruction */

unsigned long long widen_mult_accumulate_unsigned(unsigned long long a, unsigned int b, unsigned int c)
{
    return (a + (unsigned long long)b * (unsigned long long)c);
}

/* Test WMACCSU (widening signed-unsigned multiply-accumulate) instruction */

unsigned long long widen_mult_accumulate_signed_unsigned(unsigned long long a, int b, unsigned int c)
{
    return (a + (long long)b * (unsigned long long)c);
}

/* { dg-final { scan-assembler-times {\mwmacc\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwmaccu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwmaccsu\M} 1 } } */
