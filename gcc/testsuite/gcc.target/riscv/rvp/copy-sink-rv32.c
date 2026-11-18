/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */
/* { dg-options "-O3 -march=rv32gcpv -mabi=ilp32d -mlittle-endian -mrvv-vector-bits=scalable -fdump-rtl-cprop" } */

#include "copy-sink.h"

/* Check the transformation rather than incidental register allocation.
   Sink one input-pointer copy per loop.  The output base is still needed
   in the scalar preheader to compute the loop end, so keep its copy in
   place.  Both the P scalar path and the RVV path must remain available.  */
/* { dg-final { scan-rtl-dump-times "Sinking copy insn" 2 "cprop1" } } */
/* { dg-final { scan-assembler {\tmhacc\t} } } */
/* { dg-final { scan-assembler {\tmhaccu\t} } } */
/* { dg-final { scan-assembler {\tvmulh\.vv\t} } } */
/* { dg-final { scan-assembler {\tvmulhu\.vv\t} } } */
