/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -mtune=generic -fdump-tree-vect-details" } */

#include "bswap32-cost.h"

/* { dg-final { scan-tree-dump {__builtin_bswap32[^\n]*1 times vec_perm costs 2 in body} "vect" } } */
/* { dg-final { scan-tree-dump {__builtin_bswap16[^\n]*1 times vec_perm costs 1 in body} "vect" } } */
