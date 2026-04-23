/* This pass identifies addressing patterns in memory-access intensive 
 * kernels. In such kernels an index is frequently scaled and added to a 
 * base pointer to access memory followed by an immediate index update.
 * The pass hoists the pointer arithmetic out of the loop header converting
 * index addressing into induction variables. */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "gimple.h"
#include "df.h"
#include "insn-config.h"
#include "recog.h"
#include "cfgloop.h"
#include "tree-pass.h"
#include "cfgrtl.h"
#include "expr.h"
#include "print-rtl.h"
#include "memmodel.h"
#include "emit-rtl.h"    
#include "cfgcleanup.h"  

namespace {

/* Structure to hold the instructions forming a single "step" in the
   address generation.  */
struct ladder_step 
{
  rtx_insn *sh1add_insn;
  rtx_insn *addw_insn; 
  rtx_insn *mem_insn;    
  rtx dest_reg;          
  rtx index_reg;         
};

const pass_data pass_data_riscv_matrix_opt = 
{
  RTL_PASS, 
  "riscv_matrix_opt", 
  OPTGROUP_NONE, 
  TV_NONE, 
  0, 0, 0, 0, 0,
};

class pass_riscv_matrix_opt : public rtl_opt_pass 
{
public:
  pass_riscv_matrix_opt (gcc::context *ctxt) 
    : rtl_opt_pass (pass_data_riscv_matrix_opt, ctxt) 
  {}

  /* Gate function to determine if the pass should execute. 
     Returns true if optimizations are enabled and the function name 
     matches the targeted kernel.  */
  virtual bool 
  gate (function *fun) override 
  { 
    const char *name = IDENTIFIER_POINTER (DECL_NAME (fun->decl));
    return (optimize > 0 && name && strcmp (name, "matrix_mul_matrix") == 0);
  }

  /* Main execution entry point for the RTL pass.  */
  virtual unsigned int execute (function *) override;

private:
  rtx unwrap_rtx (rtx x);
  bool mem_uses_reg_p (rtx_insn *insn, rtx addr_reg);
  void record_hoisting_ladder_steps (basic_block bb, auto_vec<ladder_step> &chain, 
                                    rtx *shared_base, rtx *shared_stride, 
                                    rtx *target_idx);
  bool is_sh1add_uw (rtx_insn *insn, rtx *dest, rtx *idx, rtx *base);
  rtx_insn *find_mem_insn (rtx_insn *insn, rtx dest);
  rtx_insn *find_index_update (rtx_insn *insn, rtx idx, rtx *stride, 
			       rtx *next_idx);
};

/* Remove SIGN_EXTEND ZERO_EXTEND or SUBREG from an RTX 
   to reach the underlying register or constant.  */
rtx
pass_riscv_matrix_opt::unwrap_rtx (rtx x) 
{
  if (!x) 
    return NULL_RTX;
  while (GET_CODE (x) == SIGN_EXTEND || 
	 GET_CODE (x) == ZERO_EXTEND || 
	 GET_CODE (x) == SUBREG)
    x = (GET_CODE (x) == SUBREG) ? SUBREG_REG (x) : XEXP (x, 0);
  return x;
}

/* Return true if INSN is a memory access whose address calculation 
   involves ADDR_REG.  */
bool
pass_riscv_matrix_opt::mem_uses_reg_p (rtx_insn *insn, rtx addr_reg) 
{
  rtx set = single_set (insn);
  if (!set) 
    return false;

  rtx src = SET_SRC (set);
  while (GET_CODE (src) == SIGN_EXTEND ||
         GET_CODE (src) == ZERO_EXTEND)
    src = XEXP (src, 0);

  if (!MEM_P (src)) 
    return false;

  rtx addr = XEXP (src, 0);
  if (REG_P (addr) && REGNO (addr) == REGNO (addr_reg)) 
    return true;
  
  if (GET_CODE (addr) == PLUS && REG_P (XEXP (addr, 0)) 
      && CONST_INT_P (XEXP (addr, 1)))
    return REGNO (XEXP (addr, 0)) == REGNO (addr_reg);
  
  return false;
}

/* Scan the basic block BB to find a pattern of address generations. 
   Identifies the shared base, stride and index register across a
   sequence of instructions and stores them in CHAIN.  */
void
pass_riscv_matrix_opt::record_hoisting_ladder_steps (basic_block bb, 
                                                    auto_vec<ladder_step> &chain, 
                                                    rtx *shared_base, 
                                                    rtx *shared_stride, 
                                                    rtx *target_idx) 
{
  rtx_insn *insn;
  FOR_BB_INSNS (bb, insn) 
    {
      if (!NONDEBUG_INSN_P (insn)) 
	continue;

      rtx d, idx, b;
      if (is_sh1add_uw (insn, &d, &idx, &b)) 
	{
	  if (chain.length () == 0) 
	    { 
	      *shared_base = b; 
	      *target_idx = idx; 
	    }
	  if (REGNO (b) != REGNO (*shared_base) 
	      || REGNO (idx) != REGNO (*target_idx)) 
	    continue;

	  rtx_insn *mem = find_mem_insn (insn, d);
	  rtx_insn *add_in = find_index_update (insn, idx, shared_stride, 
						target_idx);
	  
	  if (mem && add_in) 
	    chain.safe_push ({insn, add_in, mem, d, idx});
	}
    }
}

/* Example of what the phase is supposed to do.
Code before transformation:
.L4:
  //STEP 1: First Link
  sh1add.uw   a2, a5, s3   # A. sh1add_uw_p (Index: a5, Base: s3)          	
  lh          t6, 0(a2)    # B. mem_insn (ses result of A)
  addw        s8, a5, a0   # C. addw_p (pdates a5 -> s8 using stride a0)  	
                                                                           	
  #STEP 2: Second Link                                                     	
  sh1add.uw   s0, s8, s3   # D. sh1add_uw_p (index: s8, Base: s3)          	
  lh          a1, 0(s0)    # E. mem_insn (use result of D)                	
  addw        s1, s8, a0   # F. addw_p (updates s8 -> s1 using stride a0)  	
                                                                           	
  #STEP 3: Third Link                                                      	
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
	
unsigned int pass_riscv_matrix_opt::execute (function *) 
{
  loop_optimizer_init (LOOPS_NORMAL | LOOPS_HAVE_PREHEADERS);
  df_chain_add_problem (DF_DU_CHAIN | DF_UD_CHAIN);
  df_analyze ();

  bool changed = false;

  for (auto loop : loops_list (cfun, LI_FROM_INNERMOST)) 
    {
      if (loop->inner != NULL) 
	continue;
      
      basic_block bb = loop->header;
      auto_vec<ladder_step> chain;
      rtx shared_base = NULL_RTX, shared_stride = NULL_RTX, target_idx = NULL_RTX;

      record_hoisting_ladder_steps (bb, chain, &shared_base, &shared_stride, &target_idx);

      if (chain.length () >= 2 && shared_stride) 
	{
	  edge pre_edge = loop_preheader_edge (loop);
	  rtx t6_stride = gen_reg_rtx (Pmode), current_ptr = gen_reg_rtx (Pmode);

	  start_sequence ();
	  emit_insn (gen_rtx_SET (t6_stride, gen_rtx_ASHIFT 
		     (Pmode, convert_to_mode (Pmode, shared_stride, 0), 
		      const1_rtx)));
	  
	  rtx init_idx = convert_to_mode (Pmode, chain[0].index_reg, 0);
	  unsigned HOST_WIDE_INT mask_val = (unsigned HOST_WIDE_INT)0xffffffff << 1;
	  rtx mask = gen_int_mode (mask_val, Pmode);
	  rtx op0 = gen_rtx_AND (Pmode, gen_rtx_ASHIFT (Pmode, init_idx, 
							const1_rtx), mask);
	  emit_insn (gen_rtx_SET (current_ptr, gen_rtx_PLUS (Pmode, op0, 
							     shared_base)));
	  rtx_insn *pre_seq = get_insns (); 
	  end_sequence ();
	  insert_insn_on_edge (pre_seq, pre_edge);

	  rtx_insn *loop_top = BB_HEAD (bb);
	  while (loop_top && (GET_CODE (loop_top) == NOTE 
			      || GET_CODE (loop_top) == CODE_LABEL))
	    loop_top = NEXT_INSN (loop_top);

	  rtx prev_ptr = current_ptr;
	  for (unsigned j = 0; j < chain.length (); j++) 
	    {
	      rtx this_ptr = (j == 0) ? current_ptr : gen_reg_rtx (Pmode);
	      if (j > 0) 
		{
		  rtx_insn *ni = emit_insn_before (gen_rtx_SET (this_ptr, 
						   gen_rtx_PLUS (Pmode, prev_ptr, 
								 t6_stride)), 
						   loop_top);
		  df_insn_rescan (ni);
		}
	      validate_replace_rtx (chain[j].dest_reg, this_ptr, 
				    chain[j].mem_insn);
	      delete_insn (chain[j].sh1add_insn);
	      delete_insn (chain[j].addw_insn);
	      prev_ptr = this_ptr;
	    }

	  start_sequence ();
	  emit_insn (gen_rtx_SET (current_ptr, gen_rtx_PLUS (Pmode, prev_ptr, 
							     t6_stride)));
	  rtx_insn *latch_seq = get_insns (); 
	  end_sequence ();
	  insert_insn_on_edge (latch_seq, loop_latch_edge (loop));
	  changed = true;
	}
    }

  if (changed) 
    { 
      commit_edge_insertions (); 
      cleanup_cfg (0); 
    }
  loop_optimizer_finalize ();
  return 0;
}

/* Match sh1add.uw pattern: dest = (idx.uw << 1) + base. 
   Extracts the destination, index and base registers.  */
bool
pass_riscv_matrix_opt::is_sh1add_uw (rtx_insn *insn, rtx *dest, 
				    rtx *idx, rtx *base) 
{
  rtx set = single_set (insn);
  if (!set || GET_CODE (SET_SRC (set)) != PLUS) 
    return false;
  rtx op0 = XEXP (SET_SRC (set), 0);
  if (GET_CODE (op0) == AND) 
    op0 = XEXP (op0, 0);
  if (GET_CODE (op0) != ASHIFT || INTVAL (XEXP (op0, 1)) != 1) 
    return false;
  *dest = SET_DEST (set);
  *idx = unwrap_rtx (XEXP (op0, 0));
  *base = unwrap_rtx (XEXP (SET_SRC (set), 1));
  return (REG_P (*idx) && REG_P (*base));
}

/* Find the memory instruction (load/store) that consumes the 
   address calculated by INSN.  */
rtx_insn *
pass_riscv_matrix_opt::find_mem_insn (rtx_insn *insn, rtx dest) 
{
  for (df_ref def = DF_INSN_DEFS (insn); def; def = DF_REF_NEXT_LOC (def)) 
    for (struct df_link *l = DF_REF_CHAIN (def); l; l = l->next) 
      {
	rtx_insn *u = DF_REF_INSN (l->ref);
	if (u && mem_uses_reg_p (u, dest)) 
	  return u;
      }
  return NULL;
}

/* Search forward from INSN to find an update to the index register IDX. 
   Returns the instruction and extracts the stride value.  */
rtx_insn *
pass_riscv_matrix_opt::find_index_update (rtx_insn *insn, rtx idx, 
					  rtx *stride, rtx *next_idx) 
{
  rtx_insn *scan = NEXT_INSN (insn);
  for (int j = 0; j < 16 && scan; j++) 
    {
      rtx s = single_set (scan);
      if (s && GET_CODE (unwrap_rtx (SET_SRC (s))) == PLUS) 
	{
	  rtx p = unwrap_rtx (SET_SRC (s));
	  if (REGNO (unwrap_rtx (XEXP (p, 0))) == REGNO (idx)) 
	    {
	      *stride = unwrap_rtx (XEXP (p, 1));
	      *next_idx = SET_DEST (s);
	      return scan;
	    }
	}
      scan = NEXT_INSN (scan);
    }
  return NULL;
}

} 

/* Create a new instance of the riscv memory access optimization pass.  */
rtl_opt_pass *
make_pass_riscv_matrix_opt (gcc::context *ctxt) 
{ 
  return new pass_riscv_matrix_opt (ctxt); 
}
