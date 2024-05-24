/* { dg-do run { target { riscv64*-*-* } } } */
/* { dg-options "-fdump-tree-crc -fdump-rtl-dfinish  -march=rv64gc_zbkc" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto"} } */

#include "../../gcc.c-torture/execute/crc-21.c"

/* { dg-final { scan-tree-dump "calculates CRC!" "crc"} } */
/* { dg-final { scan-tree-dump-times "Couldn't generate faster CRC code." 0 "crc"} } */
/* { dg-final { scan-rtl-dump "clmul" "dfinish"} } */
