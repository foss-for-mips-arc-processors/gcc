/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-rtl-peephole2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

/* The temporary can disappear when only the copied result is live.  */
unsigned long __RTL (startwith ("peephole2"))
zero_copy (unsigned long a, unsigned long b)
{
(function "zero_copy"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:DI a4)
        (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 4 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* Neither source may read the value that precedes the accumulator clear.  */
unsigned long __RTL (startwith ("peephole2"))
zero_left (unsigned long a, unsigned long b)
{
(function "zero_left"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0) (const_int 0)))
      (cinsn 3 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 4 (use (reg:DI a0)))
      (cjump_insn 5 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
zero_right (unsigned long a, unsigned long b)
{
(function "zero_right"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0) (const_int 0)))
      (cinsn 3 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1) (reg:DI a0)]
          UNSPEC_PABDSUMAU)))
      (cinsn 4 (use (reg:DI a0)))
      (cjump_insn 5 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* The copied result must not replace a temporary that is still needed.  */
unsigned long __RTL (startwith ("peephole2"))
zero_live (unsigned long a, unsigned long b, unsigned long *saved)
{
(function "zero_live"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:DI a4)
        (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 4 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 5 (set (mem:DI (reg:DI a2) [0 S8 A64]) (reg:DI a4)))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* A bitwise copy to an FPR cannot become a packed-integer destination.  */
double __RTL (startwith ("peephole2"))
zero_float (unsigned long a, unsigned long b)
{
(function "zero_float"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:DI a4)
        (unspec:DI [(reg:DI a4) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 4 (set (reg:DI fa0) (reg:DI a4)))
      (cinsn 5 (use (reg:DF fa0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DF fa0))))
}

/* The zero clear remains live when it supplies a packed input.  */
/* { dg-final { check-function-bodies "**" "" } } */
/*
** zero_left:
**  li\s+a0,0
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/
/*
** zero_right:
**  li\s+a0,0
**  pabdsumu\.b\s+a0,a1,a0
**  ret
*/
/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 5 } } */
/* { dg-final { scan-assembler-not {\tpabdsumau\.b\t} } } */
/* { dg-final { scan-assembler-not {\tpabdsumu\.b\tf} } } */
