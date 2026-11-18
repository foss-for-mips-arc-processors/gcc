/* { dg-do run } */
/* { dg-options "-O2" } */

/* An unsigned subtraction followed by a signed view remains modulo even
   when signed overflow is undefined.  Every later signed operation for
   these inputs is representable.  */
#include "vect-abs-minus.h"
