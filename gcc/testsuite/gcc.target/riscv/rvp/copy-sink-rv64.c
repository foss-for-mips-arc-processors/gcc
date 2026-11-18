/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */
/* { dg-options "-O3 -march=rv64gcpv -mabi=lp64d -mlittle-endian -mrvv-vector-bits=scalable -fdump-rtl-cprop" } */

#include "copy-sink.h"

/* Check the transformation rather than incidental register allocation.
   Both the P scalar path and the RVV path must remain available.  */
/* { dg-final { scan-rtl-dump-times "Sinking copy insn" 2 "cprop1" } } */
/* { dg-final { scan-assembler {\tpmhacc\.w\t} } } */
/* { dg-final { scan-assembler {\tpmhaccu\.w\t} } } */
/* { dg-final { scan-assembler {\tvmulh\.vv\t} } } */
/* { dg-final { scan-assembler {\tvmulhu\.vv\t} } } */
