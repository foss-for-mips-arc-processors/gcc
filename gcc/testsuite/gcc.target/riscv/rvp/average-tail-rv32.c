/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

#include "average-tail.h"

/* Both the main loop and its four-byte epilogue use packed averages.  */
/* { dg-final { scan-assembler-times {\mpaadd\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.b\M} 1 } } */
/* { dg-final { scan-tree-dump-times "LOOP EPILOGUE VECTORIZED" 4 "vect" } } */
