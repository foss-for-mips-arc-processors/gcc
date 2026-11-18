/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
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
** ppaire\.b\s+a0,\s*a0,\s*a1
** ...
*/
/*
** perm_v4hi_pair00_normal:
** ...
** ppaire\.h\s+a0,\s*a0,\s*a1
** ...
*/
/*
** perm_v2si_pair00_normal:
** ...
** pack\s+a0,\s*a0,\s*a1
** ...
*/
/*
** perm_v8qi_pair01_swapped:
** ...
** ppaireo\.b\s+a0,\s*a1,\s*a0
** ...
*/
/*
** perm_v4qi_zip0_normal:
** ...
** zip8p\s+a0,\s*a0,\s*a1
** ...
*/
/*
** perm_v4qi_unzip0_normal:
** ...
** pack\s+a0,\s*a0,\s*a1
** unzip8p\s+a0,\s*a0,\s*(zero|x0)
** ...
*/
/*
** perm_v8qi_reverse_same:
** ...
** rev8\s+a0,\s*a0
** ...
*/
