/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "widen-product-cost.h"

/*
** shared_ss_b:
**  ...
**  pmul\.h\.b01\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_uu_b:
**  ...
**  pmulu\.h\.b01\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_su_b:
**  ...
**  pmulsu\.h\.b00\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_us_b:
**  ...
**  pmulsu\.h\.b00\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_ss_h:
**  ...
**  pmacc\.w\.h01\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_uu_h:
**  ...
**  pmaccu\.w\.h01\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_su_h:
**  ...
**  pmaccsu\.w\.h00\s+[^\n]+
**  ...
**  ret
*/

/*
** shared_us_h:
**  ...
**  pmaccsu\.w\.h00\s+[^\n]+
**  ...
**  ret
*/

/* Full-width operands still need both scalar word products.  */
/*
** full_word:
**  ...
**  mulw\s+[^\n]+
**  mulw\s+[^\n]+
**  pack\s+[^\n]+
**  ret
*/
