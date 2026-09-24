/* { dg-do compile } */
/* { dg-options "-march=rv32imafd_xmipstrig_zfa -mtune=mips-m8500 -mabi=ilp32d" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-g" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <riscv_mips.h>

/*
**test_builtin1:
**  mips\.fsinhz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin1(float x) {
  return __riscv_mips_fsin_hz(x);
}

/*
**test_builtin2:
**  mips\.fcoshz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin2(float x) {
  return __riscv_mips_fcos_hz(x);
}

/*
**test_builtin3:
**  mips\.ftanhz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin3(float x) {
  return __riscv_mips_ftan_hz(x);
}

/*
**test_builtin4:
**  mips\.fversinhz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin4(float x) {
  return __riscv_mips_fversin_hz(x);
}

/*
**test_builtin5:
**  mips\.ffrecip\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin5(float x) {
  return __riscv_mips_ffrecip(x);
}

/*
**test_builtin6:
**  mips\.ffrsqrt\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin6(float x) {
  return __riscv_mips_ffrsqrt(x);
}

/*
**test_builtin7:
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin7(float x) {
  return __riscv_mips_fatan_hz(x);
}

/*
**test_builtin8:
**  mips\.ffexp2\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin8(float x) {
  return __riscv_mips_ffexp2(x);
}

/*
**test_builtin9:
**  mips\.ffsqrt\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin9(float x) {
  return __riscv_mips_ffsqrt(x);
}

/*
**test_builtin10:
**  mips\.fftanh\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin10(float x) {
  return __riscv_mips_fftanh(x);
}

/*
**test_builtin11:
**  mips\.fflog2\.s\s+fa[0-7],fa[0-7]
**  ret
*/
float test_builtin11(float x) {
  return __riscv_mips_fflog2(x);
}

/*
**test_builtin12:
**  fli\.s\s+fa[0-7],1.0
**  fli\.s\s+fa[0-7],0.25
**  fli\.s\s+fa[0-7],3.0
**  fnmsub\.s\s+fa[0-7],fa[0-7],fa[0-7],fa[0-7]
**  fdiv\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fsgnj\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  mips\.ffsqrt.s\s+fa[0-7],fa[0-7]
**  fdiv\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  mips\.fatanhz.s\s+fa[0-7],fa[0-7]
**  fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  mips\.fatanhz.s\s+fa[0-7],fa[0-7]
**  fmax\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  ret
*/
float test_builtin12(float x) {
  return __riscv_mips_asinf_hz(x);
}

/*
**test_builtin13:
**  fli\.s\s+fa[0-7],1.0
**  fli\.s\s+fa[0-7],0.25
**  fli\.s\s+ft[0-11],3.0
**  fnmsub\.s\s+fa[0-7],fa[0-7],fa[0-7],fa[0-7]
**  fdiv\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fsgnj\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  mips\.ffsqrt\.s\s+fa[0-7],fa[0-7]
**  fdiv\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  fmax\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fnmsub\.s\s+fa[0-7],fa[0-7],ft[0-11],fa[0-7]
**  ret
*/
float test_builtin13(float x) {
  return __riscv_mips_acosf_hz(x);
}

/*
**test_builtin14:
**  fli\.s\s+fa[0-7],0.25
**  fli\.s\s+fa[0-7],1.0
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  fdiv\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fmax\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  ret
*/
float test_builtin14(float x) {
  return __riscv_mips_tanf_fc_hz(x);
}

/*
**test_builtin15:
**  mips\.ffrecip\.s\s+fa[0-7],fa[0-7]
**  fli\.s\s+fa[0-7],0.25
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fmin\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  ret
*/
float test_builtin15(float x) {
  return __riscv_mips_atan2f_fc_hz(x);
}

/*
**test_builtin16:
**  fdiv\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fli\.s\s+fa[0-7],0.25
**  fdiv\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**  fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  fmax\.s\s+fa[0-7],fa[0-7],fa[0-7]
**  ret
*/
float test_builtin16(float x, float y) {
  return __riscv_mips_atan2f_hz(x, y);
}