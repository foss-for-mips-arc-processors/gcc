/* { dg-do compile { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-O[sgz]" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=xt-c9501fdvt -O2 -fdump-rtl-sched2-details" } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-rtl-dump-times {Fusion reorder: \(3, 5\)} 1 "sched2" { xfail *-*-* } } } */
/* { dg-final { scan-rtl-dump-not "macro fusion:" "sched2" } } */

/* Recognize POSTINDEX_ST across a zero-cost USE.  */

/*
**test_reorder2_postindex_st: { xfail *-*-* }
**	sd	a2,0\(a0\)
**	addi	a0,a0,8
**	ret
*/
long __RTL (startwith ("sched2"))
test_reorder2_postindex_st (void)
{
(function "test_reorder2_postindex_st"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (mem:DI (reg:DI a0) [0 S8 A64])
                    (reg:DI a2)))
      (cinsn 4 (use (reg:DI a6)))
      (cinsn 5 (set (reg:DI a0)
                    (plus:DI (reg:DI a0) (const_int 8))))
      (cinsn 6 (use (reg:DI a0)))
      (cjump_insn 7 (simple_return))
      (edge-to exit)
    ) ;; block 2
    (cbarrier 8)
  ) ;; insn-chain
  (crtl
    (return_rtx
      (reg/i:DI a0)
    ) ;; return_rtx
  ) ;; crtl
) ;; function "test_reorder2_postindex_st"
}
