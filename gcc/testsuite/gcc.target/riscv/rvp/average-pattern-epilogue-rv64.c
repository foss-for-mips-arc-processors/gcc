/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3" } */

#include "average-pattern-epilogue.h"

/* Main loop and two-element vector epilogue.  */
/* { dg-final { scan-assembler-times {\mpsrari\.h\M} 2 } } */
