/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32d -fdump-rtl-cprop1-details" } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */

/* The source changes after the copy.  An independent copied guard operand
   gives cprop work without adding a suffix use of the destination.  */

unsigned int __RTL (startwith ("cprop1"))
copy_source (unsigned int x, unsigned int limit, unsigned int n)
{
(function "copy_source"
  (param "x"
    (DECL_RTL (reg:SI <0>)) (DECL_RTL_INCOMING (reg:SI a0)))
  (param "limit"
    (DECL_RTL (reg:SI <1>)) (DECL_RTL_INCOMING (reg:SI a1)))
  (param "n"
    (DECL_RTL (reg:SI <2>)) (DECL_RTL_INCOMING (reg:SI a2)))
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:SI <0>) (reg:SI a0)))
      (cinsn 3 (set (reg:SI <1>) (reg:SI a1)))
      (cinsn 4 (set (reg:SI <2>) (reg:SI a2)))
      (cnote 5 NOTE_INSN_FUNCTION_BEG)
      (cjump_insn 64
        (set (pc) (if_then_else (eq (reg:SI <2>) (const_int 0))
                               (label_ref 70) (pc))))
      (edge-to 10 (flags "FALLTHRU"))
      (edge-to 11))
    (block 10
      (edge-from 2 (flags "FALLTHRU"))
      (cnote 65 [bb 10] NOTE_INSN_BASIC_BLOCK)
      (cinsn 7 (set (reg:SI <3>) (reg:SI <0>)))
      (cinsn 8 (set (reg:SI <6>) (reg:SI <1>)))
      (cinsn 9
        (set (reg:SI <0>) (plus:SI (reg:SI <0>) (const_int 9))))
      (cjump_insn 10
        (set (pc) (if_then_else (ltu (reg:SI <6>) (reg:SI <2>))
                               (label_ref 30) (pc))))
      (edge-to 3 (flags "FALLTHRU"))
      (edge-to 4))
    (block 3
      (edge-from 10 (flags "FALLTHRU"))
      (cnote 11 [bb 3] NOTE_INSN_BASIC_BLOCK)
      (cinsn 12 (set (reg:SI <5>) (reg:SI <2>)))
      (edge-to 5 (flags "FALLTHRU")))
    (block 5
      (edge-from 3 (flags "FALLTHRU"))
      (edge-from 5)
      (clabel 20 1)
      (cnote 21 [bb 5] NOTE_INSN_BASIC_BLOCK)
      (cinsn 23
        (set (reg:SI <3>) (plus:SI (reg:SI <3>) (const_int 1))))
      (cinsn 24
        (set (reg:SI <5>) (plus:SI (reg:SI <5>) (const_int -1))))
      (cjump_insn 25
        (set (pc) (if_then_else (ne (reg:SI <5>) (const_int 0))
                               (label_ref 20) (pc))))
      (edge-to 5)
      (edge-to 6 (flags "FALLTHRU")))
    (block 6
      (edge-from 5 (flags "FALLTHRU"))
      (cnote 26 [bb 6] NOTE_INSN_BASIC_BLOCK)
      (cinsn 27 (set (reg:SI <8>) (reg:SI <3>)))
      (edge-to 7 (flags "FALLTHRU")))
    (block 4
      (edge-from 10)
      (clabel 30 2)
      (cnote 31 [bb 4] NOTE_INSN_BASIC_BLOCK)
      (cinsn 32 (set (reg:SI <8>) (reg:SI <0>)))
      (edge-to 7 (flags "FALLTHRU")))
    (block 11
      (edge-from 2)
      (clabel 70 5)
      (cnote 71 [bb 11] NOTE_INSN_BASIC_BLOCK)
      (cinsn 72 (set (reg:SI <8>) (const_int 0)))
      (edge-to 7 (flags "FALLTHRU")))
    (block 7
      (edge-from 11 (flags "FALLTHRU"))
      (edge-from 4 (flags "FALLTHRU"))
      (edge-from 6 (flags "FALLTHRU"))
      (clabel 50 4)
      (cnote 51 [bb 7] NOTE_INSN_BASIC_BLOCK)
      (cinsn 52 (set (reg/i:SI a0) (reg:SI <8>)))
      (cinsn 53 (use (reg/i:SI a0)))
      (edge-to exit (flags "FALLTHRU"))))
  (crtl (return_rtx (reg/i:SI a0))))
}

/* { dg-final { scan-rtl-dump-not "Sinking copy insn 7 " "cprop1" } } */

