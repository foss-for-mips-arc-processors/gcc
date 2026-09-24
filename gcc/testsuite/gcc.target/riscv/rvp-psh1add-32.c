/* { dg-do compile } */
/* { dg-options "-march=rv32gcbp0p21 -mabi=ilp32 -O2" } */
/* { dg-require-effective-target rv32 } */

/* Test PSH1ADD.H, PSH1ADD.DH, and PSH1ADD.DW instruction generation on RV32.
   psh1add.h:  rd[i] = (rs1[i] << 1) + rs2[i]  (16-bit, PV2HI, single register)
   psh1add.dh: rd[i] = (rs1[i] << 1) + rs2[i]  (16-bit, PV4HI, register pair)
   psh1add.dw: rd[i] = (rs1[i] << 1) + rs2[i]  (32-bit, PV2SI, register pair)  */

typedef short          pv2hi  __attribute__((vector_size (4)));
typedef unsigned short pv2uhi __attribute__((vector_size (4)));
typedef short          pv4hi  __attribute__((vector_size (8)));
typedef unsigned short pv4uhi __attribute__((vector_size (8)));
typedef int            pv2si  __attribute__((vector_size (8)));
typedef unsigned int   pv2usi __attribute__((vector_size (8)));

/* --- psh1add.h: 16-bit elements, 2-element vector (single register) --- */

pv2hi test_psh1add_h_2(pv2hi a, pv2hi b) {
    return (a << 1) + b;
}

pv2uhi test_psh1add_h_2u(pv2uhi a, pv2uhi b) {
    return (a << 1) + b;
}

/* --- psh1add.dh: 16-bit elements, 4-element vector (register pair) --- */

pv4hi test_psh1add_dh(pv4hi a, pv4hi b) {
    return (a << 1) + b;
}

pv4uhi test_psh1add_dhu(pv4uhi a, pv4uhi b) {
    return (a << 1) + b;
}

/* --- psh1add.dw: 32-bit elements, 2-element vector (register pair) --- */

pv2si test_psh1add_dw(pv2si a, pv2si b) {
    return (a << 1) + b;
}

pv2usi test_psh1add_dwu(pv2usi a, pv2usi b) {
    return (a << 1) + b;
}

/* { dg-final { scan-assembler-times {psh1add\.h} 2 } } */
/* { dg-final { scan-assembler-times {psh1add\.dh} 2 } } */
/* { dg-final { scan-assembler-times {psh1add\.dw} 2 } } */
