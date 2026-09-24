/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */

/* Test P-extension ABS instruction generation for RV32.  */

typedef int int32_t;

int32_t test_abs_i32(int32_t a) {
    return (a < 0) ? -a : a;
}
/* { dg-final { scan-assembler-times {\tabs\t} 2 } } */

int32_t test_builtin_abs(int32_t a) {
    return __builtin_abs(a);
}

