/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */

/* Test P-extension ABS/ABSW instruction generation for RV64.  */

typedef long long int64_t;
typedef int int32_t;

int64_t test_abs_i64(int64_t a) {
    return (a < 0) ? -a : a;
}

int32_t test_abs_i32(int32_t a) {
    return (a < 0) ? -a : a;
}

int64_t test_builtin_llabs(int64_t a) {
    return __builtin_llabs(a);
}

int32_t test_builtin_abs(int32_t a) {
    return __builtin_abs(a);
}

/* 2 abs instructions for 64-bit (test_abs_i64, test_builtin_llabs) */
/* { dg-final { scan-assembler-times {\tabs\t} 2 } } */

/* 2 absw instructions for 32-bit on RV64 (test_abs_i32, test_builtin_abs) */
/* { dg-final { scan-assembler-times {\tabsw\t} 2 } } */

