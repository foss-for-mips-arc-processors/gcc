/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" } } */

typedef signed char pv8qi __attribute__((vector_size (8)));
typedef short pv4hi __attribute__((vector_size (8)));
typedef int pv2si __attribute__((vector_size (8)));

/* Test packed splat: broadcast a scalar to every lane of a packed
   vector.  The middle-end lowers the composite-literal constructor
   through the standard mov<mode> pattern, which selects pmv.bs/hs/ws
   (variable) or pli.b/h, plui.h (immediate) via riscv_output_move.  */

/* Variable splat.  */
pv8qi
pmv_s_b (signed char x)
{
  return (pv8qi){x, x, x, x, x, x, x, x};
}

pv4hi
pmv_s_h (short x)
{
  return (pv4hi){x, x, x, x};
}

pv2si
pmv_s_w (int x)
{
  return (pv2si){x, x};
}

/* Immediate splat.  */
pv8qi
pmv_s_b_imm (void)
{
  return (pv8qi){5, 5, 5, 5, 5, 5, 5, 5};
}

pv4hi
pmv_s_h_imm (void)
{
  return (pv4hi){300, 300, 300, 300};
}

pv4hi
pmv_s_h_imm_u (void)
{
  return (pv4hi){512, 512, 512, 512};
}

/* { dg-final { scan-assembler-times {\mpmv\.bs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmv\.hs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmv\.ws\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpli\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpli\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mplui\.h\M} 1 } } */
