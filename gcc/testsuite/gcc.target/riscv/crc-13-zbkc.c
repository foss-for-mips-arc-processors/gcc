/* { dg-do run } */
/* { dg-options "-fdump-tree-crc -fdump-rtl-dfinish " } */
/* { dg-additional-options "-march=rv64gc_zbkc" { target { rv64 } } } */
/* { dg-additional-options "-march=rv32gc_zbkc" { target { rv32 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto"} } */

#include "../../gcc.c-torture/execute/crc-13.c"

/* { dg-final { scan-tree-dump "calculates CRC!" "crc"} } */
/* { dg-final { scan-tree-dump-times "Couldn't generate faster CRC code." 0 "crc"} } */
/* { dg-final { scan-rtl-dump "clmul" "dfinish"} } */
