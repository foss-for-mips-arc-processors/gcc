/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

/* Force overlapping scalar views after allocation, including odd pairs
   that the allocator would not normally choose for packed operations.  */
unsigned long long __RTL (startwith ("split2"))
shift_right (unsigned long long input)
{
(function "shift_right"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:PV2SI a1)
        (and:PV2SI (reg:PV2SI a0)
          (const_vector:PV2SI [(const_int 127) (const_int 2047)]))))
      (cinsn 3 (set (reg:SI a0) (reg:SI a1)))
      (cinsn 4 (set (reg:SI a1) (reg:SI a2)))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long long __RTL (startwith ("split2"))
shift_left (unsigned long long input)
{
(function "shift_left"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:SI a2) (reg:SI a1)))
      (cinsn 3 (set (reg:SI a1) (reg:SI a0)))
      (cinsn 4 (set (reg:PV2SI a0)
        (ior:PV2SI (reg:PV2SI a1)
          (const_vector:PV2SI [(const_int -2048) (const_int -128)]))))
      (cinsn 5 (use (reg:DI a0)))
      (cjump_insn 6 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

unsigned long long __RTL (startwith ("split2"))
same_pair (unsigned long long input)
{
(function "same_pair"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 2 (set (reg:PV2SI a0)
        (xor:PV2SI (reg:PV2SI a0)
          (const_vector:PV2SI [(const_int -2048) (const_int 2047)]))))
      (cinsn 3 (use (reg:DI a0)))
      (cjump_insn 4 (simple_return))
      (edge-to exit)))
  (crtl (return_rtx (reg:DI a0))))
}

/* The high source must be read before the low destination overwrites it.  */
/* { dg-final { scan-assembler {andi\s+a2,a1,2047\n\s+andi\s+a1,a0,127} } } */
/* { dg-final { scan-assembler-times {\mori\M} 2 } } */
/* { dg-final { scan-assembler-times {\mxori\M} 2 } } */
