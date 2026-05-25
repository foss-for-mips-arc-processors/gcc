/* This pass identifies addressing patterns in memory-access intensive 
   kernels. In such kernels an index is frequently scaled and added to a 
   base pointer to access memory followed by an immediate index update.
   The pass hoists the pointer arithmetic out of the loop header converting
   index addressing into induction variables. */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "gimple.h"
#include "cfghooks.h"
#include "cfgcleanup.h"
#include "memmodel.h"
#include "emit-rtl.h"
#include "alias.h"
#include "rtlanal.h"
#include "cfgloop.h"
#include "insn-config.h"
#include "insn-flags.h"
#include "insn-codes.h"
#include "optabs.h"
#include "recog.h"
#include "tree-pass.h"
#include "cfgrtl.h"
#include "expr.h"
#include "explow.h"
#include "expmed.h"
#include "df.h"
#include "print-rtl.h"

namespace {

struct ladder_step {
  rtx_insn *sh1add_insn;
  rtx_insn *addw_insn; 
  rtx_insn *mem_insn;    
  rtx dest_reg;          
  rtx index_reg;         
};

const pass_data pass_data_riscv_matrix_opt = {
  RTL_PASS, 
  "riscv_matrix_opt",
  OPTGROUP_NONE, 
  TV_NONE, 
  0, 0, 0, 0, 0,
};

class pass_riscv_matrix_opt : public rtl_opt_pass {
public:
  pass_riscv_matrix_opt (gcc::context *ctxt) 
    : rtl_opt_pass (pass_data_riscv_matrix_opt, ctxt) {}

virtual bool
 gate (function *fun) override 
  { 
    if (optimize <= 0) 
      return false;
    
    return riscv_matrix_opt && function_is_leaf(fun);
  }


/* Remove SIGN_EXTEND ZERO_EXTEND or SUBREG from an RTX 
   to reach the underlying register or constant.  */

  rtx unwrap_rtx (rtx x) {
    if (!x) return NULL_RTX;
    while (GET_CODE (x) == SIGN_EXTEND 
		    || GET_CODE (x) == ZERO_EXTEND 
		    || GET_CODE (x) == SUBREG) {
      x = (GET_CODE (x) == SUBREG) ? SUBREG_REG (x) : XEXP (x, 0);
    }
    return x;
  }

/* Return true if INSN is a memory access whose address calculation
   involves ADDR_REG.  */

  bool mem_uses_reg_p (rtx_insn *insn, rtx addr_reg) {
    rtx set = single_set (insn);
    if (!set) return false;
    rtx src = SET_SRC (set);
    while (GET_CODE (src) == SIGN_EXTEND 
		    || GET_CODE (src) == ZERO_EXTEND)
      src = XEXP (src, 0);
    if (!MEM_P (src)) return false;
    rtx addr = XEXP (src, 0);

    if (REG_P (addr) && REGNO (addr) == REGNO (addr_reg)) 
	    return true;

    if (GET_CODE (addr) == PLUS && REG_P (XEXP (addr, 0)) 
		    && CONST_INT_P (XEXP (addr, 1)))
      return REGNO (XEXP (addr, 0)) == REGNO (addr_reg);
    return false;
  }

  bool is_sh1add_uw (rtx_insn *insn, rtx *dest, rtx *idx, rtx *base) {
    rtx set = single_set (insn);
    if (!set) return false;
    rtx src = SET_SRC (set);
    if (GET_CODE (src) != PLUS) return false;
    rtx op0 = XEXP (src, 0); 
    if (GET_CODE (op0) == AND) op0 = XEXP (op0, 0);
    if (GET_CODE (op0) != ASHIFT || !CONST_INT_P (XEXP (op0, 1)) 
		    || INTVAL (XEXP (op0, 1)) != 1)
      return false;
    *dest = SET_DEST (set);
    *idx = unwrap_rtx (XEXP (op0, 0));
    *base = unwrap_rtx (XEXP (src, 1));
    return (REG_P (*idx) && REG_P (*base));
  }

  bool is_addw (rtx_insn *insn, rtx *dest, rtx *op0, rtx *op1) {
    rtx set = single_set (insn);
    if (!set) return false;
    rtx src_expr = SET_SRC (set);
    while (GET_CODE (src_expr) == SIGN_EXTEND 
		    || GET_CODE (src_expr) == ZERO_EXTEND)
      src_expr = XEXP (src_expr, 0);
    if (GET_CODE (src_expr) == PLUS) {
      *dest = SET_DEST (set);
      *op0 = unwrap_rtx (XEXP (src_expr, 0));
      *op1 = unwrap_rtx (XEXP (src_expr, 1));
      return (REG_P (*op0) || REG_P (*op1));
    }
    return false;
  }

/* Returns true if leaf.  */
bool
function_is_leaf (function *fun)
{
  if (!fun)
    return false;

  rtx_insn *insn;

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      if (CALL_P (insn))
	{
	  return false; 
	}
    }
  // No function calls were detected
  return true;
}

/* Example of what the phase is supposed to do.
Code before transformation:
.L4:
  //First Link
  sh1add.uw   a2, a5, s3   # A. sh1add_uw_p (Index: a5, Base: s3)          	
  lh          t6, 0(a2)    # B. mem_insn (ses result of A)
  addw        s8, a5, a0   # C. addw_p (pdates a5 -> s8 using stride a0)  	
                                                                           	
  #Second Link                                                     	
  sh1add.uw   s0, s8, s3   # D. sh1add_uw_p (index: s8, Base: s3)          	
  lh          a1, 0(s0)    # E. mem_insn (use result of D)                	
  addw        s1, s8, a0   # F. addw_p (updates s8 -> s1 using stride a0)  	
                                                                           	
  #Third Link                                                      	
  sh1add.uw   t0, s1, s3   # G. sh1add_uw_p (index: s1, Base: s3)          	
                           #    index s1 matches Step 2 update. 	
                                                                           	
Code after transformation:
#Preheader
  slli        t4, a0, 1    
  sh1add.uw   a2, a5, s3   
  add         s0, a2, t4   
  add         t0, s0, t4   
                           
.L4:                       
  #Loop Body               
  lh          t6, 0(a2)    
  lh          a1, 0(s0)    
  lh          t3, 0(t0)    
  add         a2, a2, t4   
  add         s0, s0, t4   
  add         t0, t0, t4   
  bne         ...          
*/         

  virtual unsigned int execute (function *fun) override {
    loop_optimizer_init (LOOPS_NORMAL | LOOPS_HAVE_PREHEADERS);
    df_chain_add_problem (DF_DU_CHAIN | DF_UD_CHAIN);
    df_analyze ();

    bool changed = false;

    for (auto loop : loops_list (fun, LI_FROM_INNERMOST)) {
      if (loop->inner != NULL) continue;
      basic_block *bbs = get_loop_body (loop);
      auto_vec<ladder_step> chain;
      rtx shared_base = NULL_RTX;
      rtx shared_stride = NULL_RTX;
      rtx target_idx = NULL_RTX;

      for (unsigned i = 0; i < loop->num_nodes; i++) {
        rtx_insn *insn;
        FOR_BB_INSNS (bbs[i], insn) {
          if (!NONDEBUG_INSN_P (insn)) continue;
          rtx dest, idx, base;
          if (is_sh1add_uw (insn, &dest, &idx, &base)) {
            if (chain.length() == 0) 
	    { 
		shared_base = base; 
		target_idx = idx; 
	    }

            if (REGNO(base) != REGNO(shared_base)
			    || REGNO(idx) != REGNO(target_idx))
		    continue;

            rtx_insn *mem_insn = NULL;
            for (df_ref def = DF_INSN_DEFS (insn); def; def = DF_REF_NEXT_LOC (def)) 
	    {
              for (struct df_link *l = DF_REF_CHAIN (def); l; l = l->next) 
	      {
                rtx_insn *u = DF_REF_INSN (l->ref);
                if (u && mem_uses_reg_p (u, dest)) { 
			mem_insn = u; 
			break;
		}
              }
              if (mem_insn) 
		      break;
            }
            if (!mem_insn) 
		    continue;

            rtx_insn *scan = NEXT_INSN (insn), *add_insn = NULL;
            rtx u_dest, u_op0, u_op1;
            for (int j = 0; j < 16 && scan; j++) {
              if (is_addw (scan, &u_dest, &u_op0, &u_op1))
	      {
                rtx f_idx = NULL_RTX, f_stride = NULL_RTX;
                if (REG_P(u_op0) && REGNO(u_op0) == REGNO(idx)) 
		{ 
		 f_idx = u_op0; 
		 f_stride = u_op1; 
		}
                else if (REG_P(u_op1) && REGNO(u_op1) == REGNO(idx)) 
		{ 
		 f_idx = u_op1; 
		 f_stride = u_op0; 
		}
                if (f_idx) 
		{ 
		  add_insn = scan; 
		  shared_stride = f_stride; 
		  target_idx = u_dest; 
		  break; 
		}
              }
              scan = NEXT_INSN (scan);
            }
            if (add_insn) 
		    chain.safe_push({insn, add_insn, mem_insn, dest, idx});
          }
        }
      }

      if (chain.length() >= 2 && shared_stride) {
        edge pre_edge = loop_preheader_edge (loop);
        rtx t6_stride = gen_reg_rtx (Pmode), current_ptr = gen_reg_rtx (Pmode);

        /* Hoist Stride Shift (SLLI) */
        start_sequence ();
        rtx s_prom = convert_to_mode (Pmode, shared_stride, 0);
        
        /* Attempt to fold the constant shift expression at compile time */
        rtx folded = simplify_binary_operation (ASHIFT, 
			Pmode, s_prom, const1_rtx);
        rtx_insn *s_insn;

        if (folded) {
            /* If it evaluates to a constant (e.g., 2), 
	     * emit a valid move instruction (li) */
            s_insn = emit_move_insn (t6_stride, folded);
        } else {
            /* If it's a variable, generate the hardware shift instruction */
            s_insn = emit_insn (gen_rtx_SET (t6_stride, 
				    gen_rtx_ASHIFT (Pmode, s_prom, 
					    const1_rtx)));
            recog_memoized (s_insn);
        }
        
        /* Force register to stay live */
        emit_insn (gen_rtx_USE (VOIDmode, t6_stride));
        rtx_insn *stride_seq = get_insns (); end_sequence ();
        insert_insn_on_edge (stride_seq, pre_edge);

        /* Hoist Initial Pointer (SH1ADD.UW) */
        start_sequence ();
        rtx init_idx = convert_to_mode (Pmode, chain[0].index_reg, 0);
        rtx shift = gen_rtx_ASHIFT (Pmode, init_idx, const1_rtx);
        rtx mask = gen_int_mode (
			(unsigned HOST_WIDE_INT)0xffffffff << 1, Pmode);
        rtx op0 = gen_rtx_AND (Pmode, shift, mask);
        rtx_insn *p_insn = emit_insn (gen_rtx_SET (current_ptr, 
				gen_rtx_PLUS (Pmode, op0, shared_base)));
        recog_memoized (p_insn);
        rtx_insn *init_seq = get_insns (); end_sequence ();
        insert_insn_on_edge (init_seq, pre_edge);

        /* Rewrite loop body: chain and rescan */
        rtx prev_ptr = current_ptr;
        for (unsigned j = 0; j < chain.length(); j++) {
          rtx this_ptr = (j == 0) ? current_ptr : gen_reg_rtx (Pmode);
          
          if (j > 0) {
            rtx_insn *new_add = emit_insn_before (gen_rtx_SET (this_ptr,
				gen_rtx_PLUS (Pmode, prev_ptr, t6_stride)),
				chain[j].sh1add_insn);
            recog_memoized (new_add);
            df_insn_rescan (new_add);
          }

          if (validate_replace_rtx (chain[j].dest_reg, this_ptr,
				  chain[j].mem_insn)) {
            df_insn_rescan (chain[j].mem_insn);
            delete_insn (chain[j].sh1add_insn);
            delete_insn (chain[j].addw_insn);
          }

          prev_ptr = this_ptr;
        }

        /* Latch Update */
        start_sequence ();
        emit_insn (gen_rtx_SET (current_ptr,
				gen_rtx_PLUS (Pmode, prev_ptr,
					t6_stride)));
        rtx_insn *latch_seq = get_insns (); end_sequence ();
        insert_insn_on_edge (latch_seq, loop_latch_edge (loop));

        changed = true;
      }
      free (bbs);
    }

    if (changed) {
      commit_edge_insertions ();
      cleanup_cfg (0);
    }
    
    loop_optimizer_finalize ();
    return 0;
  }
};

} // namespace

rtl_opt_pass * make_pass_riscv_matrix_opt (gcc::context *ctxt)
{
  return new pass_riscv_matrix_opt (ctxt);
}
