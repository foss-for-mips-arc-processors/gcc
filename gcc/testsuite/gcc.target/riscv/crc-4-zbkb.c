/* { dg-do run } */
/* { dg-options "-fdump-tree-crc-details" } */
/* { dg-additional-options "-march=rv64gc_zbkb" { target { rv64 } } } */
/* { dg-additional-options "-march=rv32gc_zbkb" { target { rv32 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto"} } */

#include "../../gcc.c-torture/execute/crc-4.c"

/* { dg-final { scan-tree-dump "calculates CRC!" "crc"} } */
/* { dg-final { scan-tree-dump-times "Couldn't generate faster CRC code." 0 "crc"} } */
