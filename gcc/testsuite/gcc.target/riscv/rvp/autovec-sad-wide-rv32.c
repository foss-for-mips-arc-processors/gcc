/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

#include "autovec-sad-wide-codegen.h"

/* { dg-final { scan-assembler-times {\tpabd\.db\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpabd\.dh\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.dh\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpredsumu\.dbs\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpredsumu\.dhs\t} 2 } } */
/* { dg-final { scan-assembler-times {\twaddau\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpm4addau\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpm2addau\.h\t} 4 } } */
/* { dg-final { scan-tree-dump-times {SAD_EXPR[^\n]*1 times vector_stmt costs 3 in body} 6 "vect" } } */
