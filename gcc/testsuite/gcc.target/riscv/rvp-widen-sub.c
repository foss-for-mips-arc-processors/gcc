/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-Og"} } */

/* Test WSUB (widening signed sub) instruction */

long long widen_sub_basic(int a, int b)
{
    return (long long)a - (long long)b;
}

/* Test WSUBU (widening unsigned sub) instruction */

unsigned long long widen_subu_basic(unsigned int a, unsigned int b)
{
    return (unsigned long long)a - (unsigned long long)b;
}

/* { dg-final { scan-assembler-times {\mwsub\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwsubu\M} 1 } } */
