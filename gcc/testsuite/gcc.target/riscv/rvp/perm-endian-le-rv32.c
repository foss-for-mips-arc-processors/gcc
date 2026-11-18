/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

/* Keep the existing little-endian permutation lowering covered.  */
#include "perm-endian.h"

/*
** perm_v4qi_pair00_normal:
** ...
** ppaire\.b\s+a0,\s*a0,\s*a1
** ...
*/
/*
** perm_v2hi_pair00_normal:
** ...
** ppaire\.h\s+a0,\s*a0,\s*a1
** ...
*/
/*
** perm_v8qi_pair00_normal:
** ...
** ppaire\.db\s+a0,\s*a0,\s*a2
** ...
*/
/*
** perm_v4hi_pair00_normal:
** ...
** ppaire\.dh\s+a0,\s*a0,\s*a2
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
** ppaireo\.db\s+a0,\s*a2,\s*a0
** ...
*/
/*
** perm_v4qi_zip0_normal:
** ...
** wzip8p\s+a0,\s*a0,\s*a1
** ...
*/
/*
** perm_v4qi_unzip0_normal:
** ...
** pncvt\.b\s+a0,\s*[a-z0-9]+
** ...
*/
/*
** perm_v8qi_reverse_same:
** ...
** rev8\s+.*
** rev8\s+.*
** ...
*/
