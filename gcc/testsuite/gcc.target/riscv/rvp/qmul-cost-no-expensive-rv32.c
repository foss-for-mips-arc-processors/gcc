/* { dg-do compile } */
/* { dg-options "-O3 -fno-expensive-optimizations -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

#include "qmul-cost.h"

/* { dg-final { scan-tree-dump-not {>> (14|30)[^\n]*times scalar_stmt costs 0} "vect" } } */
/* { dg-final { scan-tree-dump-not {RVP Q-format loop branch costs} "vect" } } */
