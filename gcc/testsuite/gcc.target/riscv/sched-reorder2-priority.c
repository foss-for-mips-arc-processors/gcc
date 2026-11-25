/* { dg-do compile { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-O[sgz]" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=xt-c9501fdvt -O2 -fdump-rtl-sched2-details" } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-rtl-dump-not "Fusion reorder:" "sched2" } } */

/* Do not move a lower-priority fusion candidate ahead of the ADD.  */

/*
**test_reorder2_respects_priority:
**	ld	a1,0\(a2\)
**	add	a3,a4,a5
**	ld	a6,8\(a2\)
**	...
**	ret
*/
long __RTL (startwith ("sched2"))
test_reorder2_respects_priority (void)
{
(function "test_reorder2_respects_priority"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (reg:DI a1)
                    (mem:DI (reg:DI a2) [0 S8 A64])))
      (cinsn 4 (set (reg:DI a3)
                    (plus:DI (reg:DI a4) (reg:DI a5))))
      (cinsn 5 (set (reg:DI a6)
                    (mem:DI
                      (plus:DI (reg:DI a2)
                               (const_int 8)) [0 S8 A64])))
      (cinsn 6 (set (reg:DI a7)
                    (plus:DI (reg:DI a1) (reg:DI a0))))
      (cinsn 7 (set (reg:DI t0)
                    (plus:DI (reg:DI a7) (reg:DI a0))))
      (cinsn 8 (set (reg:DI t1)
                    (plus:DI (reg:DI t0) (reg:DI a0))))
      (cinsn 9 (set (reg:DI t2)
                    (plus:DI (reg:DI a3) (reg:DI a0))))
      (cinsn 10 (set (reg:DI t3)
                     (plus:DI (reg:DI t2) (reg:DI a0))))
      (cinsn 11 (set (reg:DI t4)
                     (plus:DI (reg:DI t3) (reg:DI a0))))
      (cinsn 12 (set (reg:DI t5)
                     (plus:DI (reg:DI t4) (reg:DI a0))))
      (cinsn 13 (set (reg:DI t6)
                     (plus:DI (reg:DI t5) (reg:DI a0))))
      (cinsn 14 (use (reg:DI t1)))
      (cinsn 15 (use (reg:DI t6)))
      (cinsn 16 (use (reg:DI a6)))
      (cjump_insn 17 (simple_return))
      (edge-to exit)
    ) ;; block 2
    (cbarrier 18)
  ) ;; insn-chain
  (crtl
    (return_rtx
      (reg/i:DI a0)
    ) ;; return_rtx
  ) ;; crtl
) ;; function "test_reorder2_respects_priority"
}
