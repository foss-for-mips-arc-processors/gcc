/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rpx-100-series -march=rv64im_zbs -mabi=lp64 -fdump-rtl-sched2" } */

__int128 __RTL (startwith ("sched2"))
foo (void)
{
(function "foo"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (reg:DI a4)
                    (truncate:DI
                      (lshiftrt:TI
                        (mult:TI (sign_extend:TI (reg:DI a0))
                                 (sign_extend:TI (reg:DI a1)))
                        (const_int 64)))))
      (cinsn 4 (set (reg:DI a5)
                    (mult:DI (reg:DI a0)
                             (reg:DI a1))))
      (cinsn 5 (set (reg:DI a0)
                    (plus:DI (reg:DI a5)
                             (const_int 1))))
      (cinsn 6 (set (reg:DI t0)
                    (ltu:DI (reg:DI a0)
                            (reg:DI a5))))
      (cinsn 7 (set (reg:DI a1)
                    (plus:DI (reg:DI t0)
                             (reg:DI a4))))
      (cinsn 8 (use (reg/i:TI a0)))
      (cjump_insn 9 (simple_return))
      (edge-to exit)
    ) ;; block 2
    (cbarrier 10)
  ) ;; insn-chain
  (crtl
    (return_rtx (reg/i:TI a0))
  ) ;; crtl
) ;; function "foo"
}

__int128 __RTL (startwith ("sched2"))
bar (void)
{
(function "bar"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (reg:DI a4)
                    (truncate:DI
                      (lshiftrt:TI
                        (mult:TI (zero_extend:TI (reg:DI a1))
                                 (sign_extend:TI (reg:DI a0)))
                        (const_int 64)))))
      (cinsn 4 (set (reg:DI a5)
                    (mult:DI (reg:DI a0)
                             (reg:DI a1))))
      (cinsn 5 (set (reg:DI a0)
                    (plus:DI (reg:DI a5)
                             (const_int 1))))
      (cinsn 6 (set (reg:DI t0)
                    (ltu:DI (reg:DI a0)
                            (reg:DI a5))))
      (cinsn 7 (set (reg:DI a1)
                    (plus:DI (reg:DI t0)
                             (reg:DI a4))))
      (cinsn 8 (use (reg/i:TI a0)))
      (cjump_insn 9 (simple_return))
      (edge-to exit)
    ) ;; block 2
    (cbarrier 10)
  ) ;; insn-chain
  (crtl
    (return_rtx (reg/i:TI a0))
  ) ;; crtl
) ;; function "bar"
}

__int128 __RTL (startwith ("sched2"))
baz (void)
{
(function "baz"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (reg:DI a4)
                    (truncate:DI
                      (lshiftrt:TI
                        (mult:TI (zero_extend:TI (reg:DI a0))
                                 (zero_extend:TI (reg:DI a1)))
                        (const_int 64)))))
      (cinsn 4 (set (reg:DI a5)
                    (mult:DI (reg:DI a0)
                             (reg:DI a1))))
      (cinsn 5 (set (reg:DI a0)
                    (plus:DI (reg:DI a5)
                             (const_int 1))))
      (cinsn 6 (set (reg:DI t0)
                    (ltu:DI (reg:DI a0)
                            (reg:DI a5))))
      (cinsn 7 (set (reg:DI a1)
                    (plus:DI (reg:DI t0)
                             (reg:DI a4))))
      (cinsn 8 (use (reg/i:TI a0)))
      (cjump_insn 9 (simple_return))
      (edge-to exit)
    ) ;; block 2
    (cbarrier 10)
  ) ;; insn-chain
  (crtl
    (return_rtx (reg/i:TI a0))
  ) ;; crtl
) ;; function "baz"
}

__int128 __RTL (startwith ("sched2"))
quux (void)
{
(function "quux"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 1 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cnote 2 NOTE_INSN_FUNCTION_BEG)
      (cinsn 3 (set (reg:DI a4)
                    (truncate:DI
                      (lshiftrt:TI
                        (mult:TI (zero_extend:TI (reg:DI a0))
                                 (sign_extend:TI (reg:DI a1)))
                        (const_int 64)))))
      (cinsn 4 (set (reg:DI a5)
                    (mult:DI (reg:DI a1)
                             (reg:DI a0))))
      (cinsn 5 (set (reg:DI a0)
                    (plus:DI (reg:DI a5)
                             (const_int 1))))
      (cinsn 6 (set (reg:DI t0)
                    (ltu:DI (reg:DI a0)
                            (reg:DI a5))))
      (cinsn 7 (set (reg:DI a1)
                    (plus:DI (reg:DI t0)
                             (reg:DI a4))))
      (cinsn 8 (use (reg/i:TI a0)))
      (cjump_insn 9 (simple_return))
      (edge-to exit)
    ) ;; block 2
    (cbarrier 10)
  ) ;; insn-chain
  (crtl
    (return_rtx (reg/i:TI a0))
  ) ;; crtl
) ;; function "quux"
}

/* { dg-final { scan-rtl-dump "(?n)0-->.*a4=trn\\(sxn\\(a0\\)\\*sxn\\(a1\\) 0>>0x40\\).*\n.*4-->.*a5=a0\\*a1.*\n.*9-->.*a0=a5\\+0x1.*" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?n)0-->.*a4=trn\\(zxn\\(a1\\)\\*sxn\\(a0\\) 0>>0x40\\).*\n.*4-->.*a5=a0\\*a1.*\n.*9-->.*a0=a5\\+0x1.*" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?n)0-->.*a4=trn\\(zxn\\(a0\\)\\*zxn\\(a1\\) 0>>0x40\\).*\n.*4-->.*a5=a0\\*a1.*\n.*9-->.*a0=a5\\+0x1.*" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?n)0-->.*a4=trn\\(zxn\\(a0\\)\\*sxn\\(a1\\) 0>>0x40\\).*\n.*4-->.*a5=a1\\*a0.*\n.*9-->.*a0=a5\\+0x1.*" "sched2" } } */
