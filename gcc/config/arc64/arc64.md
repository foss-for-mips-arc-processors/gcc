;; Register numbers
(define_constants
  [
    (R0_REGNUM		0)
    (R1_REGNUM		1)
    (R2_REGNUM		2)
    (R3_REGNUM		3)
    (R4_REGNUM		4)
    (R5_REGNUM		5)
    (R6_REGNUM		6)
    (R7_REGNUM		7)
    (R8_REGNUM		8)
    (R9_REGNUM		9)
    (R10_REGNUM		10)
    (R11_REGNUM		11)
    (R12_REGNUM		12)
    (R13_REGNUM		13)
    (R14_REGNUM		14)
    (R15_REGNUM		15)
    (R16_REGNUM		16)
    (R17_REGNUM		17)
    (R18_REGNUM		18)
    (R19_REGNUM		19)
    (R20_REGNUM		20)
    (R21_REGNUM		21)
    (R22_REGNUM		22)
    (R23_REGNUM		23)
    (R24_REGNUM		24)
    (R25_REGNUM		25)
    (R26_REGNUM		26)
    (R27_REGNUM		27)
    (SP_REGNUM		28)
    (ILINK_REGNUM	29)
    (R30_REGNUM		30)
    (BLINK_REGNUM	31)
    (R32_REGNUM		32)
    (R33_REGNUM		33)
    (R34_REGNUM		34)
    (R35_REGNUM		35)
    (R36_REGNUM		36)
    (R37_REGNUM		37)
    (R38_REGNUM		38)
    (R39_REGNUM		39)
    (R40_REGNUM		40)
    (R41_REGNUM		41)
    (R42_REGNUM		42)
    (R43_REGNUM		43)
    (R44_REGNUM		44)
    (R45_REGNUM		45)
    (R46_REGNUM		46)
    (R47_REGNUM		47)
    (R48_REGNUM		48)
    (R49_REGNUM		49)
    (R50_REGNUM		50)
    (R51_REGNUM		51)
    (R52_REGNUM		52)
    (R53_REGNUM		53)
    (R54_REGNUM		54)
    (R55_REGNUM		55)
    (R56_REGNUM		56)
    (R57_REGNUM		57)
    (R58_REGNUM		58)
    (R59_REGNUM		59)

    (F0_REGNUM		64)
    (F1_REGNUM		65)
    (F2_REGNUM		66)
    (F3_REGNUM		67)
    (F4_REGNUM		68)
    (F5_REGNUM		69)
    (F6_REGNUM		70)
    (F7_REGNUM		71)
    (F8_REGNUM		72)
    (F9_REGNUM		73)
    (F10_REGNUM		74)
    (F11_REGNUM		75)
    (F12_REGNUM		76)
    (F13_REGNUM		77)
    (F14_REGNUM		78)
    (F15_REGNUM		79)
    (F16_REGNUM		80)
    (F17_REGNUM		81)
    (F18_REGNUM		82)
    (F19_REGNUM		83)
    (F20_REGNUM		84)
    (F21_REGNUM		85)
    (F22_REGNUM		86)
    (F23_REGNUM		87)
    (F24_REGNUM		88)
    (F25_REGNUM		89)
    (F26_REGNUM		90)
    (F27_REGNUM		91)
    (F28_REGNUM		92)
    (F29_REGNUM 	93)
    (F30_REGNUM		94)
    (F31_REGNUM 	95)

    (AP_REGNUM		96)
    (SFP_REGNUM		97)
    (CC_REGNUM		98)
  ]
  )

(define_c_enum "unspec"
  [
   ARC64_UNSPEC_PCREL
   ARC64_UNSPEC_GOT
   ARC64_UNSPEC_GOT32
   ARC64_UNSPEC_TLS_GD
   ARC64_UNSPEC_TLS_IE
   ARC64_UNSPEC_TLS_OFF
   ARC64_VUNSPEC_BLOCKAGE

   ARC64_VUNSPEC_LR
   ARC64_VUNSPEC_SR
   ARC64_VUNSPEC_LRL
   ARC64_VUNSPEC_SRL
   ARC64_VUNSPEC_FLAG
   ARC64_VUNSPEC_BRK
   ARC64_VUNSPEC_NOP
   ARC64_VUNSPEC_TRAP_S

   ARC64_VUNSPEC_EX
   ARC64_VUNSPEC_CAS
   ARC64_VUNSPEC_SC
   ARC64_VUNSPEC_LL
   ARC64_VUNSPEC_SYNC
   ARC64_VUNSPEC_ATOOPS

   ARC64_UNSPEC_MEMBAR
   ARC64_UNSPEC_FLS
   ARC64_UNSPEC_COPYSIGN
   ARC64_UNSPEC_XORSIGN
   ARC64_UNSPEC_ROUND
   ARC64_UNSPEC_BTRUNC
   ARC64_UNSPEC_CASESI
   ARC64_UNSPEC_VECINIT
   ARC64_UNSPEC_QMPYH
   ARC64_UNSPEC_QMACH
   ARC64_UNSPEC_DMPYWH
   ARC64_UNSPEC_VPACK4HL
   ARC64_UNSPEC_VPACK4HM
   ARC64_UNSPEC_VPACK2WL
   ARC64_UNSPEC_SWAPL
   ARC64_UNSPEC_SWAP
   ARC64_UNSPEC_VEC_SHR
   ARC64_UNSPEC_VEC_SHL
   ])

(include "constraints.md")
(include "predicates.md")

;; -------------------------------------------------------------------
;; Mode Iterators
;; -------------------------------------------------------------------

;; Iterator for General Purpose Integer registers (32- and 64-bit modes)
(define_mode_iterator GPI [SI DI])

;; Iterator for QI and HI modes
(define_mode_iterator SHORT [QI HI])

;; Iterator for QI HI and SI modes
(define_mode_iterator EXT [QI HI SI])

;; Iterator for all integer modes (up to 64-bit)
(define_mode_iterator ALLI [QI HI SI DI])

;; Iterator for HI SI and DI modes
(define_mode_iterator EPI [HI SI DI])

;; This mode iterator allows :P to be used for patterns that operate on
;; pointer-sized quantities.  Exactly one of the two alternatives will match.
(define_mode_iterator P [(SI "Pmode == SImode") (DI "Pmode == DImode")])

;; Iterator for General Purpose Floating-point registers (16 -, 32-
;; and 64-bit modes)
(define_mode_iterator GPF_HF [(HF "ARC64_HAS_FPUH")
			      (SF "ARC64_HAS_FPUS") (DF "ARC64_HAS_FPUD")])

;; Iterator for General Purpose Floating-point registers (32- and 64-bit modes)
(define_mode_iterator GPF [(SF "ARC64_HAS_FPUS") (DF "ARC64_HAS_FPUD")])

;; All int vectors
(define_mode_iterator VALL [V2HI V4HI V2SI])

;; All 64b int vectors
(define_mode_iterator V64I [V2HI V4HI V2SI])

;; All fp vectors
(define_mode_iterator VALLF [(V2HF "ARC64_VFP_32")
			     (V4HF "ARC64_VFP_64") (V2SF "ARC64_VFP_64")
			     (V8HF "ARC64_VFP_128") (V4SF "ARC64_VFP_128")
			     (V2DF "ARC64_VFP_128")])

;; ALl fp vectors up to 64bit
(define_mode_iterator VALLF_64 [(V2HF "ARC64_VFP_32")
				(V4HF "ARC64_VFP_64") (V2SF "ARC64_VFP_64")])

;; All 128b fp vectos
(define_mode_iterator VALLF_128 [(V8HF "ARC64_VFP_128") (V4SF "ARC64_VFP_128")
				 (V2DF "ARC64_VFP_128")])

;; All 2xfp Vectors
(define_mode_iterator V2xF [(V2HF "ARC64_VFP_32") (V2SF "ARC64_VFP_64")
			    (V2DF "ARC64_VFP_128")])

;; All 4xfp Vectors
(define_mode_iterator V4xF [(V4HF "ARC64_VFP_64") (V4SF "ARC64_VFP_128")])

;; All 2xreg wide vectors
;; All 2xfp Vectors
(define_mode_iterator W2xF [(V2DF "ARC64_VFP_128")])

;; -------------------------------------------------------------------
;; Code Iterators
;; -------------------------------------------------------------------

;; Code iterator for sign/zero extension
(define_code_iterator ANY_EXTEND [sign_extend zero_extend])

;; This code iterator allows the shifts supported in arithmetic instructions
(define_code_iterator ASHIFT [ashift ashiftrt lshiftrt])

;; Iterates over the SETcc instructions
(define_code_iterator SETCC [eq ne gt lt ge le ltu geu])
(define_code_iterator ALLCC [eq ne gt lt ge le ltu geu gtu leu])

;; Three operand arithmetic operations
(define_code_iterator ARITH [plus minus mult])

;; Three operand logic operations
(define_code_iterator LOGIC [and ior xor smin smax])

;; Two operand logic operations
(define_code_iterator LOGIC2 [not abs])

;; Two operand logic operations extended, used for zero_extend
;; patterns
(define_code_iterator LOP2EX [not abs neg])

;; Min/Max iterator
(define_code_iterator MINMAX [smin smax])

;; Three operand floating point arithmetic instructions
(define_code_iterator DOPF [plus minus mult div smin smax])

;; Vector operations
(define_code_iterator VOPS [plus minus mult div])

;; Comutative VF operations
(define_code_iterator VCOP [plus mult])

;; Emulated 2 operand vector operations
(define_code_iterator EV2OP [smin smax])

;; Emulated 1 operand vector operations
(define_code_iterator EV1OP [abs neg])

;; -------------------------------------------------------------------
;; Mode Attributes
;; -------------------------------------------------------------------

;; Map rtl mode to ARC mnemonic suffixes used in sign extend
;; instructions.
(define_mode_attr exttab [(QI "b") (HI "h") (SI "w")])

;; Map rtl mode to ARC mnemonic suffixes
(define_mode_attr sfxtab [(QI "b") (HI "h") (SI "") (DI "l")
			  (HF "h") (SF "s") (DF "d")
			  (V2HI "2h") (V4HI "4h") (V2SI "2")
			  (V2HF "h") (V4HF "h") (V2SF "s")
			  (V8HF "h") (V4SF "s") (V2DF "d")])

;; Used by FPABS patterns.
(define_mode_attr fptab [(SF "") (DF "l")])

;; Same as above but to be used by mov conditional
(define_mode_attr mcctab [(QI "") (HI "") (SI "") (DI "l")
			  (HF "") (SF "") (DF "l")
			  (V2HI "") (V4HI "l") (V2SI "l")
			  (V2HF "") (V4HF "l") (V2SF "l")])

(define_mode_attr slfp [(HF "h") (SF "") (DF "l")
			(V2HF "") (V4HF "l") (V2SF "l")])

(define_mode_attr fmvftab [(HF "s") (SF "s") (DF "d")
			   (V2HF "s") (V4HF "d") (V2SF "d")])
(define_mode_attr fmvitab [(HF "i") (SF "i") (DF "l")
			   (V2HF "i") (V4HF "l") (V2SF "l")])

;; Give the number of bits-1 in the mode
(define_mode_attr sizen [(QI "7") (HI "15") (SI "31") (DI "63")
			 (HF "15") (SF "31") (DF "63")])

;; Same like above but without -1 used for fp loads/stores
(define_mode_attr sizef [(HF "16") (SF "32") (DF "64")
			 (V2HF "32") (V4HF "64") (V2SF "64")
			 (V8HF "128") (V4SF "128") (V2DF "128")])

;; Used by float conv patterns.
(define_mode_attr f2tab [(SI "int") (DI "l")])

;; Define element mode for each vector mode.
(define_mode_attr VEL [(V2HI "HI") (V4HI "HI") (V2SI "SI")
		       (V2HF "HF") (V4HF "HF") (V2SF "SF")
		       (V8HF "HF") (V4SF "SF") (V2DF "DF")])
(define_mode_attr vel [(V2HI "hi") (V4HI "hi") (V2SI "si")
		       (V2HF "hf") (V4HF "hf") (V2SF "sf")
		       (V8HF "hf") (V4SF "sf") (V2DF "df")])

;; Used by vector extract pattern
(define_mode_attr vextrsz [(V2HI "16") (V4HI "16") (V2SI "32")])
(define_mode_attr vextrmsk [(V2HI "0x1f") (V4HI "0x3f") (V2SI "0x3f")])
(define_mode_attr vextrsh [(V2HI "5") (V4HI "6") (V2SI "6")])

;; -------------------------------------------------------------------
;; Code Attributes
;; -------------------------------------------------------------------
;; Map rtl objects to optab names
(define_code_attr optab [(ashift "ashl")
			 (ashiftrt "ashr")
			 (lshiftrt "lshr")
			 (rotatert "rotr")
			 (sign_extend "extend")
			 (zero_extend "zero_extend")
			 (sign_extract "extv")
			 (zero_extract "extzv")
			 (fix "fix")
			 (unsigned_fix "fixuns")
			 (float "float")
			 (unsigned_float "floatuns")
			 (popcount "popcount")
			 (and "and")
			 (ior "ior")
			 (xor "xor")
			 (not "one_cmpl")
			 (neg "neg")
			 (plus "add")
			 (minus "sub")
			 (mult "mul")
			 (div "div")
			 (udiv "udiv")
			 (mod "mod")
			 (umod "umod")
			 (ss_plus "qadd")
			 (us_plus "qadd")
			 (ss_minus "qsub")
			 (us_minus "qsub")
			 (ss_neg "qneg")
			 (ss_abs "qabs")
			 (smin "smin")
			 (smax "smax")
			 (umin "umin")
			 (umax "umax")
			 (eq "eq")
			 (ne "ne")
			 (lt "lt")
			 (ge "ge")
			 (le "le")
			 (gt "gt")
			 (ltu "ltu")
			 (leu "leu")
			 (geu "geu")
			 (gtu "gtu")
			 (abs "abs")
			 (sqrt "sqrt")])

;; map rtl to ARC's cc-mnemonic names, slightly different than above.
(define_code_attr cctab [(eq "eq")
			 (ne "ne")
			 (lt "lt")
			 (ge "ge")
			 (le "le")
			 (gt "gt")
			 (ltu "lo")
			 (leu "NA")
			 (geu "hs")
			 (gtu "NA")])

;; Sign- or zero-extend data-op
(define_code_attr su [(sign_extend "s") (zero_extend "u")])

;; Optab prefix for sign/zero-extending operations
(define_code_attr su_optab [(sign_extend "") (zero_extend "u")])

;; Map rtl objects to arc instuction names
(define_code_attr mntab [(abs "abs")
			 (not "not")
			 (neg "neg")
			 (ashift   "asl")
			 (ashiftrt "asr")
			 (sign_extend "sex")
			 (zero_extend "ext")
			 (div      "div")
			 (udiv     "divu")
			 (mult     "mul")
			 (mod      "rem")
			 (umod     "remu")
			 (lshiftrt "lsr")
			 (and      "and")
			 (ior      "or")
			 (xor      "xor")
			 (plus     "add")
			 (minus    "sub")
			 (smax      "max")
			 (smin      "min")])

;; -------------------------------------------------------------------
;; Int Iterators.
;; -------------------------------------------------------------------

;; -------------------------------------------------------------------
;; Instruction types and attributes
;; -------------------------------------------------------------------

;; What is the insn_cost for this insn?  The target hook can still override
;; this.  For optimizing for size the "length" attribute is used instead.
(define_attr "cost" "" (const_int 0))

(define_attr "type" "abs, adcl, add, addhl, addl, and, andl, asl,
asll, asr, asrl, atldop, atldlop, bclr, bic, bl, block, bmsk, branch,
branchcc, brk, bset, bsetl, btst, bxor, bxorl, compare, dbnz, dmb,
dmpywh, ex, div, divl, ext, fadd, fcmp, fsub, fmul, fdiv, fh2s, fmin,
fmax, fsgnj, fsgnjx, fsgnjn, fmadd, fmov, fmsub, fnmadd, fnmsub,
fsqrt, frnd, fs2d, fs2h, fd2s, int2fp, uint2fp, fp2int, fp2uint, ffs,
fls, flag, jl, jump, ld, llock, lsr, lsrl, lr, max, maxl, min, minl,
move, movecc, mod, modl, neg, nop, norm, normh, norml, mpy, mpyl, not,
notl, or, orl, return, ror,rol, sbcl, scond, setcc, sex, sr, st, sub,
subl, swap, swapl, swape, swapel, sync, trap, qmach, qmpyh, udiv,
udivl, umod, umodl, unknown, vadd, vsub, vmac2h, vmpy2h, vfadd, vfext,
vfins, vfsub, vfmul, vfdiv, vfrep, vpack, xbfu, xor, xorl"
  (const_string "unknown"))

(define_attr "iscompact" "yes,no,maybe" (const_string "no"))

(define_attr "predicable" "yes,no" (const_string "no"))

(define_attr "length" ""
  (cond
   [(eq_attr "iscompact" "yes")
    (const_int 2)

    (eq_attr "type" "ld")
    (if_then_else
     (match_operand 1 "limm_ldst_operand" "")
     (const_int 8) (const_int 4))

    (eq_attr "type" "st")
    (if_then_else
     (ior (match_operand 0 "limm_ldst_operand" "")
	  (and (not (match_operand 1 "S06S0_immediate_operand" ""))
	       (match_operand 1 "immediate_operand" "")))
     (const_int 8) (const_int 4))

    (eq_attr "iscompact" "maybe")
    (cond
     [(match_test "GET_CODE (PATTERN (insn)) == COND_EXEC")
      (const_int 4)

      (eq_attr "type" "and")
      (const_int 2)

      (eq_attr "type" "or")
      (const_int 2)

      (match_operand:DI 0 "" "")
      (const_int 4)
      ]
     (const_int 2))
    ]
   (const_int 8)))

;; Select various CPU features.
(define_attr "cpu_facility" "std,cd,ncd"
  (const_string "std"))

(define_attr "enabled" "no,yes"
  (cond [(and (eq_attr "cpu_facility" "cd")
	      (not (match_test ("TARGET_CODE_DENSITY"))))
	 (const_string "no")
	 (and (eq_attr "cpu_facility" "ncd")
	      (match_test ("TARGET_CODE_DENSITY")))
	 (const_string "no")
        ]
       (const_string "yes")))

;; -------------------------------------------------------------------
;; Pipeline descriptions and scheduling
;; -------------------------------------------------------------------

;; -------------------------------------------------------------------
;; Moves
;; -------------------------------------------------------------------

(define_expand "mov<mode>"
  [(set (match_operand:ALLI 0 "nonimmediate_operand")
	(match_operand:ALLI 1 "general_operand"))]
  ""
  "
  if (arc64_prepare_move_operands (operands[0], operands[1], <MODE>mode))
    DONE;
  "
  )

(define_expand "movti"
  [(set (match_operand:TI 0 "nonimmediate_operand")
	(match_operand:TI 1 "general_operand"))]
  "TARGET_WIDE_LDST"
  "
  if (arc64_prepare_move_operands (operands[0], operands[1], TImode))
    DONE;
  "
  )

;; We use movsf for soft and hard floats.
(define_expand "movsf"
  [(set (match_operand:SF 0 "nonimmediate_operand" "")
	(match_operand:SF 1 "general_operand"))]
  ""
  {
   if (arc64_prepare_move_operands (operands[0], operands[1], SFmode))
      DONE;
   })

(define_expand "movhf"
  [(set (match_operand:HF 0 "nonimmediate_operand" "")
	(match_operand:HF 1 "general_operand"))]
  "ARC64_HAS_FPUH"
  {
   if (arc64_prepare_move_operands (operands[0], operands[1], HFmode))
      DONE;
   })

(define_expand "movdf"
  [(set (match_operand:DF 0 "nonimmediate_operand" "")
	(match_operand:DF 1 "general_operand"))]
  "ARC64_HAS_FPUD"
  {
   if (arc64_prepare_move_operands (operands[0], operands[1], DFmode))
      DONE;
   })

;; mov<.f>        b, c
;; mov<.f>        b, s12
;; mov_s          b, u8
;; mov_s          g, h
;; mov_s          h, s3
;;
;; ld             a, [b, s9]
;; ld             a, [b,  c]
;; ld             a, [limm ]
;;
;; ldb_s          a, [b,  c]
;; ldb_s          c, [b,  u5]
;;
;; st<zz>         c   , [b , s9]
;; st<zz>         limm, [b , s9]
;; stb_s          b   , [sp, u7]
;; stb_s          c   , [b , u5]
(define_insn "*arc64_movqi"
  [(set
    (match_operand:QI 0 "arc64_dest_operand"   "=qh,    q, r,    q,Ustms,    m, Ucnst, r, m")
    (match_operand:QI 1 "general_operand" " qhS03MV,U08S0,ri,Uldms,    q,S06S0,     i, m, r"))
   ]
   ; in general, at least one of the operands must be a register
   "register_operand (operands[0], QImode)
   || register_operand (operands[1], QImode)
   /* this is to match 'stb w6, [limm]' (S06S0 is the w6).  */
   || (satisfies_constraint_S06S0 (operands[1])
       && memory_operand (operands[0], QImode))
   /* writing a byte into memory using limm variant.  */
   || (immediate_operand (operands[1], QImode)
       && memory_operand (operands[0], QImode))"
   "@
    mov_s\\t%0,%1
    mov_s\\t%0,%1
    mov\\t%0,%1
    ldb_s\\t%0,%1
    stb_s\\t%1,%0
    stb%U0\\t%1,%0
    stb%U0\\t%1,%0
    ldb%U1\\t%0,%1
    stb%U0\\t%1,%0"
   [(set_attr "type" "move,move,move,ld,st,st,st,ld,st")
    (set_attr "length" "2,2,4,2,2,*,8,*,*")]
)

(define_insn "*arc64_movhi"
  [(set
    (match_operand:HI 0 "arc64_dest_operand"  "=qh,r,    q,    r,h,r,   q,Ustms,    m,Ucnst, r, m")
    (match_operand:HI 1 "general_operand" "qhS03MV,r,U08S0,S12S0,i,i,Uldms,   q,S06S0,    i, m, r"))
   ]
  "register_operand (operands[0], HImode)
   || register_operand (operands[1], HImode)
   || (satisfies_constraint_S06S0 (operands[1])
       && memory_operand (operands[0], HImode))"
   "@
    mov_s\\t%0,%1
    mov\\t%0,%1
    mov_s\\t%0,%1
    mov\\t%0,%1
    mov_s\\t%0,%1
    mov\\t%0,%1
    ldh_s\\t%0,%1
    sth_s\\t%1,%0
    sth%U0\\t%1,%0
    sth%U0\\t%1,%0
    ldh%U1\\t%0,%1
    sth%U0\\t%1,%0"
   [(set_attr "type" "move,move,move,move,move,move,ld,st,st,st,ld,st")
    (set_attr "length" "2,4,2,4,6,8,2,2,*,8,*,*")]
)

(define_insn "*arc64_movsi"
  [(set
    (match_operand:SI 0 "arc64_dest_operand"  "=qh,r,    q,    r,h,r,    q,Ustms,    m,Ucnst, r, m")
    (match_operand:SI 1 "general_operand" "qhS03MV,r,U08S0,S12S0,i,i,Uldms,    q,S06S0,    i, m, r"))
   ]
  "register_operand (operands[0], SImode)
   || register_operand (operands[1], SImode)
   || (satisfies_constraint_S06S0 (operands[1])
       && memory_operand (operands[0], SImode))"
   "@
    mov_s\\t%0,%1
    mov\\t%0,%1
    mov_s\\t%0,%1
    mov\\t%0,%1
    mov_s\\t%0,%1
    mov\\t%0,%1
    ld_s\\t%0,%1
    st_s\\t%1,%0
    st%U0\\t%1,%0
    st%U0\\t%1,%0
    ld%U1\\t%0,%1
    st%U0\\t%1,%0"
   [(set_attr "type" "move,move,move,move,move,move,ld,st,st,st,ld,st")
    (set_attr "length" "2,4,2,4,6,8,2,2,*,8,*,*")]
)

(define_insn "*mov<mode>_cmp0"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN (match_operand:ALLI 1 "register_operand" "r")
		       (const_int 0)))
   (set (match_operand:ALLI 0 "register_operand" "=r") (match_dup 1))]
  ""
  "mov<mcctab>.f\\t%0,%1"
  [(set_attr "type" "move")
   (set_attr "length" "4")])

;; Softcore float move.
(define_insn "*movsf_softfp"
   [(set (match_operand:SF 0 "arc64_dest_operand" "=qh,r,qh,r,    q,Ustms,r,m")
	 (match_operand:SF 1 "general_operand"    "qhZ,r, E,E,Uldms,    q,m,r"))
   ]
   "!ARC64_HAS_FP_BASE
   && (register_operand (operands[0], SFmode)
       || register_operand (operands[1], SFmode))"
   "@
    mov_s\\t%0,%1
    mov\\t%0,%1
    mov_s\\t%0,%1
    mov\\t%0,%1
    ld_s\\t%0,%1
    st_s\\t%1,%0
    ld%U1\\t%0,%1
    st%U0\\t%1,%0"
   [(set_attr "type" "move,move,move,move,ld,st,ld,st")
    (set_attr "length" "2,4,6,8,2,2,*,*")])

;; For a fp move I use FSMOV.<cc> instruction. However, we can also
;; use FSSGNJ.
;; FIXME! add short instruction selection
(define_insn "*mov<mode>_hardfp"
  [(set (match_operand:GPF_HF 0 "arc64_dest_operand" "=w,    w,Ufpms,*r,*w,*r,*r,*r,*m")
	(match_operand:GPF_HF 1 "arc64_movf_operand"     "w,Ufpms,    w,*w,*r,*r,*G,*m,*r"))]
  "ARC64_HAS_FP_BASE
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
  "@
   f<sfxtab>mov\\t%0,%1
   fld<sizef>%U1\\t%0,%1
   fst<sizef>%U0\\t%1,%0
   fmv<fmvftab>2<fmvitab>\\t%0,%1
   fmv<fmvitab>2<fmvftab>\\t%0,%1
   mov<mcctab>\\t%0,%1
   mov<mcctab>\\t%0,%1
   ld<slfp>%U1\\t%0,%1
   st<slfp>%U0\\t%1,%0"
  [(set_attr "type" "fmov,ld,st,move,move,move,move,ld,st")
   (set_attr "length" "4,*,*,4,4,4,8,*,*")])

(define_insn "*arc64_push"
  [(set (mem:DI (pre_dec (reg:DI SP_REGNUM)))
	(                 match_operand:DI 0 "register_operand" "qr"))]
   ""
   "pushl_s\\t%0"
   [(set_attr "type" "st")
    (set_attr "length" "2")])

(define_insn "*arc64_pop"
  [(set (                  match_operand:DI 0 "register_operand" "=qr")
	(mem:DI (post_inc (reg:DI SP_REGNUM))))]
  ""
  "popl_s\\t%0"
  [(set_attr "type" "ld")
   (set_attr "length" "2")])

;; move 128bit
(define_insn_and_split "*arc64_movti"
  [(set (match_operand:TI 0 "arc64_dest_operand"  "=r,r,m")
	(match_operand:TI 1 "nonimmediate_operand" "r,m,r"))]
  "TARGET_WIDE_LDST
   && (register_operand (operands[0], TImode)
       || register_operand (operands[1], TImode))"
  "@
   #
   lddl%U1\\t%0,%1
   stdl%U0\\t%1,%0"
   "&& reload_completed
    && arc64_simd64x_split_move_p (operands, TImode)"
   [(const_int 0)]
   {
    arc64_simd128_split_move (operands, TImode);
    DONE;
   }
  [(set_attr "type" "move,ld,st")
   (set_attr "length" "8,*,*")])
;;
;; Short insns: movl_s g,h; movl_s b,u8
;; Long insns: movl, stl, ldl
;;
(define_insn "*arc64_movdi"
   [(set (match_operand:DI 0 "arc64_dest_operand" "=qh,    q,r,    r,         r,    r,r, m")
	 (match_operand:DI 1 "arc64_movl_operand"  "qh,U08S0,r,S12S0,S32S0SymMV,SyPic,m, r"))]
   "register_operand (operands[0], DImode)
    || register_operand (operands[1], DImode)"
   "@
    movl_s\\t%0,%1
    movl_s\\t%0,%1
    movl\\t%0,%1
    movl\\t%0,%1
    movl\\t%0,%1
    addl\\t%0,pcl,%1
    ldl%U1\\t%0,%1
    stl%U0\\t%1,%0"
   [(set_attr "type" "move,move,move,move,move,addl,ld,st")
    (set_attr "length" "2,2,4,4,8,8,*,*")]
)

;; Hi/Low moves for constant and symbol loading.

(define_insn "*movdi_high"
  [(set (match_operand:DI 0 "register_operand"   "=   r,   qh,    r,r")
	(high:DI
	 (match_operand:DI 1 "arc64_immediate_or_pic" "S12S0,SymIm,SymIm,SyPic")))]
  ""
  "@
   movhl\\t%0,%h1
   movhl_s\\t%0,%h1
   movhl\\t%0,%h1
   addhl\\t%0,pcl,%h1"
  [(set_attr "type" "move")
   (set_attr "length" "4,6,8,8")])

;; The immediates are already trimmed to fit the 32 bit limm field.
(define_insn "*movdi_high"
  [(set (match_operand:DI 0 "register_operand"            "=     r,   qh,    r")
	(ashift:DI (match_operand:DI 1 "nonmemory_operand" "rS12S0,S32S0,S32S0")
		   (const_int 32)))]
  ""
  "@
   movhl\\t%0,%1
   movhl_s\\t%0,%1
   movhl\\t%0,%1"
  [(set_attr "type" "move")
   (set_attr "length" "4,6,8")])

;; N.B. All immediates needs to be unsiged to endup at most in u32.
(define_insn "*movdi_lo_sum_iori"
  [(set (match_operand:DI 0 "register_operand"            "=q,    r,    h,    r")
	(lo_sum:DI (match_operand:DI 1 "register_operand"  "0,    0,    0,    r")
		   (match_operand:DI 2 "immediate_operand" "q,U10S0,SymIm,SymIm")))]
  ""
  "@
   orl%?\\t%0,%1,%2
   orl%?\\t%0,%1,%L2
   orl%?\\t%0,%1,%L2
   orl%?\\t%0,%1,%L2"
  [(set_attr "type" "or")
   (set_attr "iscompact" "yes,no,yes,no")
   (set_attr "length" "2,4,6,8")])

(define_insn "*adddi_high"
  [(set (match_operand:DI 0 "register_operand"          "=    qh,    r,    r,r,     r")
	(plus:DI (match_operand:DI 1 "register_operand"   "    0,    0,    r,r,     r")
		 (high:DI
		  (match_operand:DI 2 "nonmemory_operand" "S32S0,S12S0,U06S0,r,S32S0"))))]
  ""
  "@
   addhl_s\\t%0,%1,%2
   addhl\\t%0,%1,%2
   addhl\\t%0,%1,%2
   addhl\\t%0,%1,%2
   addhl\\t%0,%1,%2"
  [(set_attr "type" "addhl")
   (set_attr "iscompact" "yes,no,no,no,no")
   (set_attr "length" "6,4,4,4,8")])

; conditional execution patterns
(define_insn "*mov<mode>_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 2 "cc_register" "") (const_int 0)])
   (set (match_operand:ALLI 0 "register_operand"  "=    r,r")
	(match_operand:ALLI 1 "nonmemory_operand" "rU06S0,S32S0")))]
  ""
  "mov<mcctab>.%m3\\t%0,%1"
  [(set_attr "type" "move")
   (set_attr "length" "4,8")])

(define_insn "*mov<mode>_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 2 "cc_register" "") (const_int 0)])
   (set (match_operand:GPF_HF 0 "register_operand"  "=w,*r,*r")
	(match_operand:GPF_HF 1 "nonmemory_operand"  "w,*r,*E")))]
  ""
  "@
  f<sfxtab>mov.%m3\\t%0,%1
  mov<mcctab>.%m3\\t%0,%1
  mov<mcctab>.%m3\\t%0,%1"
  [(set_attr "type" "fmov,move,move")
   (set_attr "length" "4,4,8")])

;; -------------------------------------------------------------------
;; Subroutine calls and sibcalls
;; -------------------------------------------------------------------

(define_expand "call"
  [(parallel [(call (match_operand 0 "memory_operand")
		    (match_operand 1 "general_operand"))
	      (use (match_operand 2 "" ""))
	     (clobber (reg:DI BLINK_REGNUM))])]
  ""
  {
   arc64_expand_call (NULL_RTX, operands[0], false);
   DONE;
  }
)

(define_insn "*call_insn"
  [(call (mem:DI (match_operand:DI 0 "arc64_call_insn_operand" "q,r,BLsym,S12S0,S32S0"))
	 (match_operand 1 "" ""))
   (clobber (reg:DI BLINK_REGNUM))]
  ""
  "@
   jl_s\\t[%0]
   jl\\t[%0]
   bl\\t%C0
   jl\\t%0
   jl\\t%0"
  [(set_attr "type" "jl,jl,bl,jl,jl")
   (set_attr "length" "2,4,4,4,8")])

(define_expand "call_value"
  [(parallel [(set (match_operand 0 "" "")
		   (call (match_operand 1 "memory_operand")
			 (match_operand 2 "general_operand")))
	      (use (match_operand 3 "" ""))
	      (clobber (reg:DI BLINK_REGNUM))])]
  ""
  "
  {
    arc64_expand_call (operands[0], operands[1], false);
    DONE;
  }"
)

(define_insn "*call_value_insn"
  [(set (match_operand 0 "" "")
	(call (mem:DI (match_operand:DI 1 "arc64_call_insn_operand"
					"q,r,BLsym,S12S0,S32S0"))
	      (match_operand 2 "" "")))
   (clobber (reg:DI BLINK_REGNUM))]
  ""
  "@
   jl_s\\t[%1]
   jl\\t[%1]
   bl\\t%C1
   jl\\t%1
   jl\\t%1"
  [(set_attr "type" "jl,jl,bl,jl,jl")
   (set_attr "length" "2,4,4,4,8")])

(define_expand "sibcall"
  [(parallel [(call (match_operand 0 "memory_operand")
		    (match_operand 1 "general_operand"))
	      (return)
	      (use (match_operand 2 "" ""))])]
  ""
  {
    arc64_expand_call (NULL_RTX, operands[0], true);
    DONE;
  }
  )

(define_expand "sibcall_value"
  [(parallel [(set (match_operand 0 "" "")
		   (call (match_operand 1 "memory_operand")
			 (match_operand 2 "general_operand")))
	      (return)
	      (use (match_operand 3 "" ""))])]
  ""
  {
    arc64_expand_call (operands[0], operands[1], true);
    DONE;
  }
)

;FIXME! add short variant for jump
(define_insn "*sibcall_insn"
  [(call
    (mem:DI
     (match_operand:DI 0 "arc64_call_insn_operand" "Sbreg,BLsym,S12S0,S32S0"))
    (match_operand 1 "" ""))
  (return)]
  "SIBLING_CALL_P (insn)"
  "@
   j\\t[%0]
   b\\t%C0
   j\\t%0
   j\\t%0"
  [(set_attr "type" "jump,branch,jump,jump")
   (set_attr "length" "4,4,4,8")]
)

;FIXME! add short variant for jump
(define_insn "*sibcall_value_insn"
 [(set (match_operand 0 "" "")
       (call
	(mem:DI
	 (match_operand:DI 1 "arc64_call_insn_operand" "Sbreg,BLsym,S12S0,S32S0"))
	(match_operand 2 "" "")))
  (return)]
  "SIBLING_CALL_P (insn)"
  "@
   j\\t[%1]
   b\\t%C1
   j\\t%1
   j\\t%1"
  [(set_attr "type" "jump,branch,jump,jump")
   (set_attr "length" "4,4,4,8")]
)

; conditional execution patterns
(define_insn "*call_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 2 "cc_register" "") (const_int 0)])
    (parallel
     [(call (mem:DI
	     (match_operand:DI 0 "arc64_call_insn_operand" "r,BLsym,U06S0"))
	    (match_operand 1 "" ""))
      (clobber (reg:DI BLINK_REGNUM))]))]
  "(arc64_cmodel_var == ARC64_CMODEL_SMALL)
    || register_operand (operands[0], Pmode)"
  "@
   jl%m3\\t[%0]
   bl%m3\\t%C0
   jl%m3\\t%0"
  [(set_attr "type" "jl,bl,jl")
   (set_attr "length" "4")])

(define_insn "*callv_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 4 "cc_register" "") (const_int 0)])
    (parallel
     [(set (match_operand 0 "" "")
	   (call (mem:DI (match_operand:DI 1 "arc64_call_insn_operand"
					   "r,BLsym,U06S0"))
		 (match_operand 2 "" "")))
      (clobber (reg:DI BLINK_REGNUM))]))]
  "(arc64_cmodel_var == ARC64_CMODEL_SMALL)
    || register_operand (operands[1], Pmode)"
  "@
   jl%m3\\t[%1]
   bl%m3\\t%C1
   jl%m3\\t%1"
  [(set_attr "type" "jl,bl,jl")
   (set_attr "length" "4")])

(define_insn "*sibcall_insn_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 2 "cc_register" "") (const_int 0)])
    (parallel
     [(call (mem:DI
	     (match_operand:DI 0 "arc64_call_insn_operand" "Sbreg,BLsym,U06S0"))
	    (match_operand 1 "" ""))
      (return)]))]
  "SIBLING_CALL_P (insn)
   && ((arc64_cmodel_var == ARC64_CMODEL_SMALL)
       || register_operand (operands[0], Pmode))"
  "@
   j%m3\\t[%0]
   b%m3\\t%C0
   j%m3\\t%0"
  [(set_attr "type" "jump,branch,jump")
   (set_attr "length" "4")])

(define_insn "*sibcall_value_insn_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 4 "cc_register" "") (const_int 0)])
    (parallel
     [(set (match_operand 0 "" "")
	   (call
	    (mem:DI
	     (match_operand:DI 1 "arc64_call_insn_operand" "Sbreg,BLsym,U06S0"))
	    (match_operand 2 "" "")))
      (return)]))]
  "SIBLING_CALL_P (insn)
   && ((arc64_cmodel_var == ARC64_CMODEL_SMALL)
       || register_operand (operands[1], Pmode))"
  "@
   j%m3\\t[%1]
   b%m3\\t%C1
   j%m3\\t%1"
  [(set_attr "type" "jump,branch,jump")
   (set_attr "length" "4")])

(define_expand "untyped_call"
  [(parallel [(call (match_operand 0 "")
		    (const_int 0))
	      (match_operand 1 "")
	      (match_operand 2 "")])]
  ""
{
  int i;

  emit_call_insn (gen_call (operands[0], const0_rtx, const0_rtx));

  for (i = 0; i < XVECLEN (operands[2], 0); i++)
    {
      rtx set = XVECEXP (operands[2], 0, i);
      emit_move_insn (SET_DEST (set), SET_SRC (set));
    }

  emit_insn (gen_blockage ());
  DONE;
})

;; -------------------------------------------------------------------
;; Jumps and other miscellaneous insns
;; -------------------------------------------------------------------

(define_expand "indirect_jump"
  [(set (pc) (match_operand 0 "register_operand"))]
  ""
{
  operands[0] = force_reg (Pmode, operands[0]);
  if (Pmode == SImode)
    emit_jump_insn (gen_indirect_jumpsi (operands[0]));
  else
    emit_jump_insn (gen_indirect_jumpdi (operands[0]));
  DONE;
})

(define_insn "indirect_jump<mode>"
  [(set (pc) (match_operand:P 0 "register_operand" "q,r"))]
  ""
  "j%?\\t[%0]"
  [(set_attr "type" "jump")
   (set_attr "length" "2,4")]
)

(define_insn "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  "b%?\\t%l0"
  [(set_attr "type" "branch")
   (set (attr "length")
	(if_then_else
	 (and (ge (minus (match_dup 0) (pc)) (const_int -512))
	      (le (minus (match_dup 0) (pc)) (const_int 506)))
	 (const_int 2)
	 (const_int 4)))]
)

(define_expand "cbranch<mode>4"
  [(set (pc) (if_then_else
	      (match_operator 0 "arc64_comparison_operator"
			      [(match_operand:GPI 1 "nonmemory_operand")
			       (match_operand:GPI 2 "nonmemory_operand")])
	      (label_ref (match_operand 3 "" ""))
	      (pc)))]
  ""
  "
  operands[1] = arc64_gen_compare_reg (GET_CODE (operands[0]), operands[1],
					 operands[2]);
  operands[2] = const0_rtx;
  "
  )

(define_expand "cbranch<mode>4"
  [(set (pc) (if_then_else (match_operator 0 "arc64_comparison_operator"
			    [(match_operand:GPF_HF 1 "register_operand")
			     (match_operand:GPF_HF 2 "register_operand")])
			   (label_ref (match_operand 3 "" ""))
			   (pc)))]
  "ARC64_HAS_FP_BASE"
  "
  operands[1] = arc64_gen_compare_reg (GET_CODE (operands[0]), operands[1],
					 operands[2]);
  operands[2] = const0_rtx;
  "
)


(define_insn "condjump"
  [(set (pc) (if_then_else
	      (match_operator 0 "arc64_comparison_operator"
			      [(match_operand 1 "cc_register" "")
			       (const_int 0)])
	      (label_ref (match_operand 2 "" ""))
	      (pc)))]
  ""
  "b%m0%?\\t%l2"
  [(set_attr "type" "branchcc")
   (set (attr "length")
	(cond
	  [(and (match_operand 0 "equality_comparison_operator" "")
		(and (ge (minus (match_dup 2) (pc)) (const_int -512))
		     (le (minus (match_dup 2) (pc)) (const_int 506))))
	   (const_int 2)

	   (and (match_operand 0 "ccmode_comparison_operator" "")
		(and (ge (minus (match_dup 2) (pc)) (const_int -60))
		     (le (minus (match_dup 2) (pc)) (const_int 58))))
	   (const_int 2)]
	  (const_int 4)))])

(define_expand "prologue"
  [(clobber (const_int 0))]
  ""
  "
  arc64_expand_prologue ();
  DONE;
  "
)

(define_expand "epilogue"
  [(clobber (const_int 0))]
  ""
  "
  arc64_expand_epilogue (false);
  DONE;
  "
)

(define_expand "sibcall_epilogue"
  [(clobber (const_int 0))]
  ""
  "
  arc64_expand_epilogue (true);
  DONE;
  "
)

(define_expand "return"
  [(simple_return)]
  "arc64_can_use_return_insn_p ()"
  "")

(define_insn "simple_return"
  [(simple_return)]
  ""
  "j_s\\t[blink]"
  [(set_attr "type" "return")
   (set_attr "length" "2")])

(define_insn "trap_s"
  [(unspec_volatile [(match_operand:SI 0 "immediate_operand" "U06S0")]
		   ARC64_VUNSPEC_TRAP_S)]
  ""
  "trap_s\\t%0"
  [(set_attr "length" "2")
  (set_attr "type" "trap")])

(define_insn "nop"
  [(const_int 0)]
  ""
  "nop_s"
  [(set_attr "type" "nop")
   (set_attr "length" "2")])

(define_insn "blockage"
  [(unspec_volatile [(const_int 0)] ARC64_VUNSPEC_BLOCKAGE)]
  ""
  ""
  [(set_attr "length" "0")
   (set_attr "type" "block")]
  )

;; Don't need initialization instructions.
(define_expand "doloop_begin"
 [(use (match_operand 0 "" ""))        ; loop pseudo
  (use (match_operand 1 "" ""))]       ; doloop_end pattern
  ""
  {
    FAIL;
  }
)

; operand 0 is the loop count pseudo register
; operand 1 is the label to jump to at the top of the loop
(define_expand "doloop_end"
  [(parallel [(set (pc)
		   (if_then_else
		    (ne (match_operand:DI 0 "" "")
			(const_int 1))
		    (label_ref (match_operand 1 "" ""))
		    (pc)))
	      (set (match_dup 0) (plus:DI (match_dup 0) (const_int -1)))
	      (clobber (match_dup 2))])]
  ""
  {
   machine_mode mode = GET_MODE (operands[0]);
   if (mode != DImode)
     FAIL;
   operands[2] = gen_rtx_SCRATCH (mode);
  })

(define_insn_and_split "dbnz"
  [(set (pc)
	(if_then_else
	 (ne (match_operand:DI 0 "nonimmediate_operand" "+r,!m")
	     (const_int 1))
	 (label_ref (match_operand 1 "" ""))
	 (pc)))
   (set (match_dup 0)
	(plus:DI (match_dup 0)
		 (const_int -1)))
   (clobber (match_scratch:DI 2 "=X,r"))]
  ""
  "@
   dbnz\\t%0,%l1
   #"
  "reload_completed && memory_operand (operands[0], DImode)"
  [(set (match_dup 2) (match_dup 0))
   (parallel
    [(set (reg:CC_ZN CC_REGNUM)
	  (compare:CC_ZN (plus:DI (match_dup 2) (const_int -1))
			 (const_int 0)))
     (set (match_dup 2) (plus:DI (match_dup 2) (const_int -1)))])
   (set (match_dup 0) (match_dup 2))
   (set (pc) (if_then_else (ne (reg:CC_ZN CC_REGNUM)
			       (const_int 0))
			   (label_ref (match_dup 1))
			   (pc)))]
  ""
  [(set_attr "iscompact" "no")
   (set_attr "type" "dbnz")
   (set_attr "length" "4,20")])

; conditional execution
(define_insn "*returnt_ce"
  [(set (pc)
	(if_then_else (match_operator 0 "arc64_comparison_operator"
				      [(reg CC_REGNUM) (const_int 0)])
		      (simple_return) (pc)))]
  ""
  "j%m0\\t[blink]"
  [(set_attr "type" "return")
   (set_attr "length" "4")])

; Jump tables
(define_expand "casesi"
  [(match_operand:SI 0 "register_operand" "")  ; Index
   (match_operand:SI 1 "const_int_operand" "")    ; Lower bound
   (match_operand:SI 2 "const_int_operand" "")    ; Total range
   (match_operand 3 "" "")             ; Table label
   (match_operand 4 "" "")]            ; Out of range label
  ""
 {
   arc64_expand_casesi (operands);
   DONE;
   })

(define_insn "casesi_dispatch"
  [(set (pc)
       (unspec:DI [(match_operand:SI 0 "register_operand" "r,q,r")
                   (label_ref (match_operand 1 "" ""))
                   (const_int 0)]
                  ARC64_UNSPEC_CASESI))]
  ""
  "@
  bi\\t[%0]
  j_s\\t[%0]
  j\\t[%0]"
  [(set_attr "type" "jump")
   (set_attr "length" "4,2,4")
   (set_attr "cpu_facility" "cd,ncd,ncd")])

(define_insn "casesi_addaddr"
  [(set (match_operand:SI 0 "register_operand" "=r")
       (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                   (label_ref (match_operand 2 "" ""))
                   (const_int 1)]
                  ARC64_UNSPEC_CASESI))]
  ""
  "add2\\t%0,%l2,%1"
  [(set_attr "type" "add")
   (set_attr "length" "8")])

(define_insn "casesi_addaddrdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
       (unspec:DI [(match_operand:SI 1 "register_operand" "r")
                   (match_operand:DI 2 "register_operand" "r")
                   (const_int 2)]
                  ARC64_UNSPEC_CASESI))]
  ""
  "add2l\\t%0,%2,%1"
  [(set_attr "type" "addl")
   (set_attr "length" "4")])

(define_insn "casesi_dispatchdi"
  [(set (pc) (match_operand:DI 0 "register_operand" "q,r"))
   (use (label_ref (match_operand 1 "" "")))]
  ""
  "j%?\\t[%0]"
  [(set_attr "type" "jump")
   (set_attr "length" "2,4")])

;; -------------------------------------------------------------------
;; Sign/Zero extension
;; -------------------------------------------------------------------

(define_expand "<optab>sidi2"
  [(set (match_operand:DI 0 "register_operand")
	(ANY_EXTEND:DI (match_operand:SI 1 "nonimmediate_operand")))]
  ""
)

(define_expand "<ANY_EXTEND:optab><SHORT:mode><GPI:mode>2"
  [(set (match_operand:GPI 0 "register_operand")
	(ANY_EXTEND:GPI (match_operand:SHORT 1 "nonimmediate_operand")))]
  ""
)

;; TODO: Commented out this to fix issues in dejagnu.
;;       NEEDS TO BE VERIFIED LATER ON.
;; (define_expand "<optab>qihi2"
;;   [(set (match_operand:HI 0 "register_operand")
;; 	(ANY_EXTEND:HI (match_operand:QI 1 "nonimmediate_operand")))]
;;   ""
;; )

(define_insn "*zero_extend<mode>si2"
  [(set (match_operand:SI 0 "register_operand"        "=q,r,    q,r")
	(zero_extend:SI
	 (match_operand:SHORT 1 "nonimmediate_operand" "q,r,Uldms,m")))]
   ""
   "@
   ext<exttab>_s\\t%0,%1
   ext<exttab>\\t%0,%1
   ld<sfxtab>_s\\t%0,%1
   ld<sfxtab>%U1\\t%0,%1"
  [(set_attr "type" "sex,sex,ld,ld")
   (set_attr "length" "2,4,2,*")])

(define_insn "*zero_extend<mode>di2"
  [(set (match_operand:DI 0 "register_operand"      "=r,    q,r")
	(zero_extend:DI
	 (match_operand:EXT 1 "nonimmediate_operand" "r,Uldms,m")))]
   ""
   "@
   bmskl\\t%0,%1,<sizen>
   ld<sfxtab>_s\\t%0,%1
   ld<sfxtab>%U1\\t%0,%1"
  [(set_attr "type" "and,ld,ld")
   (set_attr "length" "4,2,*")]
)

;; conditional execution for the above two patterns
(define_insn "*zero_extend<SHORT:mode><GPI:mode>2_ce"
  [(cond_exec
    (match_operator 2 "arc64_comparison_operator"
		    [(match_operand 3 "cc_register" "") (const_int 0)])
    (set (match_operand:GPI 0"register_operand" "=r")
	 (zero_extend:GPI (match_operand:SHORT 1 "register_operand" "0"))))]
  ""
  "bmsk<GPI:mcctab>.%m2\\t%0,%1,<SHORT:sizen>"
  [(set_attr "type" "and")
   (set_attr "length" "4")])

(define_insn "*sign_extend<mode>di2"
  [(set (match_operand:DI 0 "register_operand"       "=r,r")
	(sign_extend:DI
	 (match_operand:EXT 1 "nonimmediate_operand"  "r,m")))]
   ""
   "@
   sex<exttab>l\\t%0,%1
   ld<sfxtab>.x%U1\\t%0,%1"
   [(set_attr "type" "sex,ld")
    (set_attr "length" "4,*")])

(define_insn "*sign_extend<mode>si2"
  [(set (match_operand:SI 0 "register_operand" "=q,r,r")
	(sign_extend:SI
	 (match_operand:SHORT 1 "nonimmediate_operand" "q,r,m")))]
  ""
  "@
  sex<exttab>_s\\t%0,%1
  sex<exttab>\\t%0,%1
  ld<sfxtab>.x%U1\\t%0,%1"
  [(set_attr "type" "sex,sex,ld")
   (set_attr "length" "2,4,8")])

;; -------------------------------------------------------------------
;; Simple arithmetic
;; -------------------------------------------------------------------

(define_expand "<optab>di3"
  [(set (match_operand:DI 0 "register_operand")
	(ARITH:DI (match_operand:DI 1 "register_operand")
		  (match_operand:DI 2 "nonmemory_operand")))]
  ""
  {
   if (!register_operand (operands[2], DImode))
      operands[2] = force_reg (DImode, operands[2]);
  })

(define_expand "<optab>si3"
  [(set (match_operand:SI 0 "register_operand")
	(ARITH:SI (match_operand:SI 1 "register_operand")
		   (match_operand:SI 2 "nonmemory_operand")))]
  ""
  "")

;;(define_expand "addv<mode>4"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "register_operand")
;;   (match_operand:GPI 2 "nonmemory_operand")
;;   (label_ref (match_operand 3 "" ""))]
;;  ""
;;  )
;;
;;(define_expand "uaddv<mode>4"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "register_operand")
;;   (match_operand:GPI 2 "register_operand")
;;   (label_ref (match_operand 3 "" ""))]
;;  ""
;;)
;;
;;(define_expand "subv<GPI:mode>4"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "register_operand")
;;   (match_operand:GPI 2 "nonmemory_operand")
;;   (label_ref (match_operand 3 "" ""))]
;;  ""
;;  )
;;
;;(define_expand "negv<GPI:mode>3"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "register_operand")
;;   (label_ref (match_operand 2 "" ""))]
;;  ""
;;  )
;;
;;(define_expand "usubv<mode>4"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "nonmemory_operand")
;;   (match_operand:GPI 2 "nonmemory_operand")
;;   (label_ref (match_operand 3 "" ""))]
;;  ""
;;  )

;; -------------------------------------------------------------------
;; Comparison insns
;; -------------------------------------------------------------------

(define_expand "cmp<mode>"
  [(set (reg:CC CC_REGNUM)
	(compare:CC (match_operand:GPI 0 "register_operand" "")
		    (match_operand:GPI 1 "nonmemory_operand" "")))]
  ""
  {
   if (!register_operand (operands[1], DImode))
      operands[1] = force_reg (DImode, operands[1]);
  })

(define_insn "*cmp<mode>"
  [(set (reg:CC CC_REGNUM)
	(compare:CC
	 (match_operand:GPI 0 "nonmemory_operand" " q,   qh,r,    r,    r,U06S0,S12S0,S32S0,r")
	 (match_operand:GPI 1 "nonmemory_operand" "qh,S03MV,r,U06S0,S12S0,    r,    r,    r,S32S0")))]
  "register_operand (operands[0], <MODE>mode)
   || register_operand (operands[1], <MODE>mode)"
  "@
   cmp<sfxtab>%?\\t%0,%1
   cmp<sfxtab>%?\\t%0,%1
   cmp<sfxtab>%?\\t%0,%1
   cmp<sfxtab>%?\\t%0,%1
   cmp<sfxtab>%?\\t%0,%1
   rcmp<sfxtab>%?\\t%1,%0
   rcmp<sfxtab>%?\\t%1,%0
   rcmp<sfxtab>%?\\t%1,%0
   cmp<sfxtab>%?\\t%0,%1"
  [(set_attr "type" "compare")
   (set_attr "iscompact" "maybe,maybe,no,no,no,no,no,no,no")
   (set_attr "predicable" "no,no,yes,yes,no,yes,no,no,no")
   (set_attr "length" "*,*,4,4,4,4,4,8,8")])

(define_insn "*cmpsi_zn"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN (match_operand:SI 0 "register_operand" "q,r")
		       (const_int 0)))]
  ""
  "tst%?\\t%0,%0"
  [(set_attr "type" "compare")
   (set_attr "iscompact" "yes,no")
   (set_attr "length" "2,4")])

(define_insn "*cmpdi_zn"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN (match_operand:DI 0 "register_operand" "r")
		       (const_int 0)))]
  ""
  "tstl\\t%0,%0"
  [(set_attr "type" "compare")
   (set_attr "iscompact" "no")
   (set_attr "length" "4")])

(define_insn "fcmp<mode>"
  [(set (reg:CC_FPU CC_REGNUM)
	(compare:CC_FPU (match_operand:GPF_HF 0 "register_operand" "w")
			(match_operand:GPF_HF 1 "register_operand" "w")))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>cmp\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fcmp")])

(define_insn "fcmpf<mode>"
  [(set (reg:CC_FPUE CC_REGNUM)
	(compare:CC_FPUE (match_operand:GPF_HF 0 "register_operand" "w")
			 (match_operand:GPF_HF 1 "register_operand" "w")))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>cmpf\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fcmp")])

;; -------------------------------------------------------------------
;; Store-flag and conditional select insns
;; -------------------------------------------------------------------

(define_expand "cstore<mode>4"
  [(set (match_operand:SI 0 "register_operand")
	(match_operator:SI 1 "arc64_comparison_operator"
	 [(match_operand:GPI 2 "nonmemory_operand")
	  (match_operand:GPI 3 "nonmemory_operand")]))]
  ""
  {
   if (!register_operand (operands[2], <MODE>mode))
     operands[2] = force_reg (<MODE>mode, operands[2]);
   if (!arc64_nonmem_operand (operands[3], <MODE>mode))
     operands[3] = force_reg (<MODE>mode, operands[3]);
  })

(define_expand "cstore<mode>4"
  [(set (match_operand:SI 0 "register_operand")
	(match_operator:SI 1 "arc64_comparison_operator"
	 [(match_operand:GPF_HF 2 "register_operand")
	  (match_operand:GPF_HF 3 "register_operand")]))]
  "ARC64_HAS_FP_BASE"
  "
  operands[2] = arc64_gen_compare_reg (GET_CODE (operands[1]), operands[2],
				      operands[3]);
  operands[3] = const0_rtx;
  "
)

(define_insn_and_split "*scc_insn"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(match_operator:SI 1 "arc64_comparison_operator"
			   [(reg CC_REGNUM) (const_int 0)]))]
  ""
  "#"
  "reload_completed"
  [(set (match_dup 0) (const_int 0))
   (cond_exec
     (match_dup 1)
     (set (match_dup 0) (const_int 1)))]
{
  operands[1]
    = gen_rtx_fmt_ee (GET_CODE (operands[1]),
		      VOIDmode,
		      XEXP (operands[1], 0), XEXP (operands[1], 1));
}
  [(set_attr "type" "movecc")])

;; SETcc instructions
(define_expand "set<optab><mode>"
  [(set (match_operand:SI 0 "register_operand")
	(ALLCC:SI
	 (match_operand:GPI 1 "register_operand")
	 (match_operand:GPI 2 "nonmemory_operand")))]
  ""
  {
   if (!arc64_nonmem_operand (operands[2], <MODE>mode))
      operands[2] = force_reg (<MODE>mode, operands[2]);
   })

(define_insn "*set<cctab><mode>"
  [(set (match_operand:SI 0 "register_operand"      "=r,    r,    r,r")
	(SETCC:SI
	 (match_operand:GPI 1 "register_operand"     "r,    r,    0,r")
	 (match_operand:GPI 2 "arc64_nonmem_operand" "r,U06S0,S12S0,n")))]
  ""
  "set<cctab><sfxtab>%?\\t%0,%1,%2"
  [(set_attr "length" "4,4,4,8")
   (set_attr "type" "setcc")])

;; Special cases of SETCC
(define_insn_and_split "*sethi<mode>"
  [(set (match_operand:SI 0 "register_operand"      "=r,    r,r")
	(gtu:SI
	 (match_operand:GPI 1 "register_operand"     "r,    r,r")
	 (match_operand:GPI 2 "arc64_nonmem_operand" "r,U06M1,n")))]
  ""
  "setlo<sfxtab>%?\\t%0,%2,%1"
  "reload_completed
   && CONST_INT_P (operands[2])
   && satisfies_constraint_U06M1 (operands[2])"
  [(const_int 0)]
  "{
    /* sethi a,b,u6 => seths a,b,u6 + 1.  */
    operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
    emit_insn (gen_setgeu<mode> (operands[0], operands[1], operands[2]));
    DONE;
   }"
 [(set_attr "length" "4,4,8")
   (set_attr "type" "setcc")])

(define_insn_and_split "*setls<mode>"
  [(set (match_operand:SI 0 "register_operand"      "=r,    r,r")
	(leu:SI
	 (match_operand:GPI 1 "register_operand"     "r,    r,r")
	 (match_operand:GPI 2 "arc64_nonmem_operand" "r,U06M1,n")))]
  ""
  "seths<sfxtab>%?\\t%0,%2,%1"
  "reload_completed
   && satisfies_constraint_U06M1 (operands[2])"
  [(const_int 0)]
  "{
    /* setls a,b,u6 => setlo a,b,u6 + 1.  */
    operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
    emit_insn (gen_setltu<mode> (operands[0], operands[1], operands[2]));
    DONE;
   }"
  [(set_attr "length" "4,4,8")
   (set_attr "type" "setcc")])

;; MOVCC patterns seems to generate worse code. Disable them for time being
;;(define_expand "mov<mode>cc"
;;  [(set (match_operand:ALLI 0 "register_operand")
;;	(if_then_else:ALLI (match_operand 1 "arc64_comparison_operator")
;;			   (match_operand:ALLI 2 "register_operand")
;;			   (match_operand:ALLI 3 "register_operand")))]
;;  ""
;;  {
;;   rtx tmp;
;;   enum rtx_code code = GET_CODE (operands[1]);
;;
;;   if (code == UNEQ || code == LTGT)
;;     FAIL;
;;
;;   tmp = arc64_gen_compare_reg (code, XEXP (operands[1], 0),
;;				XEXP (operands[1], 1));
;;   operands[1] = gen_rtx_fmt_ee (code, VOIDmode, tmp, const0_rtx);
;;  })

;;(define_expand "mov<mode>cc"
;;  [(set (match_operand:GPF 0 "register_operand")
;;	(if_then_else:GPF (match_operand 1 "arc64_comparison_operator")
;;			  (match_operand:GPF 2 "register_operand")
;;			  (match_operand:GPF 3 "register_operand")))]
;;  ""
;;  {
;;   rtx tmp;
;;   enum rtx_code code = GET_CODE (operands[1]);
;;
;;   if (code == UNEQ || code == LTGT)
;;     FAIL;
;;
;;   tmp = arc64_gen_compare_reg (code, XEXP (operands[1], 0),
;;				XEXP (operands[1], 1));
;;   operands[1] = gen_rtx_fmt_ee (code, VOIDmode, tmp, const0_rtx);
;;  })

;;(define_insn "*cmov<mode>"
;;  [(set (match_operand:ALLI 0 "register_operand" "=r,r")
;;	(if_then_else:ALLI
;;	 (match_operator 3 "arc64_comparison_operator"
;;			 [(match_operand 4 "cc_register" "") (const_int 0)])
;;	 (match_operand:ALLI 1 "nonmemory_operand" "rU06S0,S32S0")
;;	 (match_operand:ALLI 2 "register_operand"  "0,0")))]
;;  ""
;;  "mov<mcctab>.%m3\\t%0,%1"
;;  [(set_attr "length" "4,8")
;;   (set_attr "type" "move")])

;;(define_insn "*cmov<mode>"
;;  [(set (match_operand:GPF 0 "register_operand" "=w,*r,*r")
;;	(if_then_else:GPF
;;	 (match_operator 3 "arc64_comparison_operator"
;;			 [(match_operand 4 "cc_register" "") (const_int 0)])
;;	 (match_operand:GPF 1 "nonmemory_operand" "w,*r,*E")
;;	 (match_operand:GPF 2 "register_operand"  "0, 0, 0")))]
;;  ""
;;  "@
;;   f<sfxtab>mov.%m3\\t%0,%1
;;   mov<mcctab>.%m3\\t%0,%1
;;   mov<mcctab>.%m3\\t%0,%1"
;;  [(set_attr "length" "4,4,8")
;;   (set_attr "type" "fmov,move,move")])

;; conditional patterns
;; Todo: add conditional execution for leu and geu
(define_insn "*set<cctab><mode>_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 4 "cc_register" "") (const_int 0)])
    (set (match_operand:SI 0 "register_operand"            "=r,r")
	 (SETCC:SI (match_operand:GPI 1 "register_operand"  "0,0")
		   (match_operand:GPI 2 "arc64_nonmem_operand" "r,n"))))]
  ""
  "set<cctab><sfxtab>.%m3\\t%0,%1,%2"
  [(set_attr "type" "setcc")
   (set_attr "length" "4,8")])

;; -------------------------------------------------------------------
;; Logical operations
;; -------------------------------------------------------------------

(define_expand "<optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand")
	(LOGIC:GPI (match_operand:GPI 1 "register_operand")
		   (match_operand:GPI 2 "nonmemory_operand")))]
  ""
  {
   if (!arc64_nonmem_operand (operands[2], <MODE>mode))
      operands[2] = force_reg (<MODE>mode, operands[2]);
  })

(define_expand "<optab><mode>2"
  [(set (match_operand:GPI 0 "register_operand")
	(LOGIC2:GPI (match_operand:GPI 1 "register_operand")))]
  ""
  )

(define_insn "negsi2"
  [(set (match_operand:SI 0 "register_operand"        "=q,q,r,r")
	(neg:SI (match_operand:SI 1 "register_operand" "0,q,0,r")))]
  ""
  "neg%?\\t%0,%1"
  [(set_attr "type" "neg")
   (set_attr "iscompact" "maybe,yes,no,no")
   (set_attr "predicable" "yes,no,yes,no")
   (set_attr "length" "*,2,4,4")])

(define_insn "*<optab><mode>2"
  [(set (match_operand:GPI 0 "register_operand" "=q,r")
	(LOGIC2:GPI (match_operand:GPI 1 "register_operand" "q,r")))]
  ""
  "<mntab><sfxtab>%?\\t%0,%1"
  [(set_attr "type" "<mntab>")
   (set_attr "iscompact" "maybe,no")
   (set_attr "length" "*,4")])

(define_insn "*<optab><mode>3"
   [(set (match_operand:GPI 0 "register_operand"                  "=r,    r,     r,r")
	 (MINMAX:GPI (match_operand:GPI 1 "register_operand"      "%0,    0,     r,r")
		     (match_operand:GPI 2 "nonmemory_operand" "rU06S0,S12S0,rU06S0,S32S0")))]
  ""
  "<mntab><sfxtab>%?\\t%0,%1,%2"
  [(set_attr "type" "<mntab>")
   (set_attr "length" "4,4,4,8")
   (set_attr "predicable" "yes,no,no,no")]
)

;; Conditional execution
(define_insn "*<optab><mode>_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 4 "cc_register" "") (const_int 0)])
    (set (match_operand:GPI 0 "register_operand"                  "=r,r")
	 (MINMAX:GPI (match_operand:GPI 1 "register_operand"      "%0,0")
		     (match_operand:GPI 2 "nonmemory_operand" "rU06S0,S32S0"))))]
  ""
  "<mntab><sfxtab>.%m3\\t%0,%1,%2"
  [(set_attr "type" "<mntab>")
   (set_attr "length" "4,8")])

;; Zero-extend pattern
(define_insn "*<optab>si_zextend"
  [(set (match_operand:DI 0 "register_operand" "=q,r")
	(zero_extend:DI
	 (LOP2EX:SI (match_operand:SI 1 "register_operand" "q,r"))))]
  ""
  "<mntab>%?\\t%0,%1"
  [(set_attr "type" "<mntab>")
   (set_attr "iscompact" "yes,no")
   (set_attr "length" "*,4")])

(define_insn "*<optab>3_zextend"
  [(set (match_operand:DI 0 "register_operand"        "=r,    r,     r,r")
	(zero_extend:DI
	 (MINMAX:SI
	  (match_operand:SI 1 "register_operand"      "%0,    0,     r,r")
	  (match_operand:SI 2 "nonmemory_operand" "rU06S0,S12S0,rU06S0,S32S0"))))]
  ""
  "<mntab>%?\\t%0,%1,%2"
  [(set_attr "type" "max")
   (set_attr "length" "4,4,4,8")
   (set_attr "predicable" "yes,no,no,no")])

;; -------------------------------------------------------------------
;; Shifts
;; -------------------------------------------------------------------

;; FIXME! check if we get better code if we use QI for op 2.
(define_expand "<optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand")
	(ASHIFT:GPI (match_operand:GPI 1 "register_operand")
		    (match_operand:GPI 2 "nonmemory_operand")))]
  "")

(define_expand "rotrsi3"
  [(set (match_operand:SI 0 "register_operand")
	(rotatert:SI (match_operand:SI 1 "nonmemory_operand")
		     (match_operand:SI 2 "nonmemory_operand")))]
  "")

(define_insn "*rotrsi3"
  [(set (match_operand:SI 0 "register_operand"                   "=r,     r,r")
	(rotatert:SI (match_operand:SI 1 "nonmemory_operand"      "0,     r,i")
		     (match_operand:SI 2 "nonmemory_operand" "rU06S0,rU06S0,r")))]
  ;; FIXME! this needs BARREL_SHIFTER option
  "register_operand (operands[0], SImode)
   || register_operand (operands[1], SImode)"
  "ror%?\\t%0,%1,%2"
  [(set_attr "type" "ror")
   (set_attr "predicable" "yes,no,no")
   (set_attr "length" "4,4,8")])

(define_insn "rotr1"
  [(set (match_operand:SI 0 "register_operand"              "=     r,r")
	(rotatert:SI (match_operand:SI 1 "nonmemory_operand" "rU06S0,i")
		     (const_int 1)))]
  ""
  "ror%?\\t%0,%1"
  [(set_attr "type" "ror")
   (set_attr "predicable" "no")
   (set_attr "length" "4,8")])

(define_insn "rotr8"
  [(set (match_operand:SI 0 "register_operand"              "=     r,r")
	(rotatert:SI (match_operand:SI 1 "nonmemory_operand" "rU06S0,i")
		     (const_int 8)))]
  ""
  "ror8%?\\t%0,%1"
  [(set_attr "type" "ror")
   (set_attr "predicable" "no")
   (set_attr "length" "4,8")])

(define_expand "rotlsi3"
  [(set (match_operand:SI 0 "register_operand")
	(rotatert:SI (match_operand:SI 1 "nonmemory_operand")
		     (match_operand:SI 2 "nonmemory_operand")))]
  ""
  "
  if (CONST_INT_P (operands[2])
      && (INTVAL (operands[2]) == 1))
    {
     gen_rotl1 (operands[0], operands[1]);
     DONE;
    }

  if (CONST_INT_P (operands[2])
      && (INTVAL (operands[2]) == 8))
    {
     gen_rotl8 (operands[0], operands[1]);
     DONE;
    }

  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT ((32 - INTVAL (operands[2])) % 32);
  else
    {
      rtx reg = gen_reg_rtx (SImode);
      emit_insn (gen_subsi3 (reg, GEN_INT (32), operands[2]));
      operands[2] = reg;
    }
  ")

(define_insn "rotl1"
  [(set (match_operand:SI 0 "register_operand"             "=     r,r")
	(rotate:SI (match_operand:SI 1 "nonmemory_operand"  "rU06S0,i")
		   (const_int 1)))]
  ""
  "rol%?\\t%0,%1"
  [(set_attr "type" "rol")
   (set_attr "predicable" "no")
   (set_attr "length" "4,8")])

(define_insn "rotl8"
  [(set (match_operand:SI 0 "register_operand"             "=     r,r")
	(rotate:SI (match_operand:SI 1 "nonmemory_operand"  "rU06S0,i")
		   (const_int 8)))]
  ""
  "rol8%?\\t%0,%1"
  [(set_attr "type" "rol")
   (set_attr "predicable" "no")
   (set_attr "length" "4,8")])

;; Conditional execution
(define_insn "*rotrsi_ce"
  [(cond_exec
    (match_operator 3 "arc64_comparison_operator"
		    [(match_operand 4 "cc_register" "") (const_int 0)])
    (set (match_operand:SI 0 "register_operand"                   "=r,r")
	 (rotatert:SI (match_operand:SI 1 "register_operand"      "%0,0")
		      (match_operand:SI 2 "nonmemory_operand" "rU06S0,S32S0"))))
   ]
  ""
  "ror.%m3\\t%0,%1,%2"
  [(set_attr "type" "ror")
   (set_attr "length" "4,8")])

;; -------------------------------------------------------------------
;; Bitfields
;; -------------------------------------------------------------------

(define_expand "extzv<mode>"
  [(set (match_operand:GPI 0 "register_operand" "")
	(zero_extract:GPI (match_operand:GPI 1 "register_operand" "")
			  (match_operand 2 "const_int_operand" "")
			  (match_operand 3 "const_int_operand" "")))]
  "")

(define_insn "*extzvsi"
  [(set (match_operand:SI 0 "register_operand"                  "=r,r")
	(zero_extract:SI (match_operand:SI 1 "register_operand"  "0,r")
			 (match_operand 2    "const_int_operand" "n,n")
			 (match_operand 3    "const_int_operand" "n,n")))]
  ""
  {
   int assemble_op2 = (((INTVAL (operands[2]) - 1) & 0x1f) << 5)
                       | (INTVAL (operands[3]) & 0x1f);
   operands[2] = GEN_INT (assemble_op2);
   return "xbfu%?\\t%0,%1,%2";
  }
  [(set_attr "type"       "xbfu")
   (set_attr "iscompact"  "no")
   (set_attr "length"     "4,8")
   (set_attr "predicable" "no")])

;;FIXME! compute length based on the input args.
(define_insn "*extzvdi"
  [(set (match_operand:DI 0 "register_operand"                  "=r,r")
	(zero_extract:DI (match_operand:DI 1 "register_operand"  "0,r")
			 (match_operand 2    "const_int_operand" "n,n")
			 (match_operand 3    "const_int_operand" "n,n")))]
  ""
  {
   int assemble_op2 = (((INTVAL (operands[2]) - 1) & 0x3f) << 6)
                       | (INTVAL (operands[3]) & 0x3f);
   operands[2] = GEN_INT (assemble_op2);
   return "xbful%?\\t%0,%1,%2";
  }
  [(set_attr "type"       "xbfu")
   (set_attr "iscompact"  "no")
   (set_attr "length"     "8,8")
   (set_attr "predicable" "no")])

;; -------------------------------------------------------------------
;; Bitscan
;; -------------------------------------------------------------------

(define_insn "clrsb<mode>2"
  [(set (match_operand:EPI 0 "register_operand"           "=r")
	(clrsb:EPI (match_operand:EPI 1 "register_operand" "r")))]
  "TARGET_BITSCAN"
  "norm<sfxtab>\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "norm<sfxtab>")])

(define_expand "clz<mode>2"
  [(match_operand:GPI 0 "register_operand")
   (match_operand:GPI 1 "register_operand")]
  "TARGET_BITSCAN"
  {
   rtx tmp = gen_reg_rtx (<MODE>mode);
   unsigned int size = GET_MODE_SIZE (<MODE>mode) * BITS_PER_UNIT - 1;
   emit_insn (gen_arc64_fls<sfxtab>2 (tmp, operands[1]));
   emit_insn (gen_sub<mode>3 (operands[0], GEN_INT (size), tmp));
   DONE;
   })

(define_insn "ctz<mode>2"
  [(set (match_operand:GPI 0 "register_operand"         "=r")
	(ctz:GPI (match_operand:GPI 1 "register_operand" "r")))]
  "TARGET_BITSCAN"
  "ffs<sfxtab>\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "ffs")])

(define_insn "arc64_fls<sfxtab>2"
  [(set (match_operand:GPI  0 "register_operand"            "=r")
	(unspec:GPI [(match_operand:GPI 1 "register_operand" "r")]
		    ARC64_UNSPEC_FLS))]
  "TARGET_BITSCAN"
  "fls<sfxtab>\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fls")])

;; -------------------------------------------------------------------
;; Floating-point intrinsics
;; -------------------------------------------------------------------

(define_insn "round<mode>2"
  [(set (match_operand:GPF 0 "register_operand" "=w")
	(unspec:GPF [(match_operand:GPF 1 "register_operand" "w")]
		    ARC64_UNSPEC_ROUND))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>rnd\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "frnd")])

(define_insn "btrunc<mode>2"
  [(set (match_operand:GPF 0 "register_operand" "=w")
	(unspec:GPF [(match_operand:GPF 1 "register_operand" "w")]
		    ARC64_UNSPEC_BTRUNC))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>rnd_rz\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "frnd")])

;; -------------------------------------------------------------------
;; Floating-point conversions
;; -------------------------------------------------------------------

(define_insn "extendsfdf2"
  [(set (match_operand:DF 0 "register_operand" "=w")
        (float_extend:DF (match_operand:SF 1 "register_operand" "w")))]
  "ARC64_HAS_FPUD"
  "fs2d\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fs2d")])

(define_insn "extendhfsf2"
  [(set (match_operand:SF 0 "register_operand" "=w")
        (float_extend:SF (match_operand:HF 1 "register_operand" "w")))]
  "ARC64_HAS_FPUH"
  "fh2s\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fh2s")])

;;(define_expand "extendhfdf2"
;;  [(match_operand:DF 0 "register_operand")
;;   (match_operand:HF 1 "register_operand")]
;;  "ARC64_HAS_FPUH"
;;  {
;;    rtx tmp = gen_reg_rtx (SFmode);
;;    emit_insn (gen_extendhfsf2 (tmp, operands[1]));
;;    emit_insn (gen_extendsfdf2 (operands[0], tmp));
;;    DONE;
;;  })

(define_insn "truncdfsf2"
  [(set (match_operand:SF 0 "register_operand" "=w")
        (float_truncate:SF (match_operand:DF 1 "register_operand" "w")))]
  "ARC64_HAS_FPUD"
  "fd2s\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fd2s")])

(define_insn "truncsfhf2"
  [(set (match_operand:HF 0 "register_operand" "=w")
        (float_truncate:HF (match_operand:SF 1 "register_operand" "w")))]
  "ARC64_HAS_FPUH"
  "fs2h\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fs2h")])

;;(define_expand "truncdfhf2"
;;  [(match_operand:HF 0 "register_operand")
;;   (match_operand:DF 1 "register_operand")]
;;  "ARC64_HAS_FPUH"
;;  {
;;    rtx tmp = gen_reg_rtx (SFmode);
;;    emit_insn (gen_truncdfsf2 (tmp, operands[1]));
;;    emit_insn (gen_truncsfhf2 (operands[0], tmp));
;;    DONE;
;;  })

;; SI->SF SI->DF DI->SF DI->DF
;; FINT2S FINT2D FL2S FL2D
(define_insn "float<GPI:mode><GPF:mode>2"
  [(set (match_operand:GPF 0 "register_operand"           "=w")
	(float:GPF (match_operand:GPI 1 "register_operand" "r")))]
  "ARC64_HAS_FP_BASE"
  "f<GPI:f2tab>2<GPF:sfxtab>\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "int2fp")])

(define_expand "floatsihf2"
  [(match_operand:HF 0 "register_operand")
   (match_operand:SI 1 "register_operand")]
  "ARC64_HAS_FPUH"
  {
    rtx tmp = gen_reg_rtx (SFmode);
    emit_insn (gen_floatsisf2 (tmp, operands[1]));
    emit_insn (gen_truncsfhf2 (operands[0], tmp));
    DONE;
  })

(define_expand "floatdihf2"
  [(match_operand:HF 0 "register_operand")
   (match_operand:DI 1 "register_operand")]
  "ARC64_HAS_FPUH"
  {
    rtx tmp = gen_reg_rtx (SFmode);
    emit_insn (gen_floatdisf2 (tmp, operands[1]));
    emit_insn (gen_truncsfhf2 (operands[0], tmp));
    DONE;
    })

;; uSI->SF uSI->DF uDI->SF uDI->DF
;; FUINT2S FUINT2D FUL2S FUL2D
(define_insn "floatuns<GPI:mode><GPF:mode>2"
  [(set (match_operand:GPF 0 "register_operand"                    "=w")
	(unsigned_float:GPF (match_operand:GPI 1 "register_operand" "r")))]
  "ARC64_HAS_FP_BASE"
  "fu<GPI:f2tab>2<GPF:sfxtab>\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "uint2fp")])

;; SF->uSI SF->uDI DF->uSI DF->uDI (using rounding towards zero)
;; FS2UINT_RZ FS2UL_RZ FD2UINT_RZ FD2UL_RZ
(define_insn "fixuns_trunc<GPF:mode><GPI:mode>2"
  [(set (match_operand:GPI 0 "register_operand"         "=r")
	(unsigned_fix:GPI (match_operand:GPF 1 "register_operand" "w")))]
  "ARC64_HAS_FP_BASE"
  "f<GPF:sfxtab>2u<GPI:f2tab>_rz\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fp2uint")])

;; SF->SI SF->DI DF->SI DF->DI (using rounding towards zero)
;; FS2INT_RZ FS2L_RZ FD2INT_RZ FD2L_RZ
(define_insn "fix_trunc<GPF:mode><GPI:mode>2"
  [(set (match_operand:GPI 0 "register_operand"         "=r")
	(fix:GPI (match_operand:GPF 1 "register_operand" "w")))]
  "ARC64_HAS_FP_BASE"
  "f<GPF:sfxtab>2<GPI:f2tab>_rz\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fp2int")])

;; -------------------------------------------------------------------
;; Floating-point arithmetic
;; -------------------------------------------------------------------

;; F<P>ADD F<P>SUB F<P>MUL F<P>DIV F<P>MIN F<P>MAX
(define_insn "<optab><mode>3"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(DOPF:GPF_HF (match_operand:GPF_HF 1 "register_operand" "w")
		     (match_operand:GPF_HF 2 "register_operand" "w")))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab><mntab>\\t%0,%1,%2"
  [(set_attr "length" "4")
   (set_attr "type" "f<mntab>")])

;; F<P>ABS
;; FIXME! bclr can be short. Also we can predicate it
(define_insn "abs<mode>2"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w,*r")
	(abs:GPF_HF (match_operand:GPF_HF 1 "register_operand" "w,*r")))]
  ""
  "@
  f<sfxtab>sgnjx\\t%0,%1,%1
  bclr<fptab>\\t%0,%1,<sizen>"
  [(set_attr "length" "4")
   (set_attr "type" "fsgnjx,bclr")])

;; F<P>NEG
;; FIXME! bxor can be predicated
(define_insn "neg<mode>2"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w,*r")
	(neg:GPF_HF (match_operand:GPF_HF 1 "register_operand" "w,*r")))]
  ""
  "@
  f<sfxtab>sgnjn\\t%0,%1,%1
  bxor<fptab>\\t%0,%1,<sizen>"
  [(set_attr "length" "4")
   (set_attr "type" "fsgnjn,bxor")])

;; F<P>MADD
(define_insn "fma<mode>4"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(fma:GPF_HF (match_operand:GPF_HF 1 "register_operand"  "w")
		    (match_operand:GPF_HF 2 "register_operand"  "w")
		    (match_operand:GPF_HF 3 "register_operand"  "w")))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>madd\\t%0,%1,%2,%3"
  [(set_attr "length" "4")
   (set_attr "type" "fmadd")])

;; F<P>MSUB
(define_insn "fnma<mode>4"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(fma:GPF_HF (neg:GPF_HF (match_operand:GPF_HF 1 "register_operand"  "w"))
		    (match_operand:GPF_HF 2 "register_operand"  "w")
		    (match_operand:GPF_HF 3 "register_operand"  "w")))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>msub\\t%0,%1,%2,%3"
  [(set_attr "length" "4")
   (set_attr "type" "fmsub")])

;; F<P>NMSUB
;; TBI: the md.texi says Like @code{fma@var{m}4}, except
;; operand 3 subtracted from the product instead of added to the
;; product. However, fnmsub does -(s3 - (s1 * s2))
(define_insn "fms<mode>4"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(fma:GPF_HF (match_operand:GPF_HF 1 "register_operand"  "w")
		    (match_operand:GPF_HF 2 "register_operand"  "w")
		    (neg:GPF_HF (match_operand:GPF_HF 3 "register_operand"  "w"))))]
  "!HONOR_SIGNED_ZEROS (<MODE>mode) && ARC64_HAS_FP_BASE"
  "f<sfxtab>nmsub\\t%0,%1,%2,%3"
  [(set_attr "length" "4")
   (set_attr "type" "fnmsub")])

;; -(op3 - (op1 * op2))
(define_insn "*nfnms<mode>4"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(neg:GPF_HF (fma:GPF_HF (neg:GPF_HF (match_operand:GPF_HF 1 "register_operand"  "w"))
			  (match_operand:GPF_HF 2 "register_operand"  "w")
			  (match_operand:GPF_HF 3 "register_operand"  "w"))))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>nmsub\\t%0,%1,%2,%3"
  [(set_attr "length" "4")
   (set_attr "type" "fnmsub")])

;; F<P>NMADD
;; Likewise like above
(define_insn "fnms<mode>4"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(fma:GPF_HF (neg:GPF_HF (match_operand:GPF_HF 1 "register_operand"  "w"))
		    (match_operand:GPF_HF 2 "register_operand"  "w")
		    (neg:GPF_HF (match_operand:GPF_HF 3 "register_operand"  "w"))))]
  "!HONOR_SIGNED_ZEROS (<MODE>mode) && ARC64_HAS_FP_BASE"
  "f<sfxtab>nmadd\\t%0,%1,%2,%3"
  [(set_attr "length" "4")
   (set_attr "type" "fnmadd")])

;; -(op3 + (op1 * op2))
(define_insn "*nfms<mode>4"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(neg:GPF_HF (fma:GPF_HF (match_operand:GPF_HF 1 "register_operand"  "w")
				(match_operand:GPF_HF 2 "register_operand"  "w")
				(match_operand:GPF_HF 3 "register_operand"  "w"))))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>nmadd\\t%0,%1,%2,%3"
  [(set_attr "length" "4")
   (set_attr "type" "fnmadd")])

;; F<P>SQRT
(define_insn "sqrt<mode>2"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(sqrt:GPF_HF (match_operand:GPF_HF 1 "register_operand" "w")))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>sqrt\\t%0,%1"
  [(set_attr "length" "4")
   (set_attr "type" "fsqrt")])

;; F<P>SGNJ
(define_insn "copysign<mode>3"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(unspec:GPF_HF [(match_operand:GPF_HF 1 "register_operand" "w")
			(match_operand:GPF_HF 2 "register_operand" "w")]
		       ARC64_UNSPEC_COPYSIGN))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>sgnj\\t%0,%1,%2"
  [(set_attr "length" "4")
   (set_attr "type" "fsgnj")])

;; F<P>SGNJX
(define_insn "xorsign<mode>3"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(unspec:GPF_HF [(match_operand:GPF_HF 1 "register_operand" "w")
			(match_operand:GPF_HF 2 "register_operand" "w")]
		       ARC64_UNSPEC_XORSIGN))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>sgnjx\\t%0,%1,%2"
  [(set_attr "length" "4")
   (set_attr "type" "fsgnjx")])

;; F<P>SGNJN
(define_insn "*ncopysign<mode>3"
  [(set (match_operand:GPF_HF 0 "register_operand" "=w")
	(neg:GPF_HF (unspec:GPF_HF
		     [(match_operand:GPF_HF 1 "register_operand" "w")
		      (match_operand:GPF_HF 2 "register_operand" "w")]
		     ARC64_UNSPEC_COPYSIGN)))]
  "ARC64_HAS_FP_BASE"
  "f<sfxtab>sgnjn\\t%0,%1,%2"
  [(set_attr "length" "4")
   (set_attr "type" "fsgnjn")])

;; -------------------------------------------------------------------
;; Builtins
;; -------------------------------------------------------------------

(define_insn "lr"
  [(set (match_operand:SI  0 "register_operand" "=r,r,r,r")
	(unspec_volatile:SI
	 [(match_operand:SI 1 "nonmemory_operand" "U06S0,S12S0,r,i")]
	 ARC64_VUNSPEC_LR))]
  ""
  "lr\\t%0,[%1]"
  [(set_attr "length" "4,4,4,8")
   (set_attr "type" "lr")])

(define_insn "sr"
  [(unspec_volatile
    [(match_operand:SI 0 "register_operand"  "    r,    r, r, r")
     (match_operand:SI 1 "nonmemory_operand" "U06S0,S12S0, i, r")]
    ARC64_VUNSPEC_SR)]
  ""
  "sr\\t%0,[%1]"
  [(set_attr "length" "4,4,4,8")
   (set_attr "type" "sr")])

(define_insn "lrl"
  [(set (match_operand:DI  0 "register_operand" "=r,r,r,r")
	(unspec_volatile:DI
	 [(match_operand:DI 1 "nonmemory_operand" "U06S0,S12S0,r,i")]
	 ARC64_VUNSPEC_LRL))]
  ""
  "lrl\\t%0,[%1]"
  [(set_attr "length" "4,4,4,8")
   (set_attr "type" "lr")])

(define_insn "srl"
  [(unspec_volatile
    [(match_operand:DI 0 "register_operand"  "    r,    r, r, r")
     (match_operand:DI 1 "nonmemory_operand" "U06S0,S12S0, i, r")]
    ARC64_VUNSPEC_SRL)]
  ""
  "srl\\t%0,[%1]"
  [(set_attr "length" "4,4,4,8")
   (set_attr "type" "sr")])

(define_insn "flag"
  [(unspec_volatile [(match_operand:SI 0 "nonmemory_operand" "U06S0,S12S0,r,i")]
		   ARC64_VUNSPEC_FLAG)]
  ""
  "@
    flag%?\\t%0
    flag\\t%0
    flag%?\\t%0
    flag%?\\t%0"
  [(set_attr "length" "4,4,4,8")
   (set_attr "type" "flag")
   (set_attr "predicable" "yes,no,yes,yes")])

(define_insn "brk"
  [(unspec_volatile [(const_int 0)] ARC64_VUNSPEC_BRK)]
  ""
  "brk"
  [(set_attr "length" "4")
  (set_attr "type" "brk")])

(define_insn "nopv"
  [(unspec_volatile [(const_int 0)] ARC64_VUNSPEC_NOP)]
  ""
  "nop_s"
  [(set_attr "type" "nop")
   (set_attr "length" "2")])


;; For thread pointer builtins
(define_expand "get_thread_pointerdi"
  [(set (match_operand:DI 0 "register_operand") (match_dup 1))]
 ""
 "operands[1] = gen_rtx_REG (Pmode, R30_REGNUM);")

(define_expand "set_thread_pointerdi"
  [(set (match_dup 1) (match_operand:DI 0 "register_operand"))]
 ""
 "operands[1] = gen_rtx_REG (Pmode, R30_REGNUM);")


(include "arith.md")

(define_insn "sync"
  [(unspec_volatile [(const_int 1)]
		   ARC64_VUNSPEC_SYNC)]
  ""
  "sync"
  [(set_attr "length" "4")
  (set_attr "type" "sync")])

(include "atomic.md")


;; mode:emacs-lisp
;; comment-start: ";; "
;; eval: (set-syntax-table (copy-sequence (syntax-table)))
;; eval: (modify-syntax-entry ?[ "(]")
;; eval: (modify-syntax-entry ?] ")[")
;; eval: (modify-syntax-entry ?{ "(}")
;; eval: (modify-syntax-entry ?} "){")
;; eval: (setq indent-tabs-mode t)
;; End:
