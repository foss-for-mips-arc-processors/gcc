/* { dg-do compile } */
/* { dg-require-effective-target arcv_udsp } */
/* { dg-options "-march=rv32i_xarcvudsp -mabi=ilp32" } */

int
foo1 (int a, int b)
{
	int retval = 0;
	retval = __builtin_riscv_arcv_udsp_xvwsrdot_vv_i16m1(retval, a, b);

	return retval;
}

/* { dg-final { scan-assembler-times "arcv\\.xvwsrdot\\.vv" 1 } } */
