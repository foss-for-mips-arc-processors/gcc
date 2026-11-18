/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -mlittle-endian -O3 -fdump-rtl-combine" } */

#include "autovec-pack-load-order.h"

/* { dg-final { scan-rtl-dump-not {riscv_p_pack_trunc_load_pv2hi|rvp_pack_ustrunc_small_load} "combine" } } */
