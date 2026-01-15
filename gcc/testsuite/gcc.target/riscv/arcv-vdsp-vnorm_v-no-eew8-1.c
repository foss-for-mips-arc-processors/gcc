/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } }
 */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */

#include <riscv_vector.h>
#include <stddef.h>

int test_vnorm_v_i8(vbool8_t mask,vint8m1_t v, size_t vl) {
    int result = 0;
    result += __riscv_arcv_vnorm_v_i8m1(v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_i8m1'" }*/
    result += __riscv_arcv_vnorm_v_u8m1(v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_u8m1'" }*/

    result += __riscv_arcv_vnorm_v_i8m1_m(mask,v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_i8m1_m'" }*/
    result += __riscv_arcv_vnorm_v_u8m1_m(mask, v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_u8m1_m'" }*/

    result += __riscv_arcv_vnorm_v_i8mf4(v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_i8mf4'" }*/
    result += __riscv_arcv_vnorm_v_i8mf2(v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_i8mf2'" }*/
    result += __riscv_arcv_vnorm_v_i8m2(v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_i8m2'" }*/
    result += __riscv_arcv_vnorm_v_i8m4(v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_i8m4'" }*/
    result += __riscv_arcv_vnorm_v_i8m8(v, vl); /* { dg-error "implicit declaration of function '__riscv_arcv_vnorm_v_i8m8'" }*/
    
    return result;
}