#ifndef GCC_ARC64_PROTOS_H
#define GCC_ARC64_PROTOS_H

extern int arc64_epilogue_uses (int);
extern HOST_WIDE_INT arc64_initial_elimination_offset (unsigned, unsigned);
extern void arc64_init_expanders (void);
extern void arc64_cpu_cpp_builtins (cpp_reader *);

#ifdef RTX_CODE

extern rtx arc64_return_addr (int, rtx);
extern machine_mode arc64_select_cc_mode (enum rtx_code, rtx, rtx);
extern bool arc64_check_mov_const (HOST_WIDE_INT );
extern bool arc64_split_mov_const (rtx *);
extern bool arc64_can_use_return_insn_p (void);
extern void arc64_expand_call (rtx, rtx, bool);
extern rtx arc64_gen_compare_reg (enum rtx_code, rtx, rtx);
extern bool arc64_prepare_move_operands (rtx, rtx, machine_mode);

#endif /* RTX_CODE */

#endif /* GCC_ARC64_PROTOS_H */
