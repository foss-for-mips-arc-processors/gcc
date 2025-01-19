/* { dg-do compile } */
/* { dg-options "-mriscv-attribute -march=rv64i_zca_zcb_zcmp_zcmt -mabi=lp64" } */

void foo(){}

/* { dg-final { scan-assembler ".attribute arch, \"rv64i2p1_c2p0_zicsr2p0_zca1p0_zcb1p0_zce1p0_zcmp1p0_zcmt1p0\"" } } */
