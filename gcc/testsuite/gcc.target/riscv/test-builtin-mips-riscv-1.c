/* { dg-do compile } */
/* { dg-options "-march=rv32imafd_xmipstrig_zfa -mtune=mips-m8500 -mabi=ilp32d" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O2" "-Os" "-Oz" "-g" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

/*
**test_builtin1:
**  mips\.fsinhz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin1(float x) {
  return __builtin_riscv_mips_fsin_hz(x);
}

/*
**test_builtin2:
**  mips\.fcoshz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin2(float x) {
  return __builtin_riscv_mips_fcos_hz(x);
}

/*
**test_builtin3:
**  mips\.ftanhz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin3(float x) {
  return __builtin_riscv_mips_ftan_hz(x);
}

/*
**test_builtin4:
**  mips\.fversinhz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin4(float x) {
  return __builtin_riscv_mips_fversin_hz(x);
}

/*
**test_builtin5:
**  mips\.ffrecip\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin5(float x) {
  return __builtin_riscv_mips_ffrecip(x);
}

/*
**test_builtin6:
**  mips\.ffrsqrt\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin6(float x) {
  return __builtin_riscv_mips_ffrsqrt(x);
}

/*
**test_builtin7:
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin7(float x) {
  return __builtin_riscv_mips_fatan_hz(x);
}

/*
**test_builtin8:
**  mips\.ffexp2\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin8(float x) {
  return __builtin_riscv_mips_ffexp2(x);
}

/*
**test_builtin9:
**  mips\.ffsqrt\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin9(float x) {
  return __builtin_riscv_mips_ffsqrt(x);
}

/*
**test_builtin10:
**  mips\.fftanh\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin10(float x) {
  return __builtin_riscv_mips_fftanh(x);
}

/*
**test_builtin11:
**  mips\.fflog2\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin11(float x) {
  return __builtin_riscv_mips_fflog2(x);
}
