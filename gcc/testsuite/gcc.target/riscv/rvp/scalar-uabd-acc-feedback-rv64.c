/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#define RVP_ACC_COMPILE_ONLY
#include "scalar-uabd-acc-feedback-run.c"

/*
** feedback_acc:
**  ...
**  pabdsumau\.b\s+a0,a0,[a-z][0-9]+
**  ...
*/

/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 1 } } */
/* { dg-final { scan-assembler-not {\tpabdu\.h\t} } } */
