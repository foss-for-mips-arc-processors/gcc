/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3" } */

#include "average-pattern-epilogue.h"

/* Use a smaller vector for the two-element epilogue.  */
/* { dg-final { scan-assembler-times {\mpsrari\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.h\M} 1 } } */
