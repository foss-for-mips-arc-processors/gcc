/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "clip-widths.h"
/* { dg-final { check-function-bodies "**" "" } } */

/* { dg-final { scan-assembler-times {\mpsati\.h\M[^\n]*,\s*1\s*\n} 2 } } */
/* { dg-final { scan-assembler-times {\mpsati\.h\M[^\n]*,\s*2\s*\n} 2 } } */
/* { dg-final { scan-assembler-times {\mpsati\.h\M[^\n]*,\s*8\s*\n} 2 } } */
/* { dg-final { scan-assembler {\mpsati\.h\M[^\n]*,\s*15\s*\n} } } */
/* { dg-final { scan-assembler-times {\mpsati\.h\M[^\n]*,\s*16\s*\n} 2 } } */
/* { dg-final { scan-assembler-times {\mpusati\.h\M[^\n]*,\s*1\s*\n} 2 } } */
/* { dg-final { scan-assembler-times {\mpusati\.h\M[^\n]*,\s*8\s*\n} 2 } } */
/* { dg-final { scan-assembler {\mpusati\.h\M[^\n]*,\s*14\s*\n} } } */
/* { dg-final { scan-assembler-times {\mpsati\.w\M[^\n]*,\s*1\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.w\M[^\n]*,\s*2\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.w\M[^\n]*,\s*8\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.w\M[^\n]*,\s*16\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.w\M[^\n]*,\s*31\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.w\M[^\n]*,\s*32\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.w\M[^\n]*,\s*1\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.w\M[^\n]*,\s*8\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.w\M[^\n]*,\s*30\s*\n} 1 } } */

/* { dg-final { scan-assembler-times {\mpminu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpminu\.w\M} 1 } } */

/* Asymmetric bounds must retain both min and max operations.  */
/*
** clip_h2_lower:
** ...
** pmin\.h\s+.*
** ...
** pmax\.h\s+.*
** ...
*/
/*
** clip_h2_upper:
** ...
** pmin\.h\s+.*
** ...
** pmax\.h\s+.*
** ...
*/
/*
** clip_h4_lower:
** ...
** pmin\.h\s+.*
** ...
** pmax\.h\s+.*
** ...
*/
/*
** clip_h4_upper:
** ...
** pmin\.h\s+.*
** ...
** pmax\.h\s+.*
** ...
*/
/*
** clip_w2_lower:
** ...
** pmin\.w\s+.*
** ...
** pmax\.w\s+.*
** ...
*/
/*
** clip_w2_upper:
** ...
** pmin\.w\s+.*
** ...
** pmax\.w\s+.*
** ...
*/

