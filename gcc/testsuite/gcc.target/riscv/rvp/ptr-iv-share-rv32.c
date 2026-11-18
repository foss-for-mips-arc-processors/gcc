/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */
/* { dg-options "-O3 -march=rv32gcpv -mabi=ilp32d -mlittle-endian -mrvv-vector-bits=scalable -fno-vect-cost-model -fno-tree-loop-distribute-patterns -fdump-tree-vect-details -fdump-tree-optimized" } */

#include "ptr-iv-share.h"

/* { dg-final { scan-tree-dump-times "Reusing vector pointer IV" 5 "vect" } } */
/* { dg-final { scan-tree-dump {\.SELECT_VL} "optimized" } } */
