/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "scalar-extend.h"

/* Keep the single-instruction widening paths for little-endian pairs.  */
/* { dg-final { scan-assembler "\\twadd\\t" } } */
/* { dg-final { scan-assembler "\\twaddu\\t" } } */
/* { dg-final { scan-assembler "\\twmul\\t" } } */
/* { dg-final { scan-assembler "\\twmulu\\t" } } */
/* { dg-final { scan-assembler "\\twmulsu\\t" } } */
