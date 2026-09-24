/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1"} } */
/* { dg-require-effective-target rv64 } */

typedef unsigned short pv4hi __attribute__((vector_size(8)));
typedef unsigned char pv8qi __attribute__((vector_size(8)));
typedef unsigned int pv2si __attribute__((vector_size(8)));

unsigned long test_pair_e_w(unsigned long a, unsigned long b) {
    unsigned long a_lo = (unsigned int)a & 0xffffffff;
    unsigned long b_lo = (unsigned int)b & 0xffffffff;
    return ((a_lo) | (b_lo << 32));
}

unsigned long test_pair_oe_w(unsigned long a, unsigned long b) {
    return (a >> 32 | b << 32);
}


unsigned long test_pair_eo_w_1(unsigned long a, unsigned long b) {
    unsigned long a_lo = a & 0x00000000ffffffff;
    unsigned long b_hi = b & 0xffffffff00000000;
    return (a_lo | b_hi);
}

unsigned long test_pair_eo_w_2(unsigned long a, unsigned long b) {
    unsigned int a_lo = (unsigned int)a;
    unsigned long b_hi = b & 0xffffffff00000000;
    return (a_lo | b_hi);
}

unsigned long test_pair_o_w(unsigned long a, unsigned long b) {
    unsigned long a_hi = a & 0xffffffff00000000;
    unsigned long b_hi = b & 0xffffffff00000000;
    return ((unsigned long)a_hi >> 32) | (b_hi);
}

pv2si vec_pair_e_w(pv2si a, pv2si b) {
  pv2si rd;
  rd[0] = a[0];
  rd[1] = b[0];
  return rd;
}

pv2si vec_pair_eo_w(pv2si a, pv2si b) {
  pv2si rd;
  rd[0] = a[0];
  rd[1] = b[1];
  return rd;
}

pv2si vec_pair_oe_w(pv2si a, pv2si b) {
  pv2si rd;
  rd[0] = a[1];
  rd[1] = b[0];
  return rd;
}

pv2si vec_pair_o_w(pv2si a, pv2si b) {
  pv2si rd;
  rd[0] = a[1];
  rd[1] = b[1];
  return rd;
}

pv4hi vecshuffle_pair_e_h(pv4hi a, pv4hi b) {
    pv4hi rd = {a[0], b[0], a[2], b[2]};
    return rd;
}

pv4hi vecshuffle_pair_eo_h(pv4hi a, pv4hi b) {
    pv4hi rd = {a[0], b[1], a[2], b[3]};
    return rd;
}

pv4hi vecshuffle_pair_oe_h(pv4hi a, pv4hi b) {
    pv4hi rd = {a[1], b[0], a[3], b[2]};
    return rd;
}

pv4hi vecshuffle_pair_o_h(pv4hi a, pv4hi b) {
    pv4hi rd = {a[1], b[1], a[3], b[3]};
    return rd;
}

pv8qi vecshuffle_pair_e_b(pv8qi a, pv8qi b) {
    pv8qi rd = {a[0], b[0], a[2], b[2], a[4], b[4], a[6], b[6]};
    return rd;
}

pv8qi vecshuffle_pair_eo_b(pv8qi a, pv8qi b) {
    pv8qi rd = {a[0], b[1], a[2], b[3], a[4], b[5], a[6], b[7]};
    return rd;
}

pv8qi vecshuffle_pair_oe_b(pv8qi a, pv8qi b) {
    pv8qi rd = {a[1], b[0], a[3], b[2], a[5], b[4], a[7], b[6]};
    return rd;
}

pv8qi vecshuffle_pair_o_b(pv8qi a, pv8qi b) {
    pv8qi rd = {a[1], b[1], a[3], b[3], a[5], b[5], a[7], b[7]};
    return rd;
}

/* { dg-final { scan-assembler-times {\mpack\M} 2 } } */
/* { dg-final { scan-assembler-times {\mppaireo\.w\M} 3 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mppairo\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mppaire\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppaireo\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppairo\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppaire\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppaireo\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppairo\.b\M} 1 } } */
