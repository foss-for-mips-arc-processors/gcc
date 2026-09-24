/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" } } */

typedef signed char pv8qi __attribute__((vector_size (8)));
typedef short pv4hi __attribute__((vector_size (8)));
typedef int pv2si __attribute__((vector_size (8)));

/* Test packed negation.  pneg.<b,h,w> rd, rs is an assembler alias for
   psub.<b,h,w> rd, x0, rs; the middle-end lowers the unary `-' on a
   packed vector via the neg<mode>2 standard pattern.  */

pv8qi
pneg_b (pv8qi a)
{
  return -a;
}

pv4hi
pneg_h (pv4hi a)
{
  return -a;
}

pv2si
pneg_w (pv2si a)
{
  return -a;
}

/* { dg-final { scan-assembler-times {\mpneg\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpneg\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpneg\.w\M} 1 } } */
