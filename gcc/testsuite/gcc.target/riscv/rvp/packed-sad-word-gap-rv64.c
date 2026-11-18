/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-rtl-peephole2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

/* Intervening stores and loads must not be removed or moved.  */
unsigned long __RTL (startwith ("peephole2"))
sad_gap_sign (unsigned long a, unsigned long b, unsigned long c,
              unsigned long d)
{
(function "sad_gap_sign"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (mem:DI (reg:DI a2) [0 S8 A64]) (reg:DI a0)))
      (cinsn 4 (set (reg:DI a0) (sign_extend:DI (reg:SI a0))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
sad_gap_zero (unsigned long a, unsigned long b, unsigned long c,
              unsigned long d)
{
(function "sad_gap_zero"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (mem:DI (reg:DI a2) [0 S8 A64]) (reg:DI a0)))
      (cinsn 4 (set (reg:DI a0) (zero_extend:DI (reg:SI a0))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
sad_gap_copy (unsigned long a, unsigned long b, unsigned long c,
              unsigned long d)
{
(function "sad_gap_copy"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (mem:DI (reg:DI a2) [0 S8 A64]) (reg:DI a4)))
      (cinsn 4 (set (reg:DI a0) (sign_extend:DI (reg:SI a4))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
sad_gap_load (unsigned long a, unsigned long b, unsigned long c,
              unsigned long d)
{
(function "sad_gap_load"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (reg:DI a5) (mem:DI (reg:DI a2) [0 S8 A64])))
      (cinsn 4 (set (reg:DI a0) (sign_extend:DI (reg:SI a0))))
      (cinsn 5 (set (reg:DI a0) (plus:DI (reg:DI a0) (reg:DI a5))))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* The search accepts sixteen nondebug instructions, including the SAD.  */
unsigned long __RTL (startwith ("peephole2"))
sad_gap_limit (unsigned long a, unsigned long b, unsigned long c,
               unsigned long d)
{
(function "sad_gap_limit"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (mem:DI (reg:DI a2) [0 S8 A64]) (reg:DI a0)))
      (cinsn 4 (set (mem:DI (plus:DI (reg:DI a2) (const_int 8)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 5 (set (mem:DI (plus:DI (reg:DI a2) (const_int 16)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 6 (set (mem:DI (plus:DI (reg:DI a2) (const_int 24)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 7 (set (mem:DI (plus:DI (reg:DI a2) (const_int 32)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 8 (set (mem:DI (plus:DI (reg:DI a2) (const_int 40)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 9 (set (mem:DI (plus:DI (reg:DI a2) (const_int 48)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 10 (set (mem:DI (plus:DI (reg:DI a2) (const_int 56)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 11 (set (mem:DI (plus:DI (reg:DI a2) (const_int 64)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 12 (set (mem:DI (plus:DI (reg:DI a2) (const_int 72)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 13 (set (mem:DI (plus:DI (reg:DI a2) (const_int 80)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 14 (set (mem:DI (plus:DI (reg:DI a2) (const_int 88)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 15 (set (mem:DI (plus:DI (reg:DI a2) (const_int 96)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 16 (set (mem:DI (plus:DI (reg:DI a2) (const_int 104)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 17 (set (mem:DI (plus:DI (reg:DI a2) (const_int 112)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 18 (set (reg:DI a0) (sign_extend:DI (reg:SI a0))))
      (cinsn 19 (use (reg:DI a0)))
      (cjump_insn 20 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
sad_gap_far (unsigned long a, unsigned long b, unsigned long c,
             unsigned long d)
{
(function "sad_gap_far"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (mem:DI (reg:DI a2) [0 S8 A64]) (reg:DI a0)))
      (cinsn 4 (set (mem:DI (plus:DI (reg:DI a2) (const_int 8)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 5 (set (mem:DI (plus:DI (reg:DI a2) (const_int 16)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 6 (set (mem:DI (plus:DI (reg:DI a2) (const_int 24)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 7 (set (mem:DI (plus:DI (reg:DI a2) (const_int 32)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 8 (set (mem:DI (plus:DI (reg:DI a2) (const_int 40)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 9 (set (mem:DI (plus:DI (reg:DI a2) (const_int 48)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 10 (set (mem:DI (plus:DI (reg:DI a2) (const_int 56)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 11 (set (mem:DI (plus:DI (reg:DI a2) (const_int 64)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 12 (set (mem:DI (plus:DI (reg:DI a2) (const_int 72)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 13 (set (mem:DI (plus:DI (reg:DI a2) (const_int 80)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 14 (set (mem:DI (plus:DI (reg:DI a2) (const_int 88)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 15 (set (mem:DI (plus:DI (reg:DI a2) (const_int 96)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 16 (set (mem:DI (plus:DI (reg:DI a2) (const_int 104)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 17 (set (mem:DI (plus:DI (reg:DI a2) (const_int 112)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 18 (set (mem:DI (plus:DI (reg:DI a2) (const_int 120)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 19 (set (reg:DI a0) (sign_extend:DI (reg:SI a0))))
      (cinsn 20 (use (reg:DI a0)))
      (cjump_insn 21 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* The closest full definition wins.  Preserve the earlier stored result.  */
unsigned long __RTL (startwith ("peephole2"))
sad_gap_overwrite (unsigned long a, unsigned long b, unsigned long c,
                   unsigned long d)
{
(function "sad_gap_overwrite"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (mem:DI (reg:DI a3) [0 S8 A64]) (reg:DI a4)))
      (cinsn 4 (set (reg:DI a4) (reg:DI a2)))
      (cinsn 5 (set (reg:DI a0) (sign_extend:DI (reg:SI a4))))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* Partial writes and clobbers are compile-only controls.  */
unsigned long __RTL (startwith ("peephole2"))
sad_gap_partial (unsigned long a, unsigned long b, unsigned long c,
                 unsigned long d)
{
(function "sad_gap_partial"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (mem:DI (reg:DI a3) [0 S8 A64]) (reg:DI a4)))
      (cinsn 4 (set (reg:HI a4) (reg:HI a2)))
      (cinsn 5 (set (reg:DI a0) (sign_extend:DI (reg:SI a4))))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long __RTL (startwith ("peephole2"))
sad_gap_clobber (unsigned long a, unsigned long b, unsigned long c,
                 unsigned long d)
{
(function "sad_gap_clobber"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (set (mem:DI (reg:DI a3) [0 S8 A64]) (reg:DI a4)))
      (cinsn 4 (clobber (reg:HI a4)))
      (cinsn 5 (set (reg:DI a0) (sign_extend:DI (reg:SI a4))))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* Opaque assembly must stop the search.  */
unsigned long __RTL (startwith ("peephole2"))
sad_gap_barrier (unsigned long a, unsigned long b, unsigned long c,
                 unsigned long d)
{
(function "sad_gap_barrier"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI a0)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (cinsn 3 (asm_input/v ("") 0))
      (cinsn 4 (set (reg:DI a0) (sign_extend:DI (reg:SI a0))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* A lexical SAD in a predecessor does not prove the value at a join.  */
unsigned long __RTL (startwith ("peephole2"))
sad_gap_merge (unsigned long a, unsigned long b, unsigned long choose,
           unsigned long seed)
{
(function "sad_gap_merge"
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
      (cinsn 8 (set (reg:DI a4)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (edge-to 5 (flags "FALLTHRU")))
    (block 5
      (edge-from 3)
      (edge-from 4 (flags "FALLTHRU"))
      (clabel 9 2)
      (cnote 10 [bb 5] NOTE_INSN_BASIC_BLOCK)
      (cinsn 12 (set (reg:DI a0) (sign_extend:DI (reg:SI a4))))
      (cinsn 13 (use (reg:DI a0)))
      (cjump_insn 15 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}


void __attribute__ ((noipa))
sad_gap_callee (void)
{
  __asm__ volatile ("");
}

/* Even an ABI-preserved SAD result is not tracked across a call.  */
unsigned long __RTL (startwith ("peephole2"))
sad_gap_call (unsigned long a, unsigned long b)
{
(function "sad_gap_call"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:DI sp) (plus:DI (reg:DI sp) (const_int -32))))
      (cinsn 3 (set (mem:DI (reg:DI sp) [0 S8 A64]) (reg:DI ra)))
      (cinsn 4 (set (mem:DI (plus:DI (reg:DI sp) (const_int 8)) [0 S8 A64]) (reg:DI s1)))
      (cinsn 5 (set (mem:DI (plus:DI (reg:DI sp) (const_int 16)) [0 S8 A64]) (reg:DI a0)))
      (cinsn 6 (set (mem:DI (plus:DI (reg:DI sp) (const_int 24)) [0 S8 A64]) (reg:DI a1)))
      (cinsn 7 (set (reg:DI s1)
        (unspec:DI [(reg:DI a0) (reg:DI a1)] UNSPEC_PABDSUMU)))
      (ccall_insn 8 (parallel [(call (mem:SI (symbol_ref:DI ("sad_gap_callee") [flags 0x3]) [0 S4 A32]) (const_int 0))
        (use (unspec:SI [(const_int 0)] UNSPEC_CALLEE_CC))
        (clobber (reg:SI ra))]))
      (cinsn 9 (set (reg:DI a0) (mem:DI (plus:DI (reg:DI sp) (const_int 16)) [0 S8 A64])))
      (cinsn 10 (set (reg:DI a1) (mem:DI (plus:DI (reg:DI sp) (const_int 24)) [0 S8 A64])))
      (cinsn 12 (set (reg:DI a0) (sign_extend:DI (reg:SI s1))))
      (cinsn 13 (set (reg:DI ra) (mem:DI (reg:DI sp) [0 S8 A64])))
      (cinsn 14 (set (reg:DI s1) (mem:DI (plus:DI (reg:DI sp) (const_int 8)) [0 S8 A64])))
      (cinsn 15 (set (reg:DI sp) (plus:DI (reg:DI sp) (const_int 32))))
      (cinsn 18 (use (reg:DI s1)))
      (cinsn 16 (use (reg:DI a0)))
      (cjump_insn 17 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* { dg-final { check-function-bodies "**" "" } } */
/*
** sad_gap_sign:
**  pabdsumu\.b\s+a0,a0,a1
**  sd\s+a0,0\(a2\)
**  ret
*/
/*
** sad_gap_zero:
**  pabdsumu\.b\s+a0,a0,a1
**  sd\s+a0,0\(a2\)
**  ret
*/
/*
** sad_gap_copy:
**  pabdsumu\.b\s+a4,a0,a1
**  sd\s+a4,0\(a2\)
**  mv\s+a0,a4
**  ret
*/
/*
** sad_gap_load:
**  ld\s+a5,0\(a2\)
**  pabdsumu\.b\s+a0,a0,a1
**  add\s+a0,a0,a5
**  ret
*/
/*
** sad_gap_limit:
**  pabdsumu\.b\s+a0,a0,a1
**  sd\s+a0,0\(a2\)
**  sd\s+a0,8\(a2\)
**  sd\s+a0,16\(a2\)
**  sd\s+a0,24\(a2\)
**  sd\s+a0,32\(a2\)
**  sd\s+a0,40\(a2\)
**  sd\s+a0,48\(a2\)
**  sd\s+a0,56\(a2\)
**  sd\s+a0,64\(a2\)
**  sd\s+a0,72\(a2\)
**  sd\s+a0,80\(a2\)
**  sd\s+a0,88\(a2\)
**  sd\s+a0,96\(a2\)
**  sd\s+a0,104\(a2\)
**  sd\s+a0,112\(a2\)
**  ret
*/
/*
** sad_gap_far:
**  ...
**  sext\.w\s+a0,a0
**  ...
*/
/*
** sad_gap_overwrite:
**  ...
**  sext\.w\s+a0,a2
**  ...
*/
/*
** sad_gap_partial:
**  ...
**  sext\.w\s+a0,a4
**  ...
*/
/*
** sad_gap_clobber:
**  ...
**  sext\.w\s+a0,a4
**  ...
*/
/*
** sad_gap_barrier:
**  ...
**  sext\.w\s+a0,a0
**  ...
*/
/*
** sad_gap_merge:
**  ...
**  sext\.w\s+a0,a4
**  ...
*/
/*
** sad_gap_call:
**  ...
**  sext\.w\s+a0,s1
**  ...
*/
/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 12 } } */
/* { dg-final { scan-assembler-times {\tsext\.w\t} 7 } } */
