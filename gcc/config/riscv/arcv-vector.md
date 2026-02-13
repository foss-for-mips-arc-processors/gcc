;; /* Machine description for the ARC-V DSP extensions for GNU compiler.
;;    Copyright (C) 2025 Free Software Foundation, Inc.
;;    Contributed by Artemiy Volkov (artemiy@synopsys.com), Synopsys Inc.
;; 
;;    This file is part of GCC.
;; 
;;    GCC is free software; you can redistribute it and/or modify it
;;    under the terms of the GNU General Public License as published
;;    by the Free Software Foundation; either version 3, or (at your
;;    option) any later version.
;; 
;;    GCC is distributed in the hope that it will be useful, but WITHOUT
;;    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;;    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
;;    License for more details.
;; 
;;    Under Section 7 of GPL version 3, you are granted additional
;;    permissions described in the GCC Runtime Library Exception, version
;;    3.1, as published by the Free Software Foundation.
;; 
;;    You should have received a copy of the GNU General Public License and
;;    a copy of the GCC Runtime Library Exception along with this program;
;;    see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
;;    <http://www.gnu.org/licenses/>.  */


(define_c_enum "unspec" [
  UNSPEC_ARCV_BITREV
  UNSPEC_ARCV_BSPEEK
  UNSPEC_ARCV_BSPOP
  UNSPEC_ARCV_BSPUSH
  UNSPEC_ARCV_VMV_V_S
  UNSPEC_ARCV_VMV_S_V
  UNSPEC_ARCV_VNORM
  UNSPEC_ARCV_VSSABS
  UNSPEC_ARCV_VSNEG
  UNSPEC_ARCV_VCLR
  UNSPEC_ARCV_VSRA
  UNSPEC_ARCV_VSRAT
  UNSPEC_ARCV_VSRA_S
  UNSPEC_ARCV_VSRA_2S
  UNSPEC_ARCV_VNSRA
  UNSPEC_ARCV_VNSRA_S
  UNSPEC_ARCV_VNSRA_2S
  UNSPEC_ARCV_VWSRA
  UNSPEC_ARCV_VADDSUB
  UNSPEC_ARCV_VSADDSUB
  UNSPEC_ARCV_VSAADDSUB
  UNSPEC_ARCV_VQRDOT
  UNSPEC_ARCV_VQRDOT_2S
  UNSPEC_ARCV_VWSRDOT_2S
  UNSPEC_ARCV_VQRDOTU
  UNSPEC_ARCV_VQRDOTSU
  UNSPEC_ARCV_VWRDOT
  UNSPEC_ARCV_VWSRDOT
  UNSPEC_ARCV_VWRDOTU
  UNSPEC_ARCV_VWRDOTSU
  UNSPEC_ARCV_VWSMAC
  UNSPEC_ARCV_VWSNMSAC
  UNSPEC_ARCV_VWMUL
  UNSPEC_ARCV_VWMAC
  UNSPEC_ARCV_VWMULU
  UNSPEC_ARCV_VWMACU
  UNSPEC_ARCV_VSMULF
  UNSPEC_ARCV_VWMULF
  UNSPEC_ARCV_VWSMACF
  UNSPEC_ARCV_VWSNMSACF
  UNSPEC_ARCV_VWSRDOTF
  UNSPEC_ARCV_VCONJ
  UNSPEC_ARCV_VCMULI
  UNSPEC_ARCV_VCMULNI
  UNSPEC_ARCV_VEVEN
  UNSPEC_ARCV_VODD
  UNSPEC_ARCV_VINTERLEAVE
  UNSPEC_ARCV_VSCREDSUM
  UNSPEC_ARCV_VWCREDSUM
  UNSPEC_ARCV_VSCMUL
  UNSPEC_ARCV_VSCMUL_SCALAR
  UNSPEC_ARCV_VSCJMUL
  UNSPEC_ARCV_VSCJMUL_SCALAR
  UNSPEC_ARCV_VWSCMUL
  UNSPEC_ARCV_VWSCMUL_SCALAR
  UNSPEC_ARCV_VWSCJMUL
  UNSPEC_ARCV_VWSCJMUL_SCALAR
  UNSPEC_ARCV_VWSCMAC
  UNSPEC_ARCV_VWSCMAC_SCALAR
  UNSPEC_ARCV_VWSCNMSAC
  UNSPEC_ARCV_VWSCNMSAC_SCALAR
  UNSPEC_ARCV_VWSCJMAC
  UNSPEC_ARCV_VWSCJMAC_SCALAR
  UNSPEC_ARCV_VWSCJNMSAC
  UNSPEC_ARCV_VWSCJNMSAC_SCALAR
  UNSPEC_ARCV_VWSCRDOT
  UNSPEC_ARCV_VWSCJRDOT
  UNSPEC_ARCV_VQCRDOT
  UNSPEC_ARCV_VQCJRDOT
  UNSPEC_ARCV_VWSAD
  UNSPEC_ARCV_VWSADU
  UNSPEC_ARCV_VQMXM4
  UNSPEC_ARCV_VQMXM4U
  UNSPEC_ARCV_VQMXM4SU
  UNSPEC_ARCV_VQMXM8
  UNSPEC_ARCV_VQMXM8U
  UNSPEC_ARCV_VQMXM8SU
  UNSPEC_ARCV_VQMXM16
  UNSPEC_ARCV_VQMXM16U
  UNSPEC_ARCV_VQMXM16SU
])





(define_insn "riscv_arcv_bitrev"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
    (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_BITREV))]
  "TARGET_XARCVBITREV"
  "arcv.bitrev\t%0,%1,%2"
  [(set_attr "type" "arith")])

(define_insn "riscv_arcv_bspeek"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_ARCV_BSPEEK))]
  "TARGET_XARCVBITSTREAM"
  "arcv.bspeek\t%0,%1"
  [(set_attr "type" "arith")])

(define_insn "riscv_arcv_bspop"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_ARCV_BSPOP))]
  "TARGET_XARCVBITSTREAM"
  "arcv.bspop\t%0,%1"
  [(set_attr "type" "arith")])

(define_insn "riscv_arcv_bspush"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
    (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_ARCV_BSPUSH))]
  "TARGET_XARCVBITSTREAM"
  "arcv.bspush\t%0,%1,%2"
  [(set_attr "type" "arith")])

(define_insn "@pred_arcv_vmv_v_s_scalar<V_VLSI:mode><P:mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<V_VLSI:VM>
	    [(match_operand 4 "vector_length_operand" " rK, rK, rK, rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"     "  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<V_VLSI:MODE>
	    [(match_operand:<V_LMUL1> 2 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:P 3 "reg_or_int_operand" "r,r,r,r,r,r,i,i,i,i,i,i")]
	    UNSPEC_ARCV_VMV_V_S)
	  (match_operand:V_VLSI 1 "register_operand" "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0")))]
  "TARGET_XARCVVDSP"
  { return which_alternative < 6 ? "arcv.vmv.v.sx\t%0,%2,%3" : "arcv.vmv.v.si\t%0,%2,%3"; }
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_VLSI:MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (const_int INVALID_ATTRIBUTE))
   (set (attr "ma") (const_int INVALID_ATTRIBUTE))
   (set (attr "avl_type_idx") (const_int 5))])

(define_insn "@pred_arcv_vmv_s_v_scalar<V_VLSI:mode><P:mode>"
  [(set (match_operand:<V_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_LMUL1>
	  (unspec:<V_VLSI:VM>
	    [(match_operand 4 "vector_length_operand" " rK, rK, rK, rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"     "  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<V_LMUL1>
	    [(match_operand:V_VLSI 2 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:P 3 "reg_or_int_operand" "r,r,r,r,r,r,i,i,i,i,i,i")]
	    UNSPEC_ARCV_VMV_S_V)
	  (match_operand:<V_LMUL1> 1 "register_operand" "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0")))]
  "TARGET_XARCVVDSP"
  { return which_alternative < 6 ? "arcv.vmv.s.vx\t%0,%2,%3" : "arcv.vmv.s.vi\t%0,%2,%3"; }
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_VLSI:MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (const_int INVALID_ATTRIBUTE))
   (set (attr "ma") (const_int INVALID_ATTRIBUTE))
   (set (attr "avl_type_idx") (const_int 5))])

(define_insn "@pred_arcv_vnorm<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VNORM)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnorm.v\t%0,%3%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_vssabs<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSSABS)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vssabs.v\t%0,%3%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_vsneg<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSNEG)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsneg.v\t%0,%3%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_vclr<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")
	(match_operand:V_VLSI 4 "imm5_operand" "i,i,i,i,i,i,i,i,i,i,i,i")]
	  UNSPEC_ARCV_VCLR)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vclr.v.i\t%0,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_vsra<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSRA)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsra.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsra_scalar<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VSRA)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsra.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsrat<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSRAT)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsrat.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsrat_scalar<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VSRAT)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsrat.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsra_s<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSRA_S)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsra.s.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsra_s_scalar<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VSRA_S)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsra.s.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsra_2s<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSRA_2S)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsra.2s.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsra_2s_scalar<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VSRA_2S)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsra.2s.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_narrow_arcv_vnsra<mode>"
  [(set (match_operand:<V_DOUBLE_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_DOUBLE_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_DOUBLE_TRUNC>
	  (unspec:VWEXTI
	  [(match_operand:VWEXTI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	  (sign_extend:VWEXTI
	    (match_operand:<V_DOUBLE_TRUNC> 4 "vector_shift_operand" "0,0,0,0,vr,vr,vr,vr,vk,vk,vk,vk"))]
	  UNSPEC_ARCV_VNSRA))
	(match_operand:<V_DOUBLE_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.w%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_quad_narrow_arcv_vnsra<mode>"
  [(set (match_operand:<V_QUAD_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_QUAD_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_QUAD_TRUNC>
	  (unspec:VQEXTI
	  [(match_operand:VQEXTI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	  (sign_extend:VQEXTI
	    (match_operand:<V_QUAD_TRUNC> 4 "vector_shift_operand" "0,0,0,0,vr,vr,vr,vr,vk,vk,vk,vk"))]
	  UNSPEC_ARCV_VNSRA))
	(match_operand:<V_QUAD_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.q%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_narrow_arcv_vnsra_scalar<mode>"
  [(set (match_operand:<V_DOUBLE_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_DOUBLE_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_DOUBLE_TRUNC>
	  (unspec:VWEXTI
	  [(match_operand:VWEXTI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	  (match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VNSRA))
	(match_operand:<V_DOUBLE_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.w%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_quad_narrow_arcv_vnsra_scalar<mode>"
  [(set (match_operand:<V_QUAD_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_QUAD_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_QUAD_TRUNC>
	  (unspec:VQEXTI
	  [(match_operand:VQEXTI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	  (match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VNSRA))
	(match_operand:<V_QUAD_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.q%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_narrow_arcv_vnsra_s<mode>"
  [(set (match_operand:<V_DOUBLE_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_DOUBLE_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_DOUBLE_TRUNC>
	  (unspec:VWEXTI
	  [(match_operand:<V_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr")
	  (sign_extend:VWEXTI
	    (match_operand:<V_DOUBLE_TRUNC> 4 "vector_shift_operand" "vr,vr,vr,vr,vk,vk,vk,vk"))]
	  UNSPEC_ARCV_VNSRA_S))
	(match_operand:<V_DOUBLE_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.s.w%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_quad_narrow_arcv_vnsra_s<mode>"
  [(set (match_operand:<V_QUAD_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_QUAD_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_QUAD_TRUNC>
	  (unspec:VQEXTI
	  [(match_operand:<V_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr")
	  (sign_extend:VQEXTI
	    (match_operand:<V_QUAD_TRUNC> 4 "vector_shift_operand" "vr,vr,vr,vr,vk,vk,vk,vk"))]
	  UNSPEC_ARCV_VNSRA_S))
	(match_operand:<V_QUAD_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.s.q%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_narrow_arcv_vnsra_s_scalar<mode>"
  [(set (match_operand:<V_DOUBLE_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_DOUBLE_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_DOUBLE_TRUNC>
	  (unspec:VWEXTI
	  [(match_operand:<V_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	  (match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VNSRA_S))
	(match_operand:<V_DOUBLE_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.s.w%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_quad_narrow_arcv_vnsra_s_scalar<mode>"
  [(set (match_operand:<V_QUAD_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_QUAD_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_QUAD_TRUNC>
	  (unspec:VQEXTI
	  [(match_operand:<V_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	  (match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VNSRA_S))
	(match_operand:<V_QUAD_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.s.q%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_narrow_arcv_vnsra_2s<mode>"
  [(set (match_operand:<V_DOUBLE_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_DOUBLE_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_DOUBLE_TRUNC>
	  (unspec:VWEXTI
	  [(match_operand:<V_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr")
	  (sign_extend:VWEXTI
	    (match_operand:<V_DOUBLE_TRUNC> 4 "vector_shift_operand" "vr,vr,vr,vr,vk,vk,vk,vk"))]
	  UNSPEC_ARCV_VNSRA_2S))
	(match_operand:<V_DOUBLE_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.2s.w%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_quad_narrow_arcv_vnsra_2s<mode>"
  [(set (match_operand:<V_QUAD_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_QUAD_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_QUAD_TRUNC>
	  (unspec:VQEXTI
	  [(match_operand:<V_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr")
	  (sign_extend:VQEXTI
	    (match_operand:<V_QUAD_TRUNC> 4 "vector_shift_operand" "vr,vr,vr,vr,vk,vk,vk,vk"))]
	  UNSPEC_ARCV_VNSRA_2S))
	(match_operand:<V_QUAD_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.2s.q%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_narrow_arcv_vnsra_2s_scalar<mode>"
  [(set (match_operand:<V_DOUBLE_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_DOUBLE_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_DOUBLE_TRUNC>
	  (unspec:VWEXTI
	  [(match_operand:<V_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	  (match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VNSRA_2S))
	(match_operand:<V_DOUBLE_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.2s.w%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_quad_narrow_arcv_vnsra_2s_scalar<mode>"
  [(set (match_operand:<V_QUAD_TRUNC> 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:<V_QUAD_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(truncate:<V_QUAD_TRUNC>
	  (unspec:VQEXTI
	  [(match_operand:<V_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	  (match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VNSRA_2S))
	(match_operand:<V_QUAD_TRUNC> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vnsra.2s.q%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_widen_arcv_vwsra<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))]
	  UNSPEC_ARCV_VWSRA)
	(match_operand:VWEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vwsra.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwsra_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	  (match_operand 4 "pmode_reg_or_uimm5_operand" "r,r,r,r,r,r,K,K,K,K,K,K")]
	  UNSPEC_ARCV_VWSRA)
	(match_operand:VWEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vwsra.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsshift")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_arcv_vaddsub<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VADDSUB)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vaddsub.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsaddsub<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSADDSUB)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsaddsub.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vsaaddsub<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSAADDSUB)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsaaddsub.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vaalu")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_quad_widen_arcv_vqrdot<mode>"
  [(set (match_operand:<V_QEXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_QEXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_QEXT_LMUL1>
	[(match_operand:V_QRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_QRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_QEXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQRDOT)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vqrdot.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_quad_widen_arcv_vqrdot_2s<mode>"
  [(set (match_operand:<V_QEXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_QEXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_QEXT_LMUL1>
	[(match_operand:V_QRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_QRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_QEXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQRDOT_2S)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vqrdot.2s.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwsrdot_2s<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_EXT_LMUL1>
	[(match_operand:V_WRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_WRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSRDOT_2S)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsrdot.2s.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_quad_widen_arcv_vqrdotu<mode>"
  [(set (match_operand:<V_QEXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_QEXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_QEXT_LMUL1>
	[(match_operand:V_QRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_QRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_QEXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQRDOTU)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vqrdotu.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_quad_widen_arcv_vqrdotsu<mode>"
  [(set (match_operand:<V_QEXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_QEXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_QEXT_LMUL1>
	[(match_operand:V_QRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_QRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_QEXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQRDOTSU)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vqrdotsu.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwrdot<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_EXT_LMUL1>
	[(match_operand:V_WRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_WRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWRDOT)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwrdot.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_half_arcv_vwrdot<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<V_EXT_LMUL1>
	    [(match_operand:V_WRDOT_H 3 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr")
	     (sign_extend:<V_EXT_LMUL1>
	      (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWRDOT)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwrdot.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwsrdot<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_EXT_LMUL1>
	[(match_operand:V_WRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_WRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSRDOT)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsrdot.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwrdotu<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_EXT_LMUL1>
	[(match_operand:V_WRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_WRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWRDOTU)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwrdotu.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_half_arcv_vwrdotu<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<V_EXT_LMUL1>
	    [(match_operand:V_WRDOT_H 3 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr")
	     (sign_extend:<V_EXT_LMUL1>
	      (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWRDOTU)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwrdotu.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwrdotsu<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_EXT_LMUL1>
	[(match_operand:V_WRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_WRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWRDOTSU)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwrdotsu.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwsmac<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSMAC)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsmac.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwsmac_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(match_operand:<VSUBEL> 3 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSMAC)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsmac.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwsnmsac<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSNMSAC)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsnmsac.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwsnmsac_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(match_operand:<VSUBEL> 3 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSNMSAC)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsnmsac.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmul<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (sign_extend:VQEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))]
	  UNSPEC_ARCV_VWMUL)
	(match_operand:VQEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vwmul.h%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmul_scalar<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:<VSUBEL> 4 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")]
	  UNSPEC_ARCV_VWMUL)
	(match_operand:VQEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vwmul.h%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmac<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr"))
	     (sign_extend:VQEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWMAC)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwmac.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmac_scalar<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr"))
	     (match_operand:<VSUBEL> 3 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWMAC)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwmac.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmulu<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (sign_extend:VQEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))]
	  UNSPEC_ARCV_VWMULU)
	(match_operand:VQEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vwmulu.h%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmulu_scalar<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:<VSUBEL> 4 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")]
	  UNSPEC_ARCV_VWMULU)
	(match_operand:VQEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vwmulu.h%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmacu<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr"))
	     (sign_extend:VQEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWMACU)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwmacu.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmacu_scalar<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr"))
	     (match_operand:<VSUBEL> 3 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWMACU)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwmacu.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_half_arcv_vsmulf<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VWEXTI
	    [(sign_extend:VWEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSMULF)
	(match_operand:VWEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsmulf.h%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsmul")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_half_arcv_vsmulf_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VWEXTI
	    [(sign_extend:VWEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:<VEL> 4 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")]
	  UNSPEC_ARCV_VSMULF)
	(match_operand:VWEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vsmulf.h%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsmul")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_half_arcv_vwmulf<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (sign_extend:VQEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))]
	  UNSPEC_ARCV_VWMULF)
	(match_operand:VQEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vwmulf.h%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwmulf_scalar<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:<VSUBEL> 4 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")]
	  UNSPEC_ARCV_VWMULF)
	(match_operand:VQEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVDSP"
  "arcv.vwmulf.h%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwsmacf<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr"))
	     (sign_extend:VQEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSMACF)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsmacf.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwsmacf_scalar<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr"))
	     (match_operand:<VSUBEL> 3 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSMACF)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsmacf.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwsnmsacf<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr"))
	     (sign_extend:VQEXTI
	      (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSNMSACF)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsnmsacf.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwsnmsacf_scalar<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VQEXTI
	    [(sign_extend:VQEXTI
	      (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr"))
	     (match_operand:<VSUBEL> 3 "register_operand" "r,r,r,r,r,r,r,r,r,r,r,r")
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSNMSACF)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsnmsacf.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_half_arcv_vwsrdotf<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<V_EXT_LMUL1>
	    [(match_operand:V_WRDOT_H 3 "register_operand" "vr,vr,vr,vr,0,0,vr,vr,0,0,vr,vr")
	     (sign_extend:<V_EXT_LMUL1>
	      (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSRDOTF)
	(match_dup 2)))]
  "TARGET_XARCVVDSP"
  "arcv.vwsrdotf.h%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vconj<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VCONJ)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vconj.v\t%0,%3%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_vcmuli<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VCMULI)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vcmuli.v\t%0,%3%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_vcmulni<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VCMULNI)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vcmulni.v\t%0,%3%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_veven<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VEVEN)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.veven.v\t%0,%3%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_vodd<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VODD)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vodd.v\t%0,%3%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")
   (set_attr "vl_op_idx" "4")
   (set (attr "ta") (symbol_ref "riscv_vector::get_ta(operands[5])"))
   (set (attr "ma") (symbol_ref "riscv_vector::get_ma(operands[6])"))
   (set (attr "avl_type_idx") (const_int 7))])

(define_insn "@pred_arcv_vinterleave<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VINTERLEAVE)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vinterleave.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vscredsum<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSCREDSUM)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vscredsum.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwcredsum<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_EXT_LMUL1>
	[(match_operand:VI_QHS 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:<V_EXT_LMUL1> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VWCREDSUM)
	(match_operand:<V_EXT_LMUL1> 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vwcredsum.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vscmul<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSCMUL)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vscmul.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsmul")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vscmul_scalar<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=&vd, &vd, &vr, &vr, &vd, &vd, &vr, &vr, &vd, &vd, &vr, &vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:<V_LMUL1> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSCMUL_SCALAR)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vscmul.vs\t%0,%3,%4%p1"
  [(set_attr "type" "vsmul")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vscjmul<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_VLSI 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSCJMUL)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vscjmul.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "vsmul")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_arcv_vscjmul_scalar<mode>"
  [(set (match_operand:V_VLSI 0 "register_operand" "=&vd, &vd, &vr, &vr, &vd, &vd, &vr, &vr, &vd, &vd, &vr, &vr")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
		 (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:V_VLSI
	[(match_operand:V_VLSI 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:<V_LMUL1> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VSCJMUL_SCALAR)
	(match_operand:V_VLSI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vscjmul.vs\t%0,%3,%4%p1"
  [(set_attr "type" "vsmul")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwscmul<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))]
	  UNSPEC_ARCV_VWSCMUL)
	(match_operand:VWEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscmul.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscmul_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(match_operand:<V_DOUBLE_TRUNC_LMUL1> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VWSCMUL_SCALAR)
	(match_operand:VWEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscmul.vs\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscjmul<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))]
	  UNSPEC_ARCV_VWSCJMUL)
	(match_operand:VWEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscjmul.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscjmul_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr,&vd,&vd,&vr,&vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(match_operand:<V_DOUBLE_TRUNC_LMUL1> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")]
	  UNSPEC_ARCV_VWSCJMUL_SCALAR)
	(match_operand:VWEXTI 2 "vector_merge_operand"     "vu,0,vu,0,vu,0,vu,0,vu,0,vu,0")))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscjmul.vs\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscmac<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCMAC)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscmac.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscmac_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(match_operand:<V_DOUBLE_TRUNC_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCMAC_SCALAR)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscmac.vs\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscnmsac<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCNMSAC)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscnmsac.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscnmsac_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(match_operand:<V_DOUBLE_TRUNC_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCNMSAC_SCALAR)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscnmsac.vs\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscjmac<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCJMAC)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscjmac.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscjmac_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(match_operand:<V_DOUBLE_TRUNC_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCJMAC_SCALAR)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscjmac.vs\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscjnmsac<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCJNMSAC)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscjnmsac.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscjnmsac_scalar<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(match_operand:<V_DOUBLE_TRUNC_LMUL1> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCJNMSAC_SCALAR)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscjnmsac.vs\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwscrdot<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_EXT_LMUL1>
	[(match_operand:V_WRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_WRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCRDOT)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscrdot.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwscjrdot<mode>"
  [(set (match_operand:<V_EXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_EXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_EXT_LMUL1>
	[(match_operand:V_WRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_WRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_EXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSCJRDOT)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vwscjrdot.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_quad_widen_arcv_vqcrdot<mode>"
  [(set (match_operand:<V_QEXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_QEXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_QEXT_LMUL1>
	[(match_operand:V_QRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_QRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_QEXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQCRDOT)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vqcrdot.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_quad_widen_arcv_vqcjrdot<mode>"
  [(set (match_operand:<V_QEXT_LMUL1> 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:<V_QEXT_LMUL1>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:<V_QEXT_LMUL1>
	[(match_operand:V_QRDOT 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	(match_operand:V_QRDOT 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr")
	     (match_operand:<V_QEXT_LMUL1> 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQCJRDOT)
	(match_dup 2)))]
  "TARGET_XARCVVCPLX"
  "arcv.vqcjrdot.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_widen_arcv_vwsad<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSAD)
	(match_dup 2)))]
  "TARGET_XARCVVSAD"
  "arcv.vwsad.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_widen_arcv_vwsadu<mode>"
  [(set (match_operand:VWEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VWEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VWEXTI
	[(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VWEXTI
	  (match_operand:<V_DOUBLE_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VWEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VWSADU)
	(match_dup 2)))]
  "TARGET_XARCVVSAD"
  "arcv.vwsadu.v%o4\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_DOUBLE_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm4<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM4)
	(match_dup 2)))]
  "TARGET_XARCVMXMB"
  "arcv.vqmxm4.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm4u<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM4U)
	(match_dup 2)))]
  "TARGET_XARCVMXMB"
  "arcv.vqmxm4u.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm4su<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM4SU)
	(match_dup 2)))]
  "TARGET_XARCVMXMB"
  "arcv.vqmxm4su.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm8<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM8)
	(match_dup 2)))]
  "TARGET_XARCVMXMC"
  "arcv.vqmxm8.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm8u<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM8U)
	(match_dup 2)))]
  "TARGET_XARCVMXMC"
  "arcv.vqmxm8u.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm8su<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM8SU)
	(match_dup 2)))]
  "TARGET_XARCVMXMC"
  "arcv.vqmxm8su.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm16<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM16)
	(match_dup 2)))]
  "TARGET_XARCVMXMD"
  "arcv.vqmxm16.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm16u<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM16U)
	(match_dup 2)))]
  "TARGET_XARCVMXMD"
  "arcv.vqmxm16u.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

(define_insn "@pred_quad_widen_arcv_vqmxm16su<mode>"
  [(set (match_operand:VQEXTI 0 "register_operand" "=vd, vd, vr, vr, vd, vd, vr, vr, vd, vd, vr, vr")
	(if_then_else:VQEXTI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand" "vm, vm,Wc1, Wc1, vm, vm,Wc1,Wc1, vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"    "rK, rK, rK,  rK, rK, rK, rK, rK, rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"        " i,  i,  i,   i,  i,  i,  i,  i,  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	(unspec:VQEXTI
	[(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 3 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	(sign_extend:VQEXTI
	  (match_operand:<V_QUAD_TRUNC> 4 "register_operand" "vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr,vr"))
	     (match_operand:VQEXTI 2 "register_operand" "0,0,0,0,0,0,0,0,0,0,0,0")]
	  UNSPEC_ARCV_VQMXM16SU)
	(match_dup 2)))]
  "TARGET_XARCVMXMD"
  "arcv.vqmxm16su.v%o3\t%0,%3,%4%p1"
  [(set_attr "type" "viwmuladd")
   (set_attr "mode" "<V_QUAD_TRUNC>")])

;; Combine vadd + vsub to arcv.vaddsub.vv
(define_peephole2
  [(set (match_operand:V_VLSI 0 "register_operand")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand")
	     (match_operand 5 "vector_length_operand")
	     (match_operand 6 "const_int_operand")
	     (match_operand 7 "const_int_operand")
	     (match_operand 8 "const_int_operand")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (plus:V_VLSI
	    (match_operand:V_VLSI 3 "register_operand")
	    (match_operand:V_VLSI 4 "register_operand"))
	  (match_operand:V_VLSI 2 "vector_merge_operand")))
   (set (match_dup 3)
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_dup 1)
	     (match_dup 5)
	     (match_dup 6)
	     (match_dup 7)
	     (match_dup 8)
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (minus:V_VLSI
	    (match_dup 3)
	    (match_dup 4))
	  (match_operand:V_VLSI 13 "vector_merge_operand")))]
  "TARGET_XARCVVDSP"
  [(set (match_dup 0)
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_dup 1)
	     (match_dup 5)
	     (match_dup 6)
	     (match_dup 7)
	     (match_dup 8)
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:V_VLSI
	    [(match_dup 3)
	     (match_dup 4)]
	    UNSPEC_ARCV_VADDSUB)
	  (match_dup 2)))])

;; Combine vsadd + vssub to arcv.vsaddsub.vv
(define_peephole2
  [(set (match_operand:V_VLSI 0 "register_operand")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand")
	     (match_operand 5 "vector_length_operand")
	     (match_operand 6 "const_int_operand")
	     (match_operand 7 "const_int_operand")
	     (match_operand 8 "const_int_operand")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (ss_plus:V_VLSI
	    (match_operand:V_VLSI 3 "register_operand")
	    (match_operand:V_VLSI 4 "register_operand"))
	  (match_operand:V_VLSI 2 "vector_merge_operand")))
   (set (match_dup 3)
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_dup 1)
	     (match_dup 5)
	     (match_dup 6)
	     (match_dup 7)
	     (match_dup 8)
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (ss_minus:V_VLSI
	    (match_dup 3)
	    (match_dup 4))
	  (match_operand:V_VLSI 13 "vector_merge_operand")))]
  "TARGET_XARCVVDSP"
  [(set (match_dup 0)
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_dup 1)
	     (match_dup 5)
	     (match_dup 6)
	     (match_dup 7)
	     (match_dup 8)
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:V_VLSI
	    [(match_dup 3)
	     (match_dup 4)]
	    UNSPEC_ARCV_VSADDSUB)
	  (match_dup 2)))])

;; Combine vaadd + arcv.vsasub to arcv.vsaaddsub.vv
(define_peephole2
  [(set (match_operand:V_VLSI 0 "register_operand")
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand")
	     (match_operand 5 "vector_length_operand")
	     (match_operand 6 "const_int_operand")
	     (match_operand 7 "const_int_operand")
	     (match_operand 8 "const_int_operand")
	     (match_operand 9 "const_int_operand")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:V_VLSI
	    [(match_operand:V_VLSI 3 "register_operand")
	     (match_operand:V_VLSI 4 "register_operand")]
	    UNSPEC_VAADD)
	  (match_operand:V_VLSI 2 "vector_merge_operand")))
   (set (match_dup 3)
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_dup 1)
	     (match_dup 5)
	     (match_dup 6)
	     (match_dup 7)
	     (match_dup 8)
	     (match_dup 9)
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:V_VLSI
	    [(match_dup 3)
	     (match_dup 4)]
	    UNSPEC_ARCV_VSAADDSUB)
	  (match_operand:V_VLSI 13 "vector_merge_operand")))]
  "TARGET_XARCVVDSP"
  [(set (match_dup 0)
	(if_then_else:V_VLSI
	  (unspec:<VM>
	    [(match_dup 1)
	     (match_dup 5)
	     (match_dup 6)
	     (match_dup 7)
	     (match_dup 8)
	     (match_dup 9)
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI VXRM_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:V_VLSI
	    [(match_dup 3)
	     (match_dup 4)]
	    UNSPEC_ARCV_VSAADDSUB)
	  (match_dup 2)))])
