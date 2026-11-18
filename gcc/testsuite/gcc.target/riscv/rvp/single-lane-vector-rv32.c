/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-rtl-expand" } */

#include "single-lane-vector-run.c"

/* { dg-final { scan-rtl-dump "reg:PV1DI" "expand" } } */
