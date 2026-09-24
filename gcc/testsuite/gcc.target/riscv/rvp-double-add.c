/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" } } */

/* Test addd (double signed add) instruction */

long long double_add_basic(long long a, long long b)
{
    return a + b;
}

/* { dg-final { scan-assembler-times {\maddd\M} 1 } } */
