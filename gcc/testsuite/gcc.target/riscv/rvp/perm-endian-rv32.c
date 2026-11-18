/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mbig-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

/* Compile every pair, zip, unzip and reversal with distinct, swapped and
   identical inputs, including double-register packed modes.  */
#include "perm-endian.h"

/*
** perm_v4qi_pair00_normal:
** ...
** ppairo\.b\s+a0,\s*a1,\s*a0
** ...
*/
/*
** perm_v2hi_pair00_normal:
** ...
** ppairo\.h\s+a0,\s*a1,\s*a0
** ...
*/
/*
** perm_v8qi_pair00_normal:
** ...
** ppairo\.db\s+a0,\s*a2,\s*a0
** ...
*/
/*
** perm_v4hi_pair00_normal:
** ...
** ppairo\.dh\s+a0,\s*a2,\s*a0
** ...
*/
/*
** perm_v2si_pair00_normal:
** ...
** mv\s+a1,\s*a2
** ...
*/
/*
** perm_v8qi_pair01_swapped:
** ...
** ppaireo\.db\s+a0,\s*a0,\s*a2
** ...
*/
/*
** perm_v4qi_zip0_normal:
** ...
** wzip8p\s+a0,\s*a1,\s*a0
** mv\s+a0,\s*a1
** ...
*/
/*
** perm_v4qi_unzip0_normal:
** ...
** pnsrli\.b\s+a0,\s*[a-z0-9]+,\s*8
** ...
*/
/*
** perm_v8qi_reverse_same:
** ...
** rev8\s+.*
** rev8\s+.*
** ...
*/
