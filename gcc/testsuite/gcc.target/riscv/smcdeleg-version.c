/* { dg-do compile } */
/* { dg-options "-mriscv-attribute -march=rv64i_smcdeleg1p0 -mabi=lp64" { target { rv64 } } } */
/* { dg-options "-mriscv-attribute -march=rv32i_smcdeleg1p0 -mabi=ilp32" { target { rv32 } } } */

#ifndef __riscv_smcdeleg
#error "Feature macro for 'smcdeleg' not defined"
#endif

int
foo (void)
{
  return 0;
}

/* { dg-final { scan-assembler ".attribute arch, .*smcdeleg1p0" } } */
