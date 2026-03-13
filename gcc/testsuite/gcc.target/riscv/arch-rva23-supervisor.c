/* { dg-do compile } */
/* { dg-options "-march=rv64imafdcbv_zicsr_zicntr_zihpm_ziccif_ziccrse_ziccamoa_zicclsm_zic64b_za64rs_zihintpause_zba_zbb_zbs_zicbom_zicbop_zicboz_zfhmin_zkt_zvfhmin_zvbb_zvkt_zihintntl_zicond_zimop_zcmop_zcb_zfa_zawrs_svbare_svade_ssccptr_sstvecd_sstvala_sscounterenw_svpbmt_svinval_svnapot_sstc_sscofpmf_ssnpm_ssu64xl_sha_supm_zifencei -mabi=lp64d" } */

/* Test that RVA23 supervisor extensions produce the correct .attribute arch */

void foo(){}

/* { dg-final { scan-assembler ".attribute arch, \"rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0" } } */
/* { dg-final { scan-assembler "_b1p0_v1p0_h1p0_zic64b1p0_zicbom1p0_zicbop1p0_zicboz1p0" } } */
/* { dg-final { scan-assembler "_ziccamoa1p0_ziccif1p0_zicclsm1p0_ziccrse1p0_zicntr2p0" } } */
/* { dg-final { scan-assembler "_zicond1p0_zicsr2p0_zifencei2p0_zihintntl1p0_zihintpause2p0" } } */
/* { dg-final { scan-assembler "_zihpm2p0_zimop1p0_zmmul1p0_za64rs1p0_zaamo1p0_zalrsc1p0" } } */
/* { dg-final { scan-assembler "_zawrs1p0_zfa1p0_zfhmin1p0_zca1p0_zcb1p0_zcd1p0_zcmop1p0" } } */
/* { dg-final { scan-assembler "_zba1p0_zbb1p0_zbs1p0_zkt1p0_zvbb1p0_zve32f1p0_zve32x1p0" } } */
/* { dg-final { scan-assembler "_zve64d1p0_zve64f1p0_zve64x1p0_zvfhmin1p0_zvkb1p0_zvkt1p0" } } */
/* { dg-final { scan-assembler "_zvl128b1p0_zvl32b1p0_zvl64b1p0_sha1p0_shcounterenw1p0" } } */
/* { dg-final { scan-assembler "_shgatpa1p0_shtvala1p0_shvsatpa1p0_shvstvala1p0_shvstvecd1p0" } } */
/* { dg-final { scan-assembler "_ssccptr1p0_sscofpmf1p0_sscounterenw1p0_ssnpm1p0_ssstateen1p0" } } */
/* { dg-final { scan-assembler "_sstc1p0_sstvala1p0_sstvecd1p0_ssu64xl1p0_supm1p0_svade1p0" } } */
/* { dg-final { scan-assembler "_svbare1p0_svinval1p0_svnapot1p0_svpbmt1p0\"" } } */
