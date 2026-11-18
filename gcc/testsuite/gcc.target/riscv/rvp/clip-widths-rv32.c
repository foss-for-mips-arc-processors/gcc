/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "clip-widths.h"
/* { dg-final { check-function-bodies "**" "" } } */

/* { dg-final { scan-assembler-times {\mpsati\.h\M[^\n]*,\s*1\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.h\M[^\n]*,\s*2\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.h\M[^\n]*,\s*8\s*\n} 1 } } */
/* { dg-final { scan-assembler {\mpsati\.h\M[^\n]*,\s*15\s*\n} } } */
/* { dg-final { scan-assembler-times {\mpsati\.h\M[^\n]*,\s*16\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.h\M[^\n]*,\s*1\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.h\M[^\n]*,\s*8\s*\n} 1 } } */
/* { dg-final { scan-assembler {\mpusati\.h\M[^\n]*,\s*14\s*\n} } } */
/* { dg-final { scan-assembler-times {\mpsati\.dh\M[^\n]*,\s*1\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dh\M[^\n]*,\s*2\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dh\M[^\n]*,\s*8\s*\n} 1 } } */
/* { dg-final { scan-assembler {\mpsati\.dh\M[^\n]*,\s*15\s*\n} } } */
/* { dg-final { scan-assembler-times {\mpsati\.dh\M[^\n]*,\s*16\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.dh\M[^\n]*,\s*1\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.dh\M[^\n]*,\s*8\s*\n} 1 } } */
/* { dg-final { scan-assembler {\mpusati\.dh\M[^\n]*,\s*14\s*\n} } } */
/* { dg-final { scan-assembler-times {\mpsati\.dw\M[^\n]*,\s*1\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dw\M[^\n]*,\s*2\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dw\M[^\n]*,\s*8\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dw\M[^\n]*,\s*16\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dw\M[^\n]*,\s*31\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dw\M[^\n]*,\s*32\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.dw\M[^\n]*,\s*1\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.dw\M[^\n]*,\s*8\s*\n} 1 } } */
/* { dg-final { scan-assembler-times {\mpusati\.dw\M[^\n]*,\s*30\s*\n} 1 } } */

/* { dg-final { scan-assembler-times {\mpminu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpminu\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpminu\.dw\M} 1 } } */

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
** pmin\.dh\s+.*
** ...
** pmax\.dh\s+.*
** ...
*/
/*
** clip_h4_upper:
** ...
** pmin\.dh\s+.*
** ...
** pmax\.dh\s+.*
** ...
*/
/*
** clip_w2_lower:
** ...
** pmin\.dw\s+.*
** ...
** pmax\.dw\s+.*
** ...
*/
/*
** clip_w2_upper:
** ...
** pmin\.dw\s+.*
** ...
** pmax\.dw\s+.*
** ...
*/

