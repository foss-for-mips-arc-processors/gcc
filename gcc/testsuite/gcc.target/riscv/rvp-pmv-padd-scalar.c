/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64d" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test PMV.xS (vec_duplicate) and PADD.xS (scalar-add) codegen on RV64.
   PMV.xS broadcasts the low element of a register to every lane.
   PADD.xS adds a vector with a broadcast scalar in a single instruction.  */

typedef signed char pv4qi __attribute__((vector_size(4)));
typedef short       pv2hi __attribute__((vector_size(4)));
typedef signed char pv8qi __attribute__((vector_size(8)));
typedef short       pv4hi __attribute__((vector_size(8)));
typedef int         pv2si __attribute__((vector_size(8)));

/* PMV.BS: broadcast byte scalar to 4-byte vector.  */
pv4qi splat_b4 (signed char x) { return (pv4qi){x, x, x, x}; }

/* PMV.HS: broadcast halfword scalar to 4-byte vector.  */
pv2hi splat_h2 (short x) { return (pv2hi){x, x}; }

/* PMV.BS: broadcast byte scalar to 8-byte vector.  */
pv8qi splat_b8 (signed char x) { return (pv8qi){x, x, x, x, x, x, x, x}; }

/* PMV.HS: broadcast halfword scalar to 8-byte vector.  */
pv4hi splat_h4 (short x) { return (pv4hi){x, x, x, x}; }

/* PMV.WS: broadcast word scalar to 8-byte vector.  */
pv2si splat_w2 (int x) { return (pv2si){x, x}; }

/* PADD.BS: vector + broadcast-scalar (4-byte).  */
pv4qi add_bs4 (pv4qi a, signed char b) { return a + (pv4qi){b, b, b, b}; }

/* PADD.BS: commuted (scalar first).  */
pv4qi add_bs4_rev (pv4qi a, signed char b) { return (pv4qi){b, b, b, b} + a; }

/* PADD.HS: vector + broadcast-scalar (4-byte).  */
pv2hi add_hs2 (pv2hi a, short b) { return a + (pv2hi){b, b}; }

/* PADD.HS: commuted.  */
pv2hi add_hs2_rev (pv2hi a, short b) { return (pv2hi){b, b} + a; }

/* PADD.BS: vector + broadcast-scalar (8-byte).  */
pv8qi add_bs8 (pv8qi a, signed char b) { return a + (pv8qi){b, b, b, b, b, b, b, b}; }

/* PADD.BS: commuted.  */
pv8qi add_bs8_rev (pv8qi a, signed char b) { return (pv8qi){b, b, b, b, b, b, b, b} + a; }

/* PADD.HS: vector + broadcast-scalar (8-byte).  */
pv4hi add_hs4 (pv4hi a, short b) { return a + (pv4hi){b, b, b, b}; }

/* PADD.HS: commuted.  */
pv4hi add_hs4_rev (pv4hi a, short b) { return (pv4hi){b, b, b, b} + a; }

/* PADD.WS: vector + broadcast-scalar (8-byte).  */
pv2si add_ws2 (pv2si a, int b) { return a + (pv2si){b, b}; }

/* PADD.WS: commuted.  */
pv2si add_ws2_rev (pv2si a, int b) { return (pv2si){b, b} + a; }

/* { dg-final { scan-assembler-times {\mpmv\.bs\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmv\.hs\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmv\.ws\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpadd\.bs\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpadd\.hs\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpadd\.ws\M} 2 } } */
