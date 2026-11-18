/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

unsigned long __RTL (startwith ("peephole2"))
word_sign_same (unsigned long a, unsigned long b, unsigned long c)
{
(function "word_sign_same"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMU)))
      (cinsn 3 (set (reg:DI a0)
        (sign_extend:DI (reg:SI a0))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
word_sign_copy (unsigned long a, unsigned long b, unsigned long c)
{
(function "word_sign_copy"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMU)))
      (cinsn 3 (set (reg:DI a0)
        (sign_extend:DI (reg:SI a4))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
word_zero_same (unsigned long a, unsigned long b, unsigned long c)
{
(function "word_zero_same"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMU)))
      (cinsn 3 (set (reg:DI a0)
        (zero_extend:DI (reg:SI a0))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
word_zero_copy (unsigned long a, unsigned long b, unsigned long c)
{
(function "word_zero_copy"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMU)))
      (cinsn 3 (set (reg:DI a0)
        (zero_extend:DI (reg:SI a4))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
word_live (unsigned long a, unsigned long b, unsigned long c)
{
(function "word_live"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMU)))
      (cinsn 3 (set (reg:DI a0)
        (sign_extend:DI (reg:SI a4))))
      (cinsn 4 (set (mem:DI (reg:DI a2) [0 S8 A64]) (reg:DI a4)))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
word_unrelated (unsigned long a, unsigned long b, unsigned long c)
{
(function "word_unrelated"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMU)))
      (cinsn 3 (set (reg:DI a0)
        (sign_extend:DI (reg:SI a2))))
      (cinsn 4 (set (reg:DI a0) (plus:DI (reg:DI a0) (reg:DI a4))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
word_wrap_signed (unsigned long a, unsigned long b, unsigned long c)
{
(function "word_wrap_signed"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a2)
        (unspec:DI [(reg:DI a2) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 3 (set (reg:DI a0)
        (sign_extend:DI (reg:SI a2))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
word_wrap_unsigned (unsigned long a, unsigned long b, unsigned long c)
{
(function "word_wrap_unsigned"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a2)
        (unspec:DI [(reg:DI a2) (reg:DI a0) (reg:DI a1)]
          UNSPEC_PABDSUMAU)))
      (cinsn 3 (set (reg:DI a0)
        (zero_extend:DI (reg:SI a2))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/*
** word_sign_same:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/
/*
** word_sign_copy:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/
/*
** word_zero_same:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/
/*
** word_zero_copy:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/

/* Keep the original result when it is stored after the extension.  */
/*
** word_live:
**  pabdsumu\.b\s+a4,a0,a1
**  sd\s+a4,0\(a2\)
**  mv\s+a0,a4
**  ret
*/

/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 6 } } */
/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 2 } } */
