/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-rtl-combine" } */

#include "masked-select-loop.h"

/* All three loop forms must match packed selects, not only scalar tails.  */
/* { dg-final { scan-rtl-dump-times {\*mvmpv8qi} 3 "combine" } } */
/* { dg-final { scan-rtl-dump-times {\*mvmpv4hi} 3 "combine" } } */
/* { dg-final { scan-assembler-not {\m(andn|not)\M} } } */
