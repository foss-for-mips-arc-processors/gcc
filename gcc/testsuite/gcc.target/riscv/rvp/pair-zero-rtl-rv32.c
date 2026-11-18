/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

/* Exercise both partial overwrites after register allocation.  */
unsigned long long __RTL (startwith ("peephole2"))
zero_upper (unsigned int input)
{
(function "zero_upper"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:SI a5) (reg:SI a0)))
      (cinsn 4 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long long __RTL (startwith ("peephole2"))
zero_lower (unsigned int input)
{
(function "zero_lower"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:SI a4) (reg:SI a0)))
      (cinsn 4 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* A use of the overwritten half must not read its previous contents.  */
unsigned long long __RTL (startwith ("peephole2"))
zero_overlap (unsigned int input)
{
(function "zero_overlap"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4) (const_int 0)))
      (cinsn 3 (set (reg:SI a5) (reg:SI a5)))
      (cinsn 4 (set (reg:DI a0) (reg:DI a4)))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* The overlapping case retains a full pair clear.  */
/* { dg-final { scan-assembler-times {\taddd\t[^,]+,x0,x0} 1 } } */
/* { dg-final { scan-assembler-times {\tli\ta[45],0} 2 } } */
