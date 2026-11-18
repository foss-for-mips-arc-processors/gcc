/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-tree-vect-details" } */

#include "autovec-sad-wide-codegen.h"

/* { dg-final { scan-assembler-times {\tpabd\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpabd\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpredsumu\.bs\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpredsumu\.hs\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpm4addau\.b\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpm2addau\.h\t} 2 } } */
/* { dg-final { scan-tree-dump-times {SAD_EXPR[^\n]*1 times vector_stmt costs 2 in body} 6 "vect" } } */
