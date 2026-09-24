/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" } } */

/* Test WADD (widening signed add) instruction */

long long widen_add_basic(int a, int b)
{
    return (long long)a + (long long)b;
}

/* Test WADDU (widening unsigned add) instruction */

unsigned long long widen_addu_basic(unsigned int a, unsigned int b)
{
    return (unsigned long long)a + (unsigned long long)b;
}

/* { dg-final { scan-assembler-times {\mwadd\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwaddu\M} 1 } } */
