/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test PMV.xS/PMV.DxS (vec_duplicate) and PADD.xS/PADD.DxS (scalar-add)
   codegen on RV32.  4-byte modes use PMV.BS/HS and PADD.BS/HS; 8-byte modes
   use the register-pair variants PMV.DBS/DHS/DWS and PADD.DBS/DHS/DWS.  */

typedef signed char pv4qi __attribute__((vector_size(4)));
typedef short       pv2hi __attribute__((vector_size(4)));
typedef signed char pv8qi __attribute__((vector_size(8)));
typedef short       pv4hi __attribute__((vector_size(8)));
typedef int         pv2si __attribute__((vector_size(8)));

/* PMV.BS: broadcast byte scalar to 4-byte vector (single register).  */
pv4qi splat_b4 (signed char x) { return (pv4qi){x, x, x, x}; }

/* PMV.HS: broadcast halfword scalar to 4-byte vector (single register).  */
pv2hi splat_h2 (short x) { return (pv2hi){x, x}; }

/* PMV.DBS: broadcast byte scalar to 8-byte register pair.  */
pv8qi splat_b8 (signed char x) { return (pv8qi){x, x, x, x, x, x, x, x}; }

/* PMV.DHS: broadcast halfword scalar to 8-byte register pair.  */
pv4hi splat_h4 (short x) { return (pv4hi){x, x, x, x}; }

/* PMV.DWS: broadcast word scalar to 8-byte register pair.  */
pv2si splat_w2 (int x) { return (pv2si){x, x}; }

/* PADD.BS: vector + broadcast-scalar (4-byte).  */
pv4qi add_bs4 (pv4qi a, signed char b) { return a + (pv4qi){b, b, b, b}; }

/* PADD.BS: commuted (scalar first).  */
pv4qi add_bs4_rev (pv4qi a, signed char b) { return (pv4qi){b, b, b, b} + a; }

/* PADD.HS: vector + broadcast-scalar (4-byte).  */
pv2hi add_hs2 (pv2hi a, short b) { return a + (pv2hi){b, b}; }

/* PADD.HS: commuted.  */
pv2hi add_hs2_rev (pv2hi a, short b) { return (pv2hi){b, b} + a; }

/* PADD.DBS: 8-byte register-pair + broadcast-scalar.  */
pv8qi add_dbs8 (pv8qi a, signed char b) { return a + (pv8qi){b, b, b, b, b, b, b, b}; }

/* PADD.DBS: commuted.  */
pv8qi add_dbs8_rev (pv8qi a, signed char b) { return (pv8qi){b, b, b, b, b, b, b, b} + a; }

/* PADD.DHS: 8-byte register-pair + broadcast-scalar.  */
pv4hi add_dhs4 (pv4hi a, short b) { return a + (pv4hi){b, b, b, b}; }

/* PADD.DHS: commuted.  */
pv4hi add_dhs4_rev (pv4hi a, short b) { return (pv4hi){b, b, b, b} + a; }

/* PADD.DWS: 8-byte register-pair + broadcast-scalar.  */
pv2si add_dws2 (pv2si a, int b) { return a + (pv2si){b, b}; }

/* PADD.DWS: commuted.  */
pv2si add_dws2_rev (pv2si a, int b) { return (pv2si){b, b} + a; }

/* { dg-final { scan-assembler-times {\mpmv\.bs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmv\.hs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmv\.dbs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmv\.dhs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmv\.dws\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpadd\.bs\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpadd\.hs\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpadd\.dbs\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpadd\.dhs\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpadd\.dws\M} 2 } } */
