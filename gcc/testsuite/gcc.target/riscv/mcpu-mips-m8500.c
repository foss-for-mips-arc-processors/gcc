/* { dg-do compile } */
/* { dg-skip-if "-march given" { *-*-* } { "-march=*" } } */
/* { dg-options "-mcpu=mips-m8500 -mabi=ilp32" } */
/* mips-m8500 = rv32imafdb_zce_zbc_zicbop_zimop_zcmop_zicond_zihintntl_zihintpause_zawrs_zabha_zbkb_zbkx_zfa_zicbom_zicboz_zifencei_zicsr_zicntr_zilsd_xmipscmov_xmipsexectl_xmipslsp_xmipstrig */

#if !((__riscv_xlen == 32)		\
      && !defined(__riscv_32e)		\
      && defined(__riscv_zicbom)	\
      && defined(__riscv_zicbop)	\
      && defined(__riscv_zicboz)	\
      && defined(__riscv_zicsr)		\
      && defined(__riscv_zifencei)	\
      && defined(__riscv_zihintntl)	\
      && defined(__riscv_zihintpause)	\
      && defined(__riscv_zba)		\
      && defined(__riscv_zbb)		\
      && defined(__riscv_zbs))
#error "unexpected arch"
#endif

int main() {
  return 0;
}

/* { dg-final { scan-assembler "rv32i2p1_m2p0_a2p1_f2p2_d2p2_b1p0_zicbom1p0_zicbop1p0_zicboz1p0_zicntr2p0_zicond1p0_zicsr2p0_zifencei2p0_zihintntl1p0_zihintpause2p0_zilsd1p0_zimop1p0_zmmul1p0_zaamo1p0_zabha1p0_zalrsc1p0_zawrs1p0_zfa1p0_zca1p0_zcb1p0_zce1p0_zcf1p0_zcmop1p0_zcmp1p0_zcmt1p0_zba1p0_zbb1p0_zbc1p0_zbkb1p0_zbkx1p0_zbs1p0_xmipscmov1p0_xmipsexectl1p0_xmipslsp1p0_xmipstrig1p0" } }*/
