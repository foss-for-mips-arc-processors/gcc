/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mbig-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "scalar-extend.h"

/* Scalar DI uses high word first, unlike the P register-pair operations.  */
/* { dg-final { scan-assembler-not "\\t(addd|subd|negd|wadda?u?|wsuba?u?|wmul(u|su)?|wmacc(u|su)?)\\t" } } */
