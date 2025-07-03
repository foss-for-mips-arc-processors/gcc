;; Machine description for the XARCVudsp extension
;; Copyright (C) 2025 Free Software Foundation, Inc.

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

(define_c_enum "unspec" [

;; ARC-V UDSP
  UNSPEC_ARCV_UDSP_VADD_VV_I16M1
  UNSPEC_ARCV_UDSP_VSUB_VV_I16M1
  UNSPEC_ARCV_UDSP_VSADD_VV_I16M1
  UNSPEC_ARCV_UDSP_VSADD_VV_I32M1
  UNSPEC_ARCV_UDSP_VSSUB_VV_I16M1
  UNSPEC_ARCV_UDSP_VSSUB_VV_I32M1
  UNSPEC_ARCV_UDSP_VSLL_VX_I16M1
  UNSPEC_ARCV_UDSP_VSRA_VX_I16M1
  UNSPEC_ARCV_UDSP_VNCLIP_WX_I16M1
  UNSPEC_ARCV_UDSP_VNCLIP_WX_I16MF2
  UNSPEC_ARCV_UDSP_VWMUL_VV_I16M1
  UNSPEC_ARCV_UDSP_VWMUL_VV_I16MF2
  UNSPEC_ARCV_UDSP_VWSRDOT_VV_I16M1
  UNSPEC_ARCV_UDSP_VSCMUL_VV_I16M1
  UNSPEC_ARCV_UDSP_VSCJMUL_VV_I16M1
  UNSPEC_ARCV_UDSP_VWSCMUL_VV_I16M1
  UNSPEC_ARCV_UDSP_VWSCJMUL_VV_I16M1
  UNSPEC_ARCV_UDSP_VWSCRDOT_VV_I16M1
  UNSPEC_ARCV_UDSP_VWSCJRDOT_VV_I16M1
  UNSPEC_ARCV_UDSP_BITREV
])


(define_insn "riscv_arcv_udsp_xvadd_vv_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "%r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VADD_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvadd.vv\t%0,%1,%2,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvsub_vv_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSUB_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvsub.vv\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvsadd_vv_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "%r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSADD_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvsadd.vv\t%0,%1,%2,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvsadd_vv_i32m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "%r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSADD_VV_I32M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvsadd.vv\t%0,%1,%2,e32,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvssub_vv_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSSUB_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvssub.vv\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvssub_vv_i32m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSSUB_VV_I32M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvssub.vv\t%0,%2,%1,e32,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvsll_vx_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSLL_VX_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvsll.vx\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvsra_vx_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSRA_VX_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvsra.vx\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvnclip_wx_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r,r,r")
	(unspec:SI [(match_operand:DI 1 "register_operand" "xAVp06,xAVp08,xAVp10,xAVp12,xAVp14,xAVp16,xAVp18,xAVp20,xAVp22,xAVp24,xAVp26,xAVp28,xAVp30")
	      (match_operand:SI 2 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r,r")]
  UNSPEC_ARCV_UDSP_VNCLIP_WX_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvnclip.wx\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvnclip_wx_i16mf2"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VNCLIP_WX_I16MF2))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvnclip.wx\t%0,%2,%1,e16,mf2"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvwmul_vv_i16m1"
  [(set (match_operand:DI 0 "register_operand" "=xAVp06,xAVp08,xAVp10,xAVp12,xAVp14,xAVp16,xAVp18,xAVp20,xAVp22,xAVp24,xAVp26,xAVp28,xAVp30")
	(unspec:DI [(match_operand:SI 1 "register_operand" "%xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")
	      (match_operand:SI 2 "register_operand" "xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")]
  UNSPEC_ARCV_UDSP_VWMUL_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvwmul.vv\t%0,%1,%2,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvwmul_vv_i16mf2"
  [(set (match_operand:SI 0 "register_operand" "=&r")
	(unspec:SI [(match_operand:HI 1 "register_operand" "%r")
	      (match_operand:HI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VWMUL_VV_I16MF2))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvwmul.vv\t%0,%1,%2,e16,mf2"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvwsrdot_vv_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "0")
              (match_operand:SI 2 "register_operand" "r")
	      (match_operand:SI 3 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VWSRDOT_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvwsrdot.vv\t%0,%2,%3,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvscmul_vv_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSCMUL_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvscmul.vv\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvscjmul_vv_i16m1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_VSCJMUL_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvscjmul.vv\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvwscmul_vv_i16m1"
  [(set (match_operand:DI 0 "register_operand" "=xAVp06,xAVp08,xAVp10,xAVp12,xAVp14,xAVp16,xAVp18,xAVp20,xAVp22,xAVp24,xAVp26,xAVp28,xAVp30")
	(unspec:DI [(match_operand:SI 1 "register_operand" "%xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")
	      (match_operand:SI 2 "register_operand" "xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")]
  UNSPEC_ARCV_UDSP_VWSCMUL_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvwscmul.vv\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvwscjmul_vv_i16m1"
  [(set (match_operand:DI 0 "register_operand" "=xAVp06,xAVp08,xAVp10,xAVp12,xAVp14,xAVp16,xAVp18,xAVp20,xAVp22,xAVp24,xAVp26,xAVp28,xAVp30")
	(unspec:DI [(match_operand:SI 1 "register_operand" "%xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")
	      (match_operand:SI 2 "register_operand" "xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")]
  UNSPEC_ARCV_UDSP_VWSCJMUL_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvwscjmul.vv\t%0,%2,%1,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvwscrdot_vv_i16m1"
  [(set (match_operand:DI 0 "register_operand" "=xAVp06,xAVp08,xAVp10,xAVp12,xAVp14,xAVp16,xAVp18,xAVp20,xAVp22,xAVp24,xAVp26,xAVp28,xAVp30")
	(unspec:DI [(match_operand:DI 1 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0,0")
              (match_operand:SI 2 "register_operand" "%xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")
	      (match_operand:SI 3 "register_operand" "xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")]
  UNSPEC_ARCV_UDSP_VWSCRDOT_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvwscrdot.vv\t%0,%2,%3,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_xvwscjrdot_vv_i16m1"
  [(set (match_operand:DI 0 "register_operand" "=xAVp06,xAVp08,xAVp10,xAVp12,xAVp14,xAVp16,xAVp18,xAVp20,xAVp22,xAVp24,xAVp26,xAVp28,xAVp30")
	(unspec:DI [(match_operand:DI 1 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0,0")
              (match_operand:SI 2 "register_operand" "%xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")
	      (match_operand:SI 3 "register_operand" "xAVn06,xAVn08,xAVn10,xAVn12,xAVn14,xAVn16,xAVn18,xAVn20,xAVn22,xAVn24,xAVn26,xAVn28,xAVn30")]
  UNSPEC_ARCV_UDSP_VWSCJRDOT_VV_I16M1))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.xvwscjrdot.vv\t%0,%2,%3,e16,m1"
[(set_attr "type" "arith")])

(define_insn "riscv_arcv_udsp_bitrev"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
	      (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_UDSP_BITREV))]
  "TARGET_XARCVUDSP && !TARGET_64BIT"
  "arcv.bitrev\t%0,%1,%2"
[(set_attr "type" "arith")])


