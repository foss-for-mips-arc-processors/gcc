/* { dg-do compile } */
/* { dg-options "-mlsx -O2" } */

#include <lsxintrin.h>

extern __m128i bar (void);
extern int *p;

void
foo ()
{
  __lsx_vst (bar(), (void *)p, 0);
}
