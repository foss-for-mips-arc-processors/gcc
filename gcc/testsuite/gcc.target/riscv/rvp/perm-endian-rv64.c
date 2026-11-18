/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mbig-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

/* Include the original interleaved halfword loop that failed in recog.  */
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
** ppairo\.b\s+a0,\s*a1,\s*a0
** ...
*/
/*
** perm_v4hi_pair00_normal:
** ...
** ppairo\.h\s+a0,\s*a1,\s*a0
** ...
*/
/*
** perm_v2si_pair00_normal:
** ...
** ppairo\.w\s+a0,\s*a1,\s*a0
** ...
*/
/*
** perm_v8qi_pair01_swapped:
** ...
** ppaireo\.b\s+a0,\s*a0,\s*a1
** ...
*/
/*
** perm_v4qi_zip0_normal:
** ...
** zip8p\s+a0,\s*a1,\s*a0
** (srai|srli)\s+a0,\s*a0,\s*32
** ...
*/
/*
** perm_v4qi_unzip0_normal:
** ...
** pack\s+a0,\s*a1,\s*a0
** unzip8hp\s+a0,\s*a0,\s*(zero|x0)
** ...
*/
/*
** perm_v8qi_reverse_same:
** ...
** rev8\s+a0,\s*a0
** ...
*/
