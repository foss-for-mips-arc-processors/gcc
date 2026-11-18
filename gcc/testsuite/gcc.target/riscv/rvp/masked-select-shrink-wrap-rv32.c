/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fshrink-wrap -fomit-frame-pointer" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "masked-select-loop.h"

/* Sinking the parameter moves frees a4 for the zero-trip test.  Propagate
   that copy before deciding whether the s0 save needs to precede the test.  */
/*
** select_loop_8:
** beq\ta4,zero,.*
** ...
*/
/*
** select_loop_inv_8:
** beq\ta4,zero,.*
** ...
*/
/*
** select_loop_commuted_8:
** beq\ta4,zero,.*
** ...
*/
