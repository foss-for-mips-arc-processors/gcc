/* { dg-do compile { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-O[sgz]" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=xt-c9501fdvt -O2 -fsched2-use-superblocks -fdump-rtl-sched2-details" } */
/* { dg-final { scan-rtl-dump-not {Fusion reorder: \(3, 6\)} "sched2" } } */

/* Do not form a ready-list fusion pair across basic blocks.  */

long __RTL (startwith ("sched2"))
test_reorder2_basic_block (void)
{
(function "test_reorder2_basic_block"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (reg:DI a1)
                    (mem:DI (reg:DI a2) [0 S8 A64])))
      (edge-to 3 (flags "FALLTHRU"))
    ) ;; block 2
    (block 3
      (edge-from 2 (flags "FALLTHRU"))
      (cnote 4 [bb 3] NOTE_INSN_BASIC_BLOCK)
      (cinsn 5 (set (reg:DI a5)
                    (mem:DI (reg:DI t0) [0 S8 A64])))
      (cinsn 6 (set (reg:DI a3)
                    (mem:DI
                      (plus:DI (reg:DI a2)
                               (const_int 8)) [0 S8 A64])))
      (cinsn 7 (set (reg:DI a4)
                    (plus:DI (reg:DI a1) (reg:DI a0))))
      (cinsn 8 (set (reg:DI a6)
                    (plus:DI (reg:DI a4) (reg:DI a0))))
      (cinsn 9 (use (reg:DI a3)))
      (cinsn 10 (use (reg:DI a5)))
      (cinsn 11 (use (reg:DI a6)))
      (cjump_insn 12 (simple_return))
      (edge-to exit)
    ) ;; block 3
    (cbarrier 13)
  ) ;; insn-chain
  (crtl
    (return_rtx
      (reg/i:DI a0)
    ) ;; return_rtx
  ) ;; crtl
) ;; function "test_reorder2_basic_block"
}
