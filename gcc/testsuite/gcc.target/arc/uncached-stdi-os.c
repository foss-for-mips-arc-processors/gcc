/* { dg-do compile } */
/* { dg-options "-Os -mno-ll64" } */

#include "uncached-stdi.h"

/* { dg-final { scan-assembler "stb.*\\.di" } } */
/* { dg-final { scan-assembler "\\m(sth|stw).*\\.di" } } */
/* { dg-final { scan-assembler "st.*\\.di" } } */

/* Second verify that no direct(di) register offset addressing are being generated. */
/* { dg-final { scan-assembler-not {stb.*\.di\s+r[0-9]+,\s*\[r[0-9]+,\s*r[0-9]+\]} } } */
/* { dg-final { scan-assembler-not {\m(sth|stw).*\.di\s+r[0-9]+,\s*\[r[0-9]+,\s*r[0-9]+\]} } } */
/* { dg-final { scan-assembler-not {st.*\.di\s+r[0-9]+,\s*\[r[0-9]+,\s*r[0-9]+\]} } } */
