/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-rtl-peephole2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

/* A nonadjacent clear can be removed without moving either load.  */
unsigned long __RTL (startwith ("peephole2"))
gap_one (unsigned long a, unsigned long b, const unsigned long *p)
{
(function "gap_one"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:DI a5) (mem:DI (reg:DI a2) [0 S8 A64])))
      (cinsn 4 (set (reg:DI a4) (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 5 (set (reg:DI a0) (plus:DI (reg:DI a4) (reg:DI a5))))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
gap_two (unsigned long a, unsigned long b,
         const unsigned long *p, const unsigned long *q)
{
(function "gap_two"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:DI a5) (mem:DI (reg:DI a2) [0 S8 A64])))
      (cinsn 4 (set (reg:DI a6) (mem:DI (reg:DI a3) [0 S8 A64])))
      (cinsn 5 (set (reg:DI a4) (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 6 (set (reg:DI a0) (plus:DI (reg:DI a4) (reg:DI a5))))
      (cinsn 7 (set (reg:DI a0) (plus:DI (reg:DI a0) (reg:DI a6))))
      (cinsn 8 (use (reg:DI a0)))
      (cjump_insn 9 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* An intervening use must retain the zero value even if the clear dies.  */
unsigned long __RTL (startwith ("peephole2"))
gap_shared (unsigned long a, unsigned long b, unsigned long *p)
{
(function "gap_shared"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (mem:DI (reg:DI a2) [0 S8 A64]) (reg:DI a4)))
      (cinsn 4 (set (reg:DI a4) (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 5 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* The most recent definition, not an earlier zero, determines the value.  */
unsigned long __RTL (startwith ("peephole2"))
gap_overwrite (unsigned long a, unsigned long b, unsigned long seed)
{
(function "gap_overwrite"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:DI a4) (reg:DI a2)))
      (cinsn 4 (set (reg:DI a4) (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 5 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* Partial definitions and clobbers do not prove a native-width zero.
   These two functions are compile-only controls.  */
unsigned long __RTL (startwith ("peephole2"))
gap_partial (unsigned long a, unsigned long b, unsigned long seed)
{
(function "gap_partial"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:HI a4) (reg:HI a2)))
      (cinsn 4 (set (reg:DI a4) (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 5 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
gap_clobber (unsigned long a, unsigned long b)
{
(function "gap_clobber"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (clobber (reg:HI a4)))
      (cinsn 4 (set (reg:DI a4) (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 5 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* Do not search past opaque assembly.  */
unsigned long __RTL (startwith ("peephole2"))
gap_barrier (unsigned long a, unsigned long b)
{
(function "gap_barrier"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (asm_input/v ("") 0))
      (cinsn 4 (set (reg:DI a4) (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 5 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* A lexical zero definition in a predecessor is not a reaching-value proof.  */
unsigned long __RTL (startwith ("peephole2"))
gap_merge (unsigned long a, unsigned long b, unsigned long choose,
           unsigned long seed)
{
(function "gap_merge"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cjump_insn 2 (set (pc)
        (if_then_else (eq (reg:DI a2) (const_int 0))
          (label_ref 6) (pc))))
      (edge-to 3 (flags "FALLTHRU"))
      (edge-to 4))
    (block 3
      (edge-from 2 (flags "FALLTHRU"))
      (cnote 3 [bb 3] NOTE_INSN_BASIC_BLOCK)
      (cinsn 4 (set (reg:DI a4) (reg:DI a3)))
      (cjump_insn 5 (set (pc) (label_ref 9)))
      (edge-to 5))
    (cbarrier 14)
    (block 4
      (edge-from 2)
      (clabel 6 1)
      (cnote 7 [bb 4] NOTE_INSN_BASIC_BLOCK)
      (cinsn 8 (set (reg:DI a4) (const_int 0)))
      (edge-to 5 (flags "FALLTHRU")))
    (block 5
      (edge-from 3)
      (edge-from 4 (flags "FALLTHRU"))
      (clabel 9 2)
      (cnote 10 [bb 5] NOTE_INSN_BASIC_BLOCK)
      (cinsn 11 (set (reg:DI a4) (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 12 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 13 (use (reg:DI a0)))
      (cjump_insn 15 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

void __attribute__ ((noipa))
gap_callee (void)
{
  __asm__ volatile ("");
}

/* Even an ABI-preserved accumulator is not tracked across a call.  */
unsigned long __RTL (startwith ("peephole2"))
gap_call (unsigned long a, unsigned long b)
{
(function "gap_call"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI sp) (plus:DI (reg:DI sp) (const_int -32))))
      (cinsn 3 (set (mem:DI (reg:DI sp) [0 S8 A64]) (reg:DI ra)))
      (cinsn 4 (set (mem:DI (plus:DI (reg:DI sp) (const_int 8)) [0 S8 A64]) (reg:DI s0)))
      (cinsn 5 (set (mem:DI (plus:DI (reg:DI sp) (const_int 16)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 6 (set (mem:DI (plus:DI (reg:DI sp) (const_int 24)) [0 S8 A64]) (reg:DI a1)))
      (cinsn 7 (set (reg:DI s0) (const_int 0)))
      (ccall_insn 8 (parallel [(call (mem:SI (symbol_ref:DI ("gap_callee") [flags 0x3]) [0 S4 A32]) (const_int 0))
        (use (unspec:SI [(const_int 0)] UNSPEC_CALLEE_CC))
        (clobber (reg:SI ra))]))
      (cinsn 9 (set (reg:DI a0) (mem:DI (plus:DI (reg:DI sp) (const_int 16)) [0 S8 A64])))
      (cinsn 10 (set (reg:DI a1) (mem:DI (plus:DI (reg:DI sp) (const_int 24)) [0 S8 A64])))
      (cinsn 11 (set (reg:DI s0) (unspec:DI [(reg:DI s0) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 12 (set (reg:DI a0) (reg:DI s0)))
      (cinsn 13 (set (reg:DI ra) (mem:DI (reg:DI sp) [0 S8 A64])))
      (cinsn 14 (set (reg:DI s0) (mem:DI (plus:DI (reg:DI sp) (const_int 8)) [0 S8 A64])))
      (cinsn 15 (set (reg:DI sp) (plus:DI (reg:DI sp) (const_int 32))))
      (cinsn 16 (use (reg:DI a0)))
      (cjump_insn 17 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* { dg-final { check-function-bodies "**" "" } } */
/*
** gap_one:
**  ld\s+a5,0\(a2\)
**  pabdsumu\.b\s+a4,a0,a1
**  add\s+a0,a4,a5
**  ret
*/
/*
** gap_two:
**  ld\s+a5,0\(a2\)
**  ld\s+a6,0\(a3\)
**  pabdsumu\.b\s+a4,a0,a1
**  add\s+a0,a4,a5
**  add\s+a0,a0,a6
**  ret
*/
/*
** gap_shared:
**  li\s+a4,0
**  sd\s+a4,0\(a2\)
**  pabdsumu\.b\s+a4,a0,a1
**  mv\s+a0,a4
**  ret
*/
/*
** gap_overwrite:
**  ...
**  pabdsumau\.b\s+a4,a0,a1
**  ...
*/
/*
** gap_partial:
**  ...
**  pabdsumau\.b\s+a4,a0,a1
**  ...
*/
/*
** gap_clobber:
**  ...
**  pabdsumau\.b\s+a4,a0,a1
**  ...
*/
/*
** gap_barrier:
**  ...
**  pabdsumau\.b\s+a4,a0,a1
**  ...
*/
/*
** gap_merge:
**  ...
**  pabdsumau\.b\s+a4,a0,a1
**  ...
*/
/*
** gap_call:
**  ...
**  pabdsumau\.b\s+s0,a0,a1
**  ...
*/
/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 6 } } */

