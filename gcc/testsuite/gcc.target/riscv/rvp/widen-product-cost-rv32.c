/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "widen-product-cost.h"

/*
** shared_ss_b:
**  ...
**  pwmul\.b\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_uu_b:
**  ...
**  pwmulu\.b\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_su_b:
**  ...
**  pwmulsu\.b\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_us_b:
**  ...
**  pwmulsu\.b\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_ss_h:
**  ...
**  pwmacc\.h\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_uu_h:
**  ...
**  pwmaccu\.h\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_su_h:
**  ...
**  pwmaccsu\.h\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_us_h:
**  ...
**  pwmaccsu\.h\s+[^\n]+
**  ...
**  ret
*/

/* Full-width operands are not truncated to halfwords.  */
/*
** full_word:
**  mul\s+[^\n]+
**  mul\s+[^\n]+
**  ret
*/
