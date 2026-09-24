/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" } } */

/* Test codegen "wadd rd_p, rs1_p, zero" */
long long extend_basic(int a)
{
    return (long long)a;
}

/* Test codegen "li {rd_p+1}, 0" */
unsigned long long extend_basic_unsigned(unsigned int a)
{
    return (unsigned long long)a;
}

/* { dg-final { scan-assembler-times {\mwadd\M} 1 } } */
/* { dg-final { scan-assembler-times {\mli\M} 1 } } */
