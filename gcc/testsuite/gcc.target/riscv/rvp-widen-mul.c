/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Og" } } */

/* Test WMUL (widening signed multiply) instruction */

long long wmul_basic(int a, int b)
{
    return (long long)a * (long long)b;
}

/* Test WMULU (widening unsigned multiply) instruction */

unsigned long long wmulu_basic(unsigned int a, unsigned int b)
{
    return (unsigned long long)a * (unsigned long long)b;
}

/* Test WMULSU (widening signed-unsigned multiply) instruction */

long long wmulsu_basic(int a, unsigned int b)
{
    return (long long)a * (unsigned long long)b;
}

/* { dg-final { scan-assembler-times {\mwmul\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwmulu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwmulsu\M} 1 } } */
