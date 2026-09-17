/* { dg-do compile } */
/* { dg-options "-march=rv32imafd -mtune=mips-m8500 -mabi=ilp32d" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-g" } } */
/* MIPS riscv cpu m8500 trig builtins - test for error */
float test_builtin1(float x) {
  return __builtin_riscv_mips_fsin_hz(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin2(float x) {
  return __builtin_riscv_mips_fcos_hz(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin3(float x) {
  return __builtin_riscv_mips_ftan_hz(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin4(float x) {
  return __builtin_riscv_mips_fversin_hz(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin5(float x) {
  return __builtin_riscv_mips_ffrecip(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin6(float x) {
  return __builtin_riscv_mips_ffrsqrt(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin7(float x) {
  return __builtin_riscv_mips_fatan_hz(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin8(float x) {
  return __builtin_riscv_mips_ffexp2(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin9(float x) {
  return __builtin_riscv_mips_ffsqrt(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin10(float x) {
  return __builtin_riscv_mips_fftanh(x); /* { dg-error "implicit declaration of function" } */
}

float test_builtin11(float x) {
  return __builtin_riscv_mips_fflog2(x); /* { dg-error "implicit declaration of function" } */
}
