/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-rtl-combine" } */

#include "masked-word-mul.h"

/* { dg-final { scan-rtl-dump {rvp_masked_mulpv2si3} "combine" } } */
