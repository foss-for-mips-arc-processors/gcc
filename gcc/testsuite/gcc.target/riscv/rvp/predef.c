/* { dg-do preprocess } */
/* { dg-options "-march=rv64gc_p -mabi=lp64d" } */

#if !defined (__riscv_p) || __riscv_p != 21000
#error "P extension macro has the wrong version"
#endif

#if !defined (__riscv_zba)
#error "P extension must imply Zba"
#endif

#if !defined (__riscv_zbb)
#error "P extension must imply Zbb"
#endif

#if !defined (__riscv_zmmul)
#error "P extension must imply Zmmul"
#endif
