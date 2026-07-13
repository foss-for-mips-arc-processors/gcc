/* { dg-do compile } */
/* { dg-options "-march=rv64gc -mabi=lp64d" } */

/* { dg-error "require the P extension" "" { target *-*-* } 0 } */
#include <riscv_packed_simd.h>
