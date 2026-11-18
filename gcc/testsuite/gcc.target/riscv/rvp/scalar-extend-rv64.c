/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "scalar-extend.h"

/* RV32 implicit-register-pair operations must not appear on RV64.  */
/* { dg-final { scan-assembler-not "\\t(addd|subd|negd|wadda?u?|wsuba?u?|wmul(u|su)?|wmacc(u|su)?)\\t" } } */
