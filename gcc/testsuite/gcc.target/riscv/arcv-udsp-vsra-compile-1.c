/* { dg-do compile } */
/* { dg-require-effective-target arcv_udsp } */
/* { dg-options "-march=rv32i_xarcvudsp -mabi=ilp32" } */

int
foo1 (int a, int b)
{
	return __builtin_riscv_arcv_udsp_xvsra_vx_i16m1(a, b);
}

/* { dg-final { scan-assembler-times "arcv\\.xvsra\\.vx" 1 } } */
