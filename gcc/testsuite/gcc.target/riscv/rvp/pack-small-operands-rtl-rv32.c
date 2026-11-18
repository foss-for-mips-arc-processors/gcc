/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -mlittle-endian -O2" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

/* The pack splitters accept subregs and hard registers as well as pseudos.
   In particular, an odd hard register cannot be widened to a register pair.  */

unsigned int __RTL (startwith ("split1"))
pack_subreg (unsigned int a, unsigned int b)
{
(function "pack_subreg"
  (param "a"
    (DECL_RTL (reg:SI <0>))
    (DECL_RTL_INCOMING (reg:SI a0)))
  (param "b"
    (DECL_RTL (reg:SI <1>))
    (DECL_RTL_INCOMING (reg:SI a1)))
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:SI <0>) (reg:SI a0)))
      (cinsn 3 (set (reg:SI <1>) (reg:SI a1)))
      (cnote 4 NOTE_INSN_FUNCTION_BEG)
      (cinsn 5 (set (reg:PV4QI <2>)
        (truncate:PV4QI
          (vec_concat:PV4HI
            (subreg:PV2HI (reg:SI <0>) 0)
            (subreg:PV2HI (reg:SI <1>) 0)))))
      (cinsn 6 (set (reg:SI a0) (subreg:SI (reg:PV4QI <2>) 0)))
      (cinsn 7 (use (reg:SI a0)))
      (edge-to exit (flags "FALLTHRU"))))
  (crtl (return_rtx (reg:SI a0))))
}

unsigned int __RTL (startwith ("split1"))
pack_hard (unsigned int a, unsigned int b)
{
(function "pack_hard"
  (param "a"
    (DECL_RTL (reg:SI <0>))
    (DECL_RTL_INCOMING (reg:SI a0)))
  (param "b"
    (DECL_RTL (reg:SI <1>))
    (DECL_RTL_INCOMING (reg:SI a1)))
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:SI <0>) (reg:SI a0)))
      (cinsn 3 (set (reg:SI <1>) (reg:SI a1)))
      (cnote 4 NOTE_INSN_FUNCTION_BEG)
      (cinsn 5 (set (reg:PV4QI <2>)
        (truncate:PV4QI
          (vec_concat:PV4HI
            (reg:PV2HI a1)
            (reg:PV2HI a0)))))
      (cinsn 6 (set (reg:SI a0) (subreg:SI (reg:PV4QI <2>) 0)))
      (cinsn 7 (use (reg:SI a0)))
      (edge-to exit (flags "FALLTHRU"))))
  (crtl (return_rtx (reg:SI a0))))
}

unsigned int __RTL (startwith ("split1"))
clip_subreg (unsigned int a, unsigned int b)
{
(function "clip_subreg"
  (param "a"
    (DECL_RTL (reg:SI <0>))
    (DECL_RTL_INCOMING (reg:SI a0)))
  (param "b"
    (DECL_RTL (reg:SI <1>))
    (DECL_RTL_INCOMING (reg:SI a1)))
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:SI <0>) (reg:SI a0)))
      (cinsn 3 (set (reg:SI <1>) (reg:SI a1)))
      (cnote 4 NOTE_INSN_FUNCTION_BEG)
      (cinsn 5 (set (reg:PV4QI <2>)
        (truncate:PV4QI
          (vec_concat:PV4HI
            (umin:PV2HI (subreg:PV2HI (reg:SI <0>) 0)
              (const_vector:PV2HI [(const_int 255) (const_int 255)]))
            (umin:PV2HI (subreg:PV2HI (reg:SI <1>) 0)
              (const_vector:PV2HI [(const_int 255) (const_int 255)]))))))
      (cinsn 6 (set (reg:SI a0) (subreg:SI (reg:PV4QI <2>) 0)))
      (cinsn 7 (use (reg:SI a0)))
      (edge-to exit (flags "FALLTHRU"))))
  (crtl (return_rtx (reg:SI a0))))
}

unsigned int __RTL (startwith ("split1"))
clip_hard (unsigned int a, unsigned int b)
{
(function "clip_hard"
  (param "a"
    (DECL_RTL (reg:SI <0>))
    (DECL_RTL_INCOMING (reg:SI a0)))
  (param "b"
    (DECL_RTL (reg:SI <1>))
    (DECL_RTL_INCOMING (reg:SI a1)))
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:SI <0>) (reg:SI a0)))
      (cinsn 3 (set (reg:SI <1>) (reg:SI a1)))
      (cnote 4 NOTE_INSN_FUNCTION_BEG)
      (cinsn 5 (set (reg:PV4QI <2>)
        (truncate:PV4QI
          (vec_concat:PV4HI
            (umin:PV2HI (reg:PV2HI a1)
              (const_vector:PV2HI [(const_int 255) (const_int 255)]))
            (umin:PV2HI (reg:PV2HI a0)
              (const_vector:PV2HI [(const_int 255) (const_int 255)]))))))
      (cinsn 6 (set (reg:SI a0) (subreg:SI (reg:PV4QI <2>) 0)))
      (cinsn 7 (use (reg:SI a0)))
      (edge-to exit (flags "FALLTHRU"))))
  (crtl (return_rtx (reg:SI a0))))
}

/* { dg-final { scan-assembler-times {\mpncvt\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpnclipiu\.b\M} 2 } } */
