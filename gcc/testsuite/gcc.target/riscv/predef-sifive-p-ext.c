/* { dg-do compile } */
/* { dg-options "-march=rv64i_p0p21 -mabi=lp64" } */

int main () {

#ifndef __riscv_arch_test
#error "__riscv_arch_test"
#endif

#if __riscv_xlen != 64
#error "__riscv_xlen"
#endif

#if !defined(__riscv_i)
#error "__riscv_i"
#endif

#if !defined(__riscv_p)
#error "__riscv_p"
#endif

#if !defined(__riscv_zba)
#error "__riscv_zba"
#endif

#if !defined(__riscv_zbb)
#error "__riscv_zbb"
#endif

#if !defined(__riscv_zmmul)
#error "__riscv_zmmul"
#endif

  return 0;
}
