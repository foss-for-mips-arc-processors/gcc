/* { dg-do compile { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-O[sgz]" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=xt-c9501fdvt -O2 -fdump-rtl-sched2-details" } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-rtl-dump-times {Fusion reorder: \(3, 5\)} 1 "sched2" { xfail *-*-* } } } */
/* { dg-final { scan-rtl-dump-not "macro fusion:" "sched2" } } */

/* Move the second A2 load next to the first without extending the pair.  */

/*
**test_reorder2_load_pair: { xfail *-*-* }
**	ld	a1,0\(a2\)
**	ld	a3,8\(a2\)
**	ld	a5,0\(a0\)
**	ld	a6,0\(t0\)
**	ld	a4,16\(a2\)
**	...
**	ret
*/
long __RTL (startwith ("sched2"))
test_reorder2_load_pair (void)
{
(function "test_reorder2_load_pair"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (reg:DI a1)
                    (mem:DI (reg:DI a2) [0 S8 A64])))
      (cinsn 4 (set (reg:DI a5)
                    (mem:DI (reg:DI a0) [0 S8 A64])))
      (cinsn 5 (set (reg:DI a3)
                    (mem:DI
                      (plus:DI (reg:DI a2)
                               (const_int 8)) [0 S8 A64])))
      (cinsn 6 (set (reg:DI a6)
                    (mem:DI (reg:DI t0) [0 S8 A64])))
      (cinsn 7 (set (reg:DI a4)
                    (mem:DI
                      (plus:DI (reg:DI a2)
                               (const_int 16)) [0 S8 A64])))
      (cinsn 8 (set (reg:DI a7)
                    (plus:DI (reg:DI a1) (reg:DI a0))))
      (cinsn 9 (use (reg:DI a7)))
      (cinsn 10 (use (reg:DI a3)))
      (cinsn 11 (use (reg:DI a4)))
      (cinsn 12 (use (reg:DI a5)))
      (cinsn 13 (use (reg:DI a6)))
      (cjump_insn 14 (simple_return))
      (edge-to exit)
    ) ;; block 2
    (cbarrier 15)
  ) ;; insn-chain
  (crtl
    (return_rtx
      (reg/i:DI a0)
    ) ;; return_rtx
  ) ;; crtl
) ;; function "test_reorder2_load_pair"
}
