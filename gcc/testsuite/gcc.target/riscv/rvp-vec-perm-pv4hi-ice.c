/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64d" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

/* This selector used to be matched as the byte-granularity rev16, which has no
   PV4HImode recognizer, and emitted an unrecognizable insn.  */

typedef short v4hi __attribute__ ((vector_size (8)));

v4hi
swap_words (v4hi a)
{
  return __builtin_shufflevector (a, a, 2, 3, 0, 1);
}

/* { dg-final { scan-assembler {\mppairoe\.w\M} } } */
