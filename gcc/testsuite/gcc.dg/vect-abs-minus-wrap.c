/* { dg-do run } */
/* { dg-options "-O2 -fwrapv" } */

/* ABS of a wrapping signed difference is not signed MAX minus MIN.  */
#define WRAPPING_SIGNED_SUBTRACTION
#include "vect-abs-minus.h"
