/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-rtl-split1" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

/* The odd destination overlaps both inputs.  Its low word must not be
   written before the high word of the first input has been consumed.  */
unsigned long long __RTL (startwith ("split1"))
masked_right (unsigned long long a, unsigned long long b)
{
(function "masked_right"
  (param "a"
    (DECL_RTL (reg:DI <0>))
    (DECL_RTL_INCOMING (reg:DI a0)))
  (param "b"
    (DECL_RTL (reg:DI <1>))
    (DECL_RTL_INCOMING (reg:DI a2)))
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 10 (set (reg:DI <0>) (reg:DI a0)))
      (cinsn 11 (set (reg:DI <1>) (reg:DI a2)))
      (cnote 12 NOTE_INSN_FUNCTION_BEG)
      (cinsn 2 (set (reg:PV2SI a1)
        (mult:PV2SI
          (and:PV2SI (reg:PV2SI a0)
            (const_vector:PV2SI [(const_int 2047) (const_int -2048)]))
          (and:PV2SI (reg:PV2SI a2)
            (const_vector:PV2SI [(const_int 127) (const_int 15)])))))
      (cinsn 3 (set (reg:SI a0) (reg:SI a1)))
      (cinsn 4 (set (reg:SI a1) (reg:SI a2)))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long long __RTL (startwith ("split1"))
masked_left (unsigned long long a, unsigned long long b)
{
(function "masked_left"
  (param "a"
    (DECL_RTL (reg:DI <0>))
    (DECL_RTL_INCOMING (reg:DI a0)))
  (param "b"
    (DECL_RTL (reg:DI <1>))
    (DECL_RTL_INCOMING (reg:DI a2)))
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 10 (set (reg:DI <0>) (reg:DI a0)))
      (cinsn 11 (set (reg:DI <1>) (reg:DI a2)))
      (cnote 12 NOTE_INSN_FUNCTION_BEG)
      (cinsn 2 (set (reg:SI a4) (reg:SI a3)))
      (cinsn 3 (set (reg:SI a3) (reg:SI a2)))
      (cinsn 4 (set (reg:SI a2) (reg:SI a1)))
      (cinsn 5 (set (reg:SI a1) (reg:SI a0)))
      (cinsn 6 (set (reg:PV2SI a0)
        (mult:PV2SI
          (and:PV2SI (reg:PV2SI a1)
            (const_vector:PV2SI [(const_int 2047) (const_int -2048)]))
          (and:PV2SI (reg:PV2SI a3)
            (const_vector:PV2SI [(const_int 127) (const_int 15)])))))
      (cinsn 7 (use (reg:DI a0)))
      (cjump_insn 8 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long long __RTL (startwith ("split1"))
masked_same (unsigned long long a, unsigned long long b)
{
(function "masked_same"
  (param "a"
    (DECL_RTL (reg:DI <0>))
    (DECL_RTL_INCOMING (reg:DI a0)))
  (param "b"
    (DECL_RTL (reg:DI <1>))
    (DECL_RTL_INCOMING (reg:DI a2)))
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 10 (set (reg:DI <0>) (reg:DI a0)))
      (cinsn 11 (set (reg:DI <1>) (reg:DI a2)))
      (cnote 12 NOTE_INSN_FUNCTION_BEG)
      (cinsn 2 (set (reg:PV2SI a0)
        (mult:PV2SI
          (and:PV2SI (reg:PV2SI a0)
            (const_vector:PV2SI [(const_int 2047) (const_int -2048)]))
          (and:PV2SI (reg:PV2SI a2)
            (const_vector:PV2SI [(const_int 127) (const_int 15)])))))
      (cinsn 3 (use (reg:DI a0)))
      (cjump_insn 4 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* { dg-final { scan-rtl-dump-not {rvp_masked_mulpv2si3} "split1" } } */
/* { dg-final { scan-assembler-times {\mandi\M} 12 } } */
