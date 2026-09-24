/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-Og"} } */

/* Test subd (double signed sub) instruction */

long long double_sub_basic(long long a, long long b)
{
    return a - b;
}

/* { dg-final { scan-assembler-times {\msubd\M} 1 } } */
