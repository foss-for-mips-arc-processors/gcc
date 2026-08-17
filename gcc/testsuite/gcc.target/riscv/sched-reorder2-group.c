/* { dg-do compile { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-O[sgz]" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=xt-c9501fdvt -O2 -fdump-rtl-sched2-details" } */
/* { dg-final { scan-rtl-dump-times "macro fusion:" 2 "sched2" { xfail *-*-* } } } */
/* { dg-final { scan-rtl-dump-not {Fusion reorder: \(7, 5\)} "sched2" } } */

/* Do not pair a load with the first instruction of an existing group.  */

long __RTL (startwith ("sched2"))
test_reorder2_group (void)
{
(function "test_reorder2_group"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (reg:DI a5)
                    (mem:DI (reg:DI t0) [0 S8 A64])))
      (cinsn 4 (set (reg:DI a6)
                    (mem:DI
                      (plus:DI (reg:DI t0)
                               (const_int 8)) [0 S8 A64])))
      (cinsn 5 (set (reg:DI a3)
                    (mem:DI
                      (plus:DI (reg:DI a2)
                               (const_int 8)) [0 S8 A64])))
      (cinsn 6 (set (reg:DI a4)
                    (mem:DI
                      (plus:DI (reg:DI a2)
                               (const_int 16)) [0 S8 A64])))
      (cinsn 7 (set (reg:DI a1)
                    (mem:DI (reg:DI a2) [0 S8 A64])))
      (cinsn 8 (set (reg:DI a7)
                    (plus:DI (reg:DI a1) (reg:DI a0))))
      (cinsn 9 (set (reg:DI t1)
                    (plus:DI (reg:DI a7) (reg:DI a0))))
      (cinsn 10 (set (reg:DI t2)
                     (plus:DI (reg:DI t1) (reg:DI a0))))
      (cinsn 11 (set (reg:DI t3)
                     (plus:DI (reg:DI t2) (reg:DI a0))))
      (cinsn 12 (set (reg:DI t4)
                     (plus:DI (reg:DI t3) (reg:DI a0))))
      (cinsn 13 (use (reg:DI t4)))
      (cinsn 14 (use (reg:DI a3)))
      (cinsn 15 (use (reg:DI a4)))
      (cinsn 16 (use (reg:DI a5)))
      (cinsn 17 (use (reg:DI a6)))
      (cjump_insn 18 (simple_return))
      (edge-to exit)
    ) ;; block 2
    (cbarrier 19)
  ) ;; insn-chain
  (crtl
    (return_rtx
      (reg/i:DI a0)
    ) ;; return_rtx
  ) ;; crtl
) ;; function "test_reorder2_group"
}
