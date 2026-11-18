/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-rtl-combine" } */

#include "inverted-logical-loop.h"

/* Check packed modes, not just the scalar prologue and epilogue.  */
/* { dg-final { scan-rtl-dump {\*rvp_and_notpv8qi} "combine" } } */
/* { dg-final { scan-rtl-dump {\*rvp_ior_notpv8qi} "combine" } } */
/* { dg-final { scan-rtl-dump {\*rvp_xor_notpv8qi} "combine" } } */
/* { dg-final { scan-rtl-dump {\*rvp_and_notpv4hi} "combine" } } */
/* { dg-final { scan-rtl-dump {\*rvp_ior_notpv4hi} "combine" } } */
/* { dg-final { scan-rtl-dump {\*rvp_xor_notpv4hi} "combine" } } */
/* { dg-final { scan-assembler-not {\mnot\M} } } */
