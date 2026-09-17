/* { dg-do compile } */
/* { dg-options "-march=rv32imafd_xmipstrig_zfa -mtune=mips-m8500 -mabi=ilp32d -ffast-math" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O2" "-Os" "-Oz" "-g" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */
/* MIPS riscv cpu m8500 - test trig support */

/*
**test_sinf:
**	mips\.flti\.s\s+fa[0-7],5
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.fsinhz\.s\s+fa[0-7],fa[0-7]
**	ret
*/
extern float sinf(float x);
float test_sinf(float x) {
  return sinf(x);
}

/*
**test_cosf:
**	mips\.flti\.s\s+fa[0-7],5
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.fcoshz\.s\s+fa[0-7],fa[0-7]
**	ret
*/
extern float cosf(float x);
float test_cosf(float x) {
  return cosf(x);
}

/*
**test_tanf:
**	mips\.flti\.s\s+fa[0-7],5
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.ftanhz\.s\s+fa[0-7],fa[0-7]
**	ret
*/
extern float tanf(float x);
float test_tanf(float x) {
  return tanf(x);
}

/*
**test_atanf:
**	mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**	mips\.flti\.s\s+fa[0-7],3
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	ret
*/
extern float atanf(float x);
float test_atanf(float x) {
  return atanf(x);
}

/*
**test_tanh:
**	mips\.fftanh\.s\s+fa[0-7],fa[0-7]
**	ret
*/
extern float tanhf(float x);
float test_tanh(float x) {
  return tanhf(x);
}

/*
**test_log2f:
**	mips\.fflog2\.s\s+fa[0-7],fa[0-7]
**	ret
*/
extern float log2f(float x);
float test_log2f(float x) {
  return log2f(x);
}

/*
**test_logf:
**	mips\.fflog2\.s\s+fa[0-7],fa[0-7]
**	mips\.flti\.s\s+fa[0-7],6
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	ret
*/
extern float logf(float x);
float test_logf(float x) {
  return logf(x);
}

/*
**test_log10:
**	mips\.fflog2\.s\s+fa[0-7],fa[0-7]
**	mips\.flti\.s\s+fa[0-7],9
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	ret
*/
extern float log10f(float x);
float test_log10(float x) {
  return log10f(x);
}

/*
**test_expf:
**	mips\.flti\.s\s+fa[0-7],7
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.ffexp2\.s\s+fa[0-7],fa[0-7]
**	ret
*/
extern float expf(float x);
float test_expf(float x) {
  return expf(x);
}

/*
**test_exp10f:
**	mips\.flti\.s\s+fa[0-7],8
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.ffexp2\.s\s+fa[0-7],fa[0-7]
**	ret
*/
extern float exp10f(float x);
float test_exp10f(float x) {
  return exp10f(x);
}

/*
**test_asinf:
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.ffrecip\.s\s+fa[0-7],fa[0-7]
**	fli\.s\s+fa[0-7],1\.0
**	fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.ffsqrt\.s\s+fa[0-7],fa[0-7]
**	mips\.ffrsqrt\.s\s+fa[0-7],fa[0-7]
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**	fli\.s\s+fa[0-7],0\.25
**	fsgnj\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**	fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	fmax\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.flti\.s\s+fa[0-7],3
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	ret
*/
extern float asinf(float x);
float test_asinf(float x) {
  return asinf(x);
}

/*
**test_acosf:
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.ffrecip\.s\s+fa[0-7],fa[0-7]
**	fli\.s\s+fa[0-7],1\.0
**	fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.ffsqrt\.s\s+fa[0-7],fa[0-7]
**	mips\.ffrsqrt\.s\s+fa[0-7],fa[0-7]
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**	fli\.s\s+fa[0-7],0\.25
**	fsgnj\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**	fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	fmax\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	fsub\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.flti\.s\s+fa[0-7],3
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	ret
*/
extern float acosf(float x);
float test_acosf(float x) {
  return acosf(x);
}

/*
**test_atan2f:
**	fdiv\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.fatanhz\.s\s+fa[0-7],fa[0-7]
**	mips\.flti\.s\s+fa[0-7],3
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	ret
*/
extern float atan2f(float x, float y);
float test_atan2f(float x, float y) {
  return atan2f(x, y);
}

/*
**test_hypotf:
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	fmul\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	fadd\.s\s+fa[0-7],fa[0-7],fa[0-7]
**	mips\.ffsqrt\.s\s+fa[0-7],fa[0-7]
**	ret
*/
extern float hypotf(float x, float y);
float test_hypotf(float x, float y) {
  return hypotf(x, y);
}
