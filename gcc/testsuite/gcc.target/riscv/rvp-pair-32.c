/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1"} } */
/* { dg-require-effective-target rv32 } */

typedef unsigned short pv2hi __attribute__((vector_size(4)));
typedef unsigned char pv4qi __attribute__((vector_size(4)));

unsigned int test_pair_e_h(unsigned int a, unsigned int b) {
    unsigned short a_lo = (unsigned short)a & 0xffff;
    unsigned short b_lo = (unsigned short)b & 0xffff;
    return (unsigned int)a_lo | (unsigned int)(b_lo << 16);
}

unsigned int test_pair_oe_h(unsigned int a, unsigned int b) {
    return (unsigned int)((a >> 16) | (b << 16));
}


unsigned int test_pair_eo_h_1(unsigned int a, unsigned int b) {
    unsigned int a_lo = a & 0x0000ffff;
    unsigned int b_hi = b & 0xffff0000;
    return (b_hi | a_lo);
}

unsigned int test_pair_eo_h_2(unsigned int a, unsigned int b) {
    unsigned short a_lo = (unsigned short)a;
    unsigned int b_hi = b & 0xffff0000;
    return (a_lo | b_hi);
}

unsigned int test_pair_o_h(unsigned int a, unsigned int b) {
    return ((b & 0xffff0000) | (a >> 16));
}

pv2hi vec_pair_e_h(pv2hi a, pv2hi b) { 
    pv2hi rd;
    rd[0] = a[0];
    rd[1] = b[0];    
    return rd;
}

pv2hi vec_pair_eo_h(pv2hi a, pv2hi b) { 
    pv2hi rd;
    rd[0] = a[0];
    rd[1] = b[1];    
    return rd;
}

pv2hi vec_pair_oe_h(pv2hi a, pv2hi b) { 
    pv2hi rd;
    rd[0] = a[1];
    rd[1] = b[0];    
    return rd;
}

pv2hi vec_pair_o_h(pv2hi a, pv2hi b) {
    pv2hi rd;
    rd[0] = a[1];
    rd[1] = b[1];
    return rd;
}

pv4qi vecshuffle_pair_e_b(pv4qi a, pv4qi b) {
    pv4qi rd = {a[0], b[0], a[2], b[2]};
    return rd;
}

pv4qi vecshuffle_pair_eo_b(pv4qi a, pv4qi b) {
    pv4qi rd = {a[0], b[1], a[2], b[3]};
    return rd;
}

pv4qi vecshuffle_pair_oe_b(pv4qi a, pv4qi b) {
    pv4qi rd = {a[1], b[0], a[3], b[2]};
    return rd;
}

pv4qi vecshuffle_pair_o_b(pv4qi a, pv4qi b) {
    pv4qi rd = {a[1], b[1], a[3], b[3]};
    return rd;
}

/* { dg-final { scan-assembler-times {\mpack\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppaire\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppaireo\.h\M} 3 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mppairo\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mppaire\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppaireo\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppairo\.b\M} 1 } } */
