/* { dg-do compile } */
/* { dg-options "-march=rv64gcbp0p21 -mabi=lp64d -O2" } */

/* Test PSH1ADD.H and PSH1ADD.W instruction generation.
   psh1add.h: rd[i] = (rs1[i] << 1) + rs2[i]  (16-bit elements)
   psh1add.w: rd[i] = (rs1[i] << 1) + rs2[i]  (32-bit elements, RV64)  */

typedef short          pv2hi  __attribute__((vector_size (4)));
typedef short          pv4hi  __attribute__((vector_size (8)));
typedef int            pv2si  __attribute__((vector_size (8)));
typedef unsigned short pv2uhi __attribute__((vector_size (4)));
typedef unsigned short pv4uhi __attribute__((vector_size (8)));
typedef unsigned int   pv2usi __attribute__((vector_size (8)));

/* --- psh1add.h: 16-bit elements, 2-element vector --- */

pv2hi test_psh1add_h_2(pv2hi a, pv2hi b) {
    return (a << 1) + b;
}

pv2uhi test_psh1add_h_2u(pv2uhi a, pv2uhi b) {
    return (a << 1) + b;
}

/* --- psh1add.h: 16-bit elements, 4-element vector (RV64) --- */

pv4hi test_psh1add_h_4(pv4hi a, pv4hi b) {
    return (a << 1) + b;
}

pv4uhi test_psh1add_h_4u(pv4uhi a, pv4uhi b) {
    return (a << 1) + b;
}

/* --- psh1add.w: 32-bit elements, 2-element vector (RV64) --- */

pv2si test_psh1add_w(pv2si a, pv2si b) {
    return (a << 1) + b;
}

pv2usi test_psh1add_wu(pv2usi a, pv2usi b) {
    return (a << 1) + b;
}

/* { dg-final { scan-assembler-times {psh1add\.h} 4 } } */
/* { dg-final { scan-assembler-times {psh1add\.w} 2 } } */
