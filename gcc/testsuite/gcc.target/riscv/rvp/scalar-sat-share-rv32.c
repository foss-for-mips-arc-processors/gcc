/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -fdump-tree-optimized" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "scalar-sat-share.h"

/* { dg-final { scan-tree-dump-times "\\.SAT_ADD " 1 "optimized" } } */
/* { dg-final { scan-tree-dump-not "\\.ADD_OVERFLOW|PHI <" "optimized" } } */
/* { dg-final { scan-assembler-times {\tsaddu\s} 1 } } */
/* { dg-final { scan-assembler-not {\t(b(eq|ne|lt|ge)(u|z)?|j)\s} } } */
