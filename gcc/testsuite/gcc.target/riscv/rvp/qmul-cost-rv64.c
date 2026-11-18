/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-tree-vect-details" } */

#include "qmul-cost.h"

/* { dg-final { scan-tree-dump {>> 14[^\n]*times scalar_stmt costs 0} "vect" } } */
/* { dg-final { scan-tree-dump {>> 30[^\n]*times scalar_stmt costs 0} "vect" } } */
/* { dg-final { scan-tree-dump {RVP Q-format loop branch costs [1-9][0-9]* in scalar loop} "vect" } } */
/* { dg-final { scan-tree-dump {RVP Q-format loop branch costs [1-9][0-9]* in vector loop} "vect" } } */
