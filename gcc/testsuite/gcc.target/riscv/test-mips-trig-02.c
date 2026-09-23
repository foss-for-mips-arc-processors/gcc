/* { dg-do compile } */
/* { dg-options "-march=rv32imafd_xmipstrig_zfa -mtune=mips-m8500 -mabi=ilp32d" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-g" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */
/* MIPS riscv cpu m8500 - test trig support */

/*
**test_sinf:
**  tail\s+sinf
*/
extern float sinf(float x);
float test_sinf(float x) {
  return sinf(x);
}

/*
**test_cosf:
**  tail\s+cosf
*/
extern float cosf(float x);
float test_cosf(float x) {
  return cosf(x);
}

/*
**test_tanf:
**  tail\s+tanf
*/
extern float tanf(float x);
float test_tanf(float x) {
  return tanf(x);
}

/*
**test_atanf:
**  tail\s+atanf
*/
extern float atanf(float x);
float test_atanf(float x) {
  return atanf(x);
}

/*
**test_tanh:
**  tail\s+tanhf
*/
extern float tanhf(float x);
float test_tanh(float x) {
  return tanhf(x);
}

/*
**test_log2f:
**  tail\s+log2f
*/
extern float log2f(float x);
float test_log2f(float x) {
  return log2f(x);
}

/*
**test_logf:
**  tail\s+logf
*/
extern float logf(float x);
float test_logf(float x) {
  return logf(x);
}

/*
**test_log10:
**  tail\s+log10f
*/
extern float log10f(float x);
float test_log10(float x) {
  return log10f(x);
}

/*
**test_expf:
**  tail\s+expf
*/
extern float expf(float x);
float test_expf(float x) {
  return expf(x);
}

/*
**test_exp10f:
**  tail\s+exp10f
*/
extern float exp10f(float x);
float test_exp10f(float x) {
  return exp10f(x);
}

/*
**test_asinf:
**  tail\s+asinf
*/
extern float asinf(float x);
float test_asinf(float x) {
  return asinf(x);
}

/*
**test_acosf:
**  tail\s+acosf
*/
extern float acosf(float x);
float test_acosf(float x) {
  return acosf(x);
}

/*
**test_atan2f:
**  tail\s+atan2f
*/
extern float atan2f(float x, float y);
float test_atan2f(float x, float y) {
  return atan2f(x, y);
}

/*
**test_hypotf:
**  tail\s+hypotf
*/
extern float hypotf(float x, float y);
float test_hypotf(float x, float y) {
  return hypotf(x, y);
}
