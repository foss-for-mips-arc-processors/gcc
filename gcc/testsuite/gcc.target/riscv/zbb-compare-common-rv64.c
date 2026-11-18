/* { dg-do compile } */
/* { dg-options "-march=rv64gc_zbb -mabi=lp64d -O2" } */
/* { dg-skip-if "Assembly check" { *-*-* } { "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "zbb-compare-common.h"

/*
** ule_all:
**  maxu\s+[^\n]+
**  sltiu\s+[^\n]+,5
**  ret
*/

/*
** ule_any:
**  minu\s+[^\n]+
**  sltiu\s+[^\n]+,5
**  ret
*/

/*
** slt_all:
**  max\s+[^\n]+
**  slti\s+[^\n]+,5
**  ret
*/

/*
** slt_any:
**  min\s+[^\n]+
**  slti\s+[^\n]+,5
**  ret
*/
