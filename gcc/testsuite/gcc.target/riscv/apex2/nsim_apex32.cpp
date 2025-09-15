/*
<copyright>
     Copyright (C) 2024 Synopsys, Inc. This software and the associated
     documentation are confidential and proprietary to Synopsys, Inc.
     Your use or disclosure of this software is subject to the terms and
     conditions of a written license agreement between you, or your company,
     and Synopsys, Inc.
</copyright>
*/
#define OEM_USE_OF_NSIM_HEADER_FILES 1
#define BUILDING_DLL
#include "api/ext/api_ext_arcv.h"

#include <array>
#include <cstring>
#include <cstdlib>

#define DIRECT_XCSR_BASE  0xBC0
#define DIRECT_XCSR_COUNT 64

struct SampleExtension : ARCV_nsimext {
 private:
  ARCV_nsimext_simulator_access* sim_access;
  ARCV_op_info inst1, inst2, inst3, inst4, inst5, inst6, inst7;
  ARCV_op_info* inst_list_[8];
  ARCV_xcsr_info xcsr1, xcsr2, xcsr3, xcsr4;
  ARCV_xcsr_info* xcsr_list_[5];
  std::array<uint32, DIRECT_XCSR_COUNT> xcsr_value_array; 

 public:
  SampleExtension() {
    // Register extension instructions
    inst2.kind = XD_Type;
    inst2.major = 0xb;
    inst2.minor = 0x8;
    inst2.name  = "apex_xd_add";
    inst_list_[1] = &inst2;
  }
  
  uint32 MS_CDECL version() {
    return ARCV_NSIMEXT_BASE_VERSION;
  }
  
  const char* MS_CDECL get_name() {
    return "SampleExtension";
  }
  
  void MS_CDECL destroy() {
    /* EMPTY */
  };
  
  void MS_CDECL set_simulator_access(ARCV_nsimext_simulator_access* sa) {
    sim_access = sa;
  }

  uint32 MS_CDECL prepare_for_new_simulation() {
    return 1;
  }
  
  /** Extension Instruction **/
  ARCV_op_info** MS_CDECL opcode_list() {
    return inst_list_;
  }
  
  uint32 MS_CDECL perform_opcode(struct ARCV_op_info *info,
                                 struct ARCV_decode_state state) {
    uint32 src1 = 0;
    uint32 src2 = 0;
    uint32 dst  = 0;
    if (state.num_sources >= 1)
       src1 = state.sources[0].operand;
    if (state.num_sources >= 2)
       src2 = state.sources[1].operand;
    switch(info->kind) {
       case XD_Type: {
          switch(info->minor) {
             case 0x8: {
                if (state.num_dests != 0) {
                   dst = src1 + src2;
                   sim_access->write_core_reg(state.dests[0].operand, dst, ARCV_from_execution);
                   return 1;
                }
                break;
             }
             default: break;
          }
          return 0;
       }
       default: break;
    }
    return 0;
  }
                                 
  /** Extension csr **/
  ARCV_xcsr_info** MS_CDECL xcsr_list() {
    return xcsr_list_;
  }
  
  ARCV_xcsr_info** MS_CDECL ixcsr_list() {
    return 0;
  }
  
  uint32 MS_CDECL read_xcsr(struct ARCV_xcsr_info* info, uint64 *value, uint8 context) {
    *value = xcsr_value_array[info->address - DIRECT_XCSR_BASE];
    return ARCV_ISA_ext_res_ok;
  }

  uint32 MS_CDECL write_xcsr(struct ARCV_xcsr_info* info, uint64 value, uint8 context) {
    xcsr_value_array[info->address - DIRECT_XCSR_BASE] = value;
    return ARCV_ISA_ext_res_ok;
  }  
  
  uint32 MS_CDECL read_ixcsr(struct ARCV_xcsr_info* info, uint64 *value, uint8 context) {
    return ARCV_ISA_ext_res_ok;
  }
  
  uint32 MS_CDECL write_ixcsr(struct ARCV_xcsr_info* info, uint64 value, uint8 context) {
    return ARCV_ISA_ext_res_ok;
  }  
};

#ifdef __cplusplus
extern "C" {
#endif
  
  DLLEXPORT ARCV_nsimext* get_ARCV_nsimext_interface() {
    ARCV_nsimext *p = new SampleExtension;
    return p;
  }
  
#ifdef __cplusplus
}
#endif
