/*
 * Copyright (C) 2010 Advanced Micro Devices, Inc.  All Rights Reserved.
 */

/********************************************************************\
|*                                                                  *|   
|*  Copyright (c) 2006 by SimpLight Nanoelectronics.                *|
|*  All rights reserved                                             *|
|*                                                                  *|
|*  This program is free software; you can redistribute it and/or   *|
|*  modify it under the terms of the GNU General Public License as  *|
|*  published by the Free Software Foundation; either version 2,    *|
|*  or (at your option) any later version.                          *|
|*                                                                  *|
\********************************************************************/

//  MIPS processor scheduling information
/////////////////////////////////////
//  
//  Description:
//
//  Generate a scheduling description of a MIPS processor
//  via the si_gen interface.
//
/////////////////////////////////////


//  $Revision: 1.12 $
//  $Date: 2006/04/28 08:27:55 $
//  $Author: weitang $
//  $Source: /depot/CVSROOT/javi/src/sw/cmplr/common/targ_info/proc/MIPS/sl2_pcore_si.cxx,v $


#include "si_gen.h"
#include "targ_isa_subset.h"
#include "topcode.h"

static RESOURCE res_issue,
                res_memory,	// Memory unit 
                res_float,	// Float unit
                res_integer,	// Integer unit
#ifdef TARG_SL
                res_cproc2,	// Co-processor 2
                res_spe,            // special register related unit
                res_mac,
                res_ffe,
                res_integer_or_memory, 
#endif 

#ifdef TARG_SL2
                res_sl2,            // sl2
                res_sl2_mem,  //sl2 load store
                res_sl2_vmult, 
                res_sl2_vadd, 
                res_sl2_mult, 
                res_sl2_add, 
                res_sl2_bit, 
                res_sl2_sum, 
                res_sl2_scan, 
                res_sl2_br, 
#endif 
                res_branch;	// Branch unit

void Generate_SL2_PCore (void)
{
  INT i;
  
  Machine("sl2_pcore", ISA_SUBSET_SL2);

  res_issue = RESOURCE_Create("issue", 4);
  res_memory = RESOURCE_Create("memory", 2);
  res_integer = RESOURCE_Create("integer", 2);
  res_float = RESOURCE_Create("float", 2);
  res_branch = RESOURCE_Create("branch", 1);

#ifdef TARG_SL
  res_cproc2 = RESOURCE_Create("cproc2", 1);
  res_mac = RESOURCE_Create("res_mac", 1);
  res_ffe = RESOURCE_Create("res_ffe", 1);
  res_integer_or_memory = RESOURCE_Create("res_int_or_mem", 3); 
#endif

#ifdef TARG_SL2
  res_sl2 = RESOURCE_Create("sl2", 1);
  res_sl2_br   = RESOURCE_Create("sl2_br", 1); 
  res_sl2_mem  = RESOURCE_Create("sl2_mem", 1);
  res_sl2_add  = RESOURCE_Create("sl2_add", 1); 
  res_sl2_bit  = RESOURCE_Create("sl2_bit", 1); 
  res_sl2_sum  = RESOURCE_Create("sl2_sum", 1); 
  res_sl2_mult = RESOURCE_Create("sl2_mult", 1); 
  res_sl2_scan = RESOURCE_Create("sl2_scan", 1); 
  res_sl2_vmult = RESOURCE_Create("sl2_vmult", 1); 
  res_sl2_vadd = RESOURCE_Create("sl2_vadd", 1); 
#endif


#if defined(TARG_SL)
  Instruction_Group("movespe",
                    TOP_mvtc,
                    TOP_mvtc_i,
                    TOP_mvtc16,
                    TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_integer_or_memory, 0); 
  Resource_Requirement(res_integer, 0);
  Resource_Requirement(res_issue,0);
#endif //targ_sl

  Instruction_Group("default",
		    TOP_add,
		    TOP_addi,
		    TOP_addiu,
		    TOP_addu,
		    TOP_slt,
		    TOP_slti,
		    TOP_sltiu,
		    TOP_sltu,
		    TOP_sub,
		    TOP_subu,
		    TOP_dadd,
		    TOP_daddi,
		    TOP_daddiu,
		    TOP_daddu,
		    TOP_dsub,
		    TOP_dsubu,
		    TOP_and,
		    TOP_andi,
		    TOP_lui,
		    TOP_nor,
		    TOP_or,
		    TOP_ori,
		    TOP_xor,
		    TOP_xori,
		    TOP_mfhi,
		    TOP_mflo,
		    TOP_mthi,
		    TOP_mtlo,
#ifdef TARG_SL		    
		    TOP_mc_abs,
		    TOP_mc_zc_eq,
        	    TOP_mc_zc_ne,
		    TOP_mc_zc_gt,
		    TOP_mc_zc_ge,
		    TOP_mc_zc_lt,
		    TOP_mc_zc_le,
           	    TOP_mc_z_eq,
		    TOP_mc_z_ne,
		    TOP_mc_z_gt,
		    TOP_mc_z_ge,
		    TOP_mc_z_lt,
		    TOP_mc_z_le,
		    TOP_mc_zn_eq,
		    TOP_mc_zn_ne,
		    TOP_mc_zn_gt,
		    TOP_mc_zn_ge,
		    TOP_mc_zn_lt,
		    TOP_mc_zn_le,
		    TOP_mc_r_eq,
		    TOP_mc_r_ne,
		    TOP_mc_r_gt,
		    TOP_mc_r_ge,
		    TOP_mc_r_lt,
		    TOP_mc_r_le,
		    TOP_depb,
		    TOP_extrbs,
		    TOP_extrbu,				
                    TOP_mvfc,
		    TOP_abs16,
                    TOP_add16,
                    TOP_add16_i,
                    TOP_add16_sp,
                    TOP_and16,
                    TOP_and16_i,
                    TOP_mv16,
                    TOP_mv16_i,
                    TOP_mvfc16,
                    TOP_nop16,
                    TOP_inv16,
                    TOP_or16,
                    TOP_or16_i,
                    TOP_shll16,
                    TOP_shll16_i,
                    TOP_shra16,
                    TOP_shra16_i,
                    TOP_shrl16,
                    TOP_shrl16_i,
                    TOP_sub16,
                    TOP_sub16_i,
                    TOP_xor16,
                    TOP_xor16_i,
#endif	
		    TOP_movf,
		    TOP_movn,
		    TOP_movt,
		    TOP_movz,
		    TOP_sll,
		    TOP_sllv,
		    TOP_sra,
		    TOP_srav,
		    TOP_srl,
		    TOP_srlv,
		    TOP_dsll,
		    TOP_dsll32,
		    TOP_dsllv,
		    TOP_dsra,
		    TOP_dsra32,
		    TOP_dsrav,
		    TOP_dsrl,
		    TOP_dsrl32,
		    TOP_dsrlv,
		    TOP_teq,
		    TOP_teqi,
		    TOP_tge,
		    TOP_tgei,
		    TOP_tgeiu,
		    TOP_tgeu,
		    TOP_tlt,
		    TOP_tlti,
		    TOP_tltiu,
		    TOP_tltu,
		    TOP_tne,
		    TOP_tnei,
		    TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_integer_or_memory, 0); 
  Resource_Requirement(res_integer, 0);
  Resource_Requirement(res_issue, 0);

  Instruction_Group("load",
		    TOP_lb,
		    TOP_lbu,
		    TOP_lh,
		    TOP_lhu,
		    TOP_lw,
		    TOP_lwl,
		    TOP_lwr,
		    TOP_lwu,
		    TOP_ld,
		    TOP_ldl,
		    TOP_ldr,
		    TOP_ll,
		    TOP_lld,
		    TOP_lwc1,
		    TOP_ldc1,
#ifdef TARG_SL
                   TOP_ldw16,
                    TOP_pop16,
                   TOP_ldub16_rs,
                   TOP_lduh16_rs,
#endif
		    TOP_lwxc1,
		    TOP_ldxc1,
		    TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(2);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_integer_or_memory, 0); 
  Resource_Requirement(res_memory, 0);
  Load_Access_Time(1);

  Instruction_Group("store",
		    TOP_sb,
		    TOP_sh,
		    TOP_sw,
		    TOP_swl,
		    TOP_swr,
		    TOP_sc,
		    TOP_sd,
		    TOP_sdl,
		    TOP_sdr,
		    TOP_scd,
		    TOP_swc1,
		    TOP_sdc1,
#ifdef TARG_SL
                    TOP_stw16,
                    TOP_push16,
#endif
		    TOP_swxc1,
		    TOP_sdxc1,
		    TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_integer_or_memory, 0); 
  Resource_Requirement(res_memory, 0);
  Store_Available_Time(1);

  Instruction_Group("branch",
		    TOP_beq,
		    TOP_bgez,
		    TOP_bgezal,
		    TOP_bgtz,
		    TOP_blez,
		    TOP_bltz,
		    TOP_bltzal,
		    TOP_bne,
		    TOP_j,
		    TOP_jal,
		    TOP_jalr,
		    TOP_jr,
		    TOP_syscall,
#if defined(TARG_SL)		    
                   TOP_br16_eqz,
                   TOP_br16_nez,
                    TOP_jr16,
                    TOP_jr16_lnk,
                    TOP_ret,
                    TOP_ret16,
#endif                    
		    TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_integer_or_memory, 0); 
  Resource_Requirement(res_integer, 0);
  Resource_Requirement(res_branch, 0);

#ifdef TARG_SL2

  Instruction_Group("sl2_mem",
      TOP_c2_ld_s_h_u_p,
      TOP_c2_ld_s_h_u,
      TOP_c2_ld_s_h_p,
      TOP_c2_ld_s_h,
      TOP_c2_ld_s_w_p,
      TOP_c2_ld_s_w,
      TOP_c2_st_s_h,
      TOP_c2_st_s_h_p,
      TOP_c2_st_s_w,
      TOP_c2_st_s_w_p,
      TOP_c2_ldi_s_h_u,
      TOP_c2_ldi_s_h,
      TOP_c2_ldi_s_w,
      TOP_c2_ldi_c,
      TOP_c2_sti_s_h,
      TOP_c2_sti_s_w,
      TOP_c2_sti_c,
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(2);
  Resource_Requirement(res_issue,0);
  Resource_Requirement(res_sl2_mem, 0);

  Instruction_Group("sl2_vbuf_store",
      TOP_c2_st_v_b,
      TOP_c2_st_v_h,
      TOP_c2_st_v_w,
      TOP_c2_st_v_m_b,
      TOP_c2_st_v_m_h,
      TOP_c2_st_v_m_w,
      TOP_c2_sti_v_b,
      TOP_c2_sti_v_h,
      TOP_c2_sti_v_w,
      TOP_c2_sti_v_m_b,
      TOP_c2_sti_v_m_h,
      TOP_c2_sti_v_m_w,
      TOP_c2_st_g2v_b, 
      TOP_c2_st_g2v_h, 
      TOP_c2_st_g2v_w, 
      TOP_c2_sti_g2v_b,   
      TOP_c2_sti_g2v_h,   
      TOP_c2_sti_g2v_w,   
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(4);
  Resource_Requirement(res_issue,0);
  Resource_Requirement(res_sl2_mem, 0);

  
  Instruction_Group("sl2_vbuf_load",
      TOP_c2_ld_v_b_u,
      TOP_c2_ld_v_b,
      TOP_c2_ld_v_h,
      TOP_c2_ld_v_w,
      TOP_c2_ld_v_sw,
      TOP_c2_ld_v_m_b_u,
      TOP_c2_ld_v_m_b,
      TOP_c2_ld_v_m_h,
      TOP_c2_ld_v_m_w,
      TOP_c2_ld_v2g_b_u,
      TOP_c2_ld_v2g_b,
      TOP_c2_ld_v2g_h_u, 
      TOP_c2_ld_v2g_h,   
      TOP_c2_ld_v2g_w,   
      TOP_c2_ldi_v2g_b_u, 
      TOP_c2_ldi_v2g_b,   
      TOP_c2_ldi_v2g_h_u, 
      TOP_c2_ldi_v2g_h,   
      TOP_c2_ldi_v2g_w,   
      TOP_c2_ldi_v_b_u,
      TOP_c2_ldi_v_b,
      TOP_c2_ldi_v_h,
      TOP_c2_ldi_v_w,
      TOP_c2_ldi_v_m_b_u,
      TOP_c2_ldi_v_m_b,
      TOP_c2_ldi_v_m_h,
      TOP_c2_ldi_v_m_w,
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(4);
  Resource_Requirement(res_issue,0);
  Resource_Requirement(res_sl2_mem, 0);




  Instruction_Group("sl2_mem_to_gpr",
      TOP_c2_mvgr_r2g_h_u,
      TOP_c2_mvgr_r2g_h,
      TOP_c2_mvgr_r2g_w,
      TOP_c2_mvgr_r2g_h_u_i,
      TOP_c2_mvgr_r2g_h_i,
      TOP_c2_mvgr_r2g_w_i,
      TOP_c2_mvgc_c2g,
      TOP_c2_mvgr_g2r_ba_lh,
      TOP_c2_mvgr_g2r_ba_hh,
      TOP_c2_mvgr_g2r_ba_w,
      TOP_c2_mvgr_g2r_lh,
      TOP_c2_mvgr_g2r_hh,
      TOP_c2_mvgr_g2r_w,
      TOP_c2_mvgr_g2r_lh_i,
      TOP_c2_mvgr_g2r_hh_i,
      TOP_c2_mvgr_g2r_w_i,
      TOP_c2_mvgr_g2r_bh,
      TOP_c2_mvgr_g2r_bh_u,
      TOP_c2_mvgr_g2r_bv,
      TOP_c2_mvgr_g2r_bv_u,
      TOP_c2_mvgr_g2r_b4_i,
      TOP_c2_mvgr_g2r_b4,      
      TOP_c2_mvgc_g2c,
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(2);
  Resource_Requirement(res_issue,0);
  Resource_Requirement(res_sl2_mem, 0);

  Instruction_Group("sl2_vadd",
      TOP_c2_vadds_h,
      TOP_c2_vadds_w,
      TOP_c2_vadds_p,
      TOP_c2_vadds_h_mode6,
      TOP_c2_vadds_h_mode2,
      TOP_c2_vadds_w_mode6,
      TOP_c2_vadds_w_mode2,
      TOP_c2_vadds_p_mode6,
      TOP_c2_vadds_p_mode2,
      TOP_c2_vsubs_h,
      TOP_c2_vsubs_h_sm,
      TOP_c2_vsubs_h_abs,
      TOP_c2_vsubs_h_abs_sm,
      TOP_c2_vabs_h,
      TOP_c2_vabs_h_sm,
      TOP_c2_vsubs_w,
      TOP_c2_vsubs_w_sm,
      TOP_c2_vsubs_w_abs,
      TOP_c2_vsubs_w_abs_sm,
      TOP_c2_vabs_w,
      TOP_c2_vabs_w_sm,
      TOP_c2_vsubs_p,
      TOP_c2_vsubs_p_sm,
      TOP_c2_vsubs_p_abs,
      TOP_c2_vsubs_p_abs_sm,
      TOP_c2_vabs_p,
      TOP_c2_vabs_p_sm,
      TOP_c2_vneg_h,
      TOP_c2_vneg_w,
      TOP_c2_vneg_p,
      TOP_c2_vshr_p,
      TOP_c2_vshr_h,
      TOP_c2_vshr_w,
      TOP_c2_vshl_p,
      TOP_c2_vshl_h,
      TOP_c2_vshl_w,
      TOP_c2_vclp,
      TOP_c2_vclp_p,
      TOP_c2_vclp_a,
      TOP_c2_vclp_s,
      TOP_c2_vclp_2,
      TOP_c2_vclp_n,
      TOP_c2_vclg_h_lt_and,
      TOP_c2_vclg_h_lt_or,
      TOP_c2_vclg_h_le_and,
      TOP_c2_vclg_h_le_or,
      TOP_c2_vclg_h_eq_and,
      TOP_c2_vclg_h_eq_or,
      TOP_c2_vclg_h_ge_and,
      TOP_c2_vclg_h_ge_or,
      TOP_c2_vclg_h_gt_and,
      TOP_c2_vclg_h_gt_or,
      TOP_c2_vclg_h_and,
      TOP_c2_vclg_h_or,
      TOP_c2_vclg_h_le,
      TOP_c2_vclg_h_lt,
      TOP_c2_vclg_h_ge,
      TOP_c2_vclg_h_gt,
      TOP_c2_vclg_w_lt_and,
      TOP_c2_vclg_w_lt_or,
      TOP_c2_vclg_w_le_and,
      TOP_c2_vclg_w_le_or,
      TOP_c2_vclg_w_eq_and,
      TOP_c2_vclg_w_eq_or,
      TOP_c2_vclg_w_ge_and,
      TOP_c2_vclg_w_ge_or,
      TOP_c2_vclg_w_gt_and,
      TOP_c2_vclg_w_gt_or,
      TOP_c2_vclg_w_and,
      TOP_c2_vclg_w_or,
      TOP_c2_vclg_w_le ,
      TOP_c2_vclg_w_lt ,
      TOP_c2_vclg_w_ge,
      TOP_c2_vclg_w_gt ,
      TOP_c2_vclg_p_lt_and,
      TOP_c2_vclg_p_lt_or,
      TOP_c2_vclg_p_le_and,
      TOP_c2_vclg_p_le_or,
      TOP_c2_vclg_p_eq_and,
      TOP_c2_vclg_p_eq_or,
      TOP_c2_vclg_p_ge_and,
      TOP_c2_vclg_p_ge_or,
      TOP_c2_vclg_p_gt_and,
      TOP_c2_vclg_p_gt_or,
      TOP_c2_vclg_p_and,
      TOP_c2_vclg_p_or,
      TOP_c2_vclg_p_le,
      TOP_c2_vclg_p_eq,
      TOP_c2_vclg_p_ge,
      TOP_c2_vclg_p_gt,
      TOP_c2_lczero_z,
      TOP_c2_lczero_nz_fw,
      TOP_c2_lczero_nz_bw,
      TOP_c2_vrnd_h,
      TOP_c2_vrnd_w,
      TOP_c2_vspas,
      TOP_c2_vcmpr_h_eq,
      TOP_c2_vcmpr_h_lt,
      TOP_c2_vcmpr_h_le,
      TOP_c2_vcmpr_h_gt,
      TOP_c2_vcmpr_h_ge,
      TOP_c2_vcmpr_w_eq,
      TOP_c2_vcmpr_w_lt,
      TOP_c2_vcmpr_w_le,
      TOP_c2_vcmpr_w_gt,
      TOP_c2_vcmpr_w_ge,
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue,0);
  Resource_Requirement(res_sl2_vadd, 0);


  Instruction_Group("sl2_vmult_no_bypass", 
      TOP_c2_vmul_h, 
      TOP_c2_vmul_w, 
      TOP_c2_vmov,
      TOP_c2_vmov_swin,
      TOP_UNDEFINED); 
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(3);
  Resource_Requirement(res_issue,0);
  Resource_Requirement(res_sl2_vmult, 0);


  
  Instruction_Group("sl2_vmult", 
      TOP_c2_vcmov_h_f,
      TOP_c2_vcmov_h_t,
      TOP_c2_vcmov_w_f,
      TOP_c2_vcmov_w_t,
      TOP_c2_mmul_h,
      TOP_c2_mmul_w,
      TOP_c2_vcopy, 
      TOP_UNDEFINED); 
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue,0);
  Resource_Requirement(res_sl2_vmult, 0);
     
  Instruction_Group("sl2_add_to_rf", 
      TOP_c2_add_shl_r_h_i,
      TOP_c2_add_shr_r_h_i,
      TOP_c2_add_shl_r_w_i,
      TOP_c2_add_shr_r_w_i,
      TOP_c2_add_shl_r_h,
      TOP_c2_add_shr_r_h,
      TOP_c2_add_shl_r_w,
      TOP_c2_add_shr_r_w,
      TOP_c2_subs_r_h_i,
      TOP_c2_subs_r_w_i,
      TOP_c2_sub_r_abs_h_i,
      TOP_c2_sub_r_abs_w_i,
      TOP_c2_subs_r_h,
      TOP_c2_subs_r_w,
      TOP_c2_sub_r_abs_h,
      TOP_c2_sub_r_abs_w,
      TOP_c2_scond_r_h_eq,
      TOP_c2_scond_r_h_lt,
      TOP_c2_scond_r_h_le,
      TOP_c2_scond_r_h_gt,
      TOP_c2_scond_r_h_ge,
      TOP_c2_scond_r_h_eq_i,
      TOP_c2_scond_r_h_lt_i,
      TOP_c2_scond_r_h_le_i,
      TOP_c2_scond_r_h_gt_i,
      TOP_c2_scond_r_h_ge_i,
      TOP_c2_scond_r_w_eq,
      TOP_c2_scond_r_w_lt,
      TOP_c2_scond_r_w_le,
      TOP_c2_scond_r_w_gt,
      TOP_c2_scond_r_w_ge,
      TOP_c2_scond_r_w_eq_i,
      TOP_c2_scond_r_w_lt_i,
      TOP_c2_scond_r_w_le_i,
      TOP_c2_scond_r_w_gt_i,
      TOP_c2_scond_r_w_ge_i,
      TOP_c2_scond_r_h_wb_eq,
      TOP_c2_scond_r_h_wb_lt,
      TOP_c2_scond_r_h_wb_le,
      TOP_c2_scond_r_h_wb_gt,
      TOP_c2_scond_r_h_wb_ge,
      TOP_c2_scond_r_wb_eq_i,
      TOP_c2_scond_r_wb_lt_i,
      TOP_c2_scond_r_wb_le_i,
      TOP_c2_scond_r_wb_gt_i,
      TOP_c2_scond_r_wb_ge_i,
      TOP_c2_scond_r_w_wb_eq,
      TOP_c2_scond_r_w_wb_lt,
      TOP_c2_scond_r_w_wb_le,
      TOP_c2_scond_r_w_wb_gt,
      TOP_c2_scond_r_w_wb_ge,      
      TOP_c2_scond_r_w_wb_eq_i,
      TOP_c2_scond_r_w_wb_lt_i,
      TOP_c2_scond_r_w_wb_le_i,
      TOP_c2_scond_r_w_wb_gt_i,
      TOP_c2_scond_r_w_wb_ge_i,      

      TOP_UNDEFINED);
  Any_Operand_Access_Time(0); 
  Any_Result_Available_Time(3);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2_add, 0);



  Instruction_Group("sl2_add_to_gpr", 
      TOP_c2_bcst_q,
      TOP_c2_bcst_i,
      TOP_c2_add_shl_g_i,
      TOP_c2_add_shr_g_i,
      TOP_c2_add_shl_g,
      TOP_c2_add_shr_g,
      TOP_c2_sub_g_abs_i,
      TOP_c2_subs_g_i,
      TOP_c2_sub_g_abs,
      TOP_c2_subs_g,
      TOP_c2_cmov,
      TOP_c2_clp,
      TOP_c2_clp_i,
      TOP_c2_chkrng,

      TOP_c2_scond_eq,
      TOP_c2_scond_lt,
      TOP_c2_scond_le,
      TOP_c2_scond_gt,
      TOP_c2_scond_ge,
      TOP_c2_scond_eq_i,
      TOP_c2_scond_lt_i,
      TOP_c2_scond_le_i,
      TOP_c2_scond_gt_i,
      TOP_c2_scond_ge_i,

      TOP_c2_shadd_l,
      TOP_c2_shadd_rl,
      TOP_c2_shadd_ra,
      TOP_c2_shsub_l,
      TOP_c2_shsub_rl, 
      TOP_c2_shsub_ra, 
      TOP_c2_shadd_l_i,
      TOP_c2_shadd_rl_i,
      TOP_c2_shadd_ra_i,
      TOP_c2_shsub_l_i,
      TOP_c2_shsub_rl_i, 
      TOP_c2_shsub_ra_i, 
     TOP_UNDEFINED);
  Any_Operand_Access_Time(0); 
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2_add, 0);





  Instruction_Group("sl2_med", 
      TOP_c2_med, 
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0); 
  Any_Result_Available_Time(2);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2_add, 0);
  Resource_Requirement(res_sl2_add, 1);
  	

  Instruction_Group("sl2_scan_to_rf", 
      TOP_c2_vlcs_dc,
      TOP_c2_vlcs_ac,
      TOP_UNDEFINED); 
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(3);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2_scan, 0);

  Instruction_Group("sl2_scan_to_gpr", 
      TOP_c2_vlcs_wb,
      TOP_UNDEFINED); 
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2_scan, 0);

  Instruction_Group("sl2_mult", 
      TOP_c2_muls,
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2_mult, 0);
      
  Instruction_Group("sl2_sum_to_rf", 
      TOP_c2_mov_r ,
      TOP_c2_mov_c_i,
      TOP_c2_mov_c,
      TOP_c2_mov_s_i, 
      TOP_c2_mov_s, 
      TOP_c2_sum4_c,
      TOP_c2_sum4_r ,
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(3);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2_sum, 0);


  Instruction_Group("sl2_sum_to_gpr", 
      TOP_c2_mov_g,
      TOP_c2_gsums,
      TOP_c2_wrap,
      TOP_c2_sum4_g,
      TOP_c2_sum4_sw,
      TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2_sum, 0);




  Instruction_Group("sl2_bit", 
      TOP_c2_bop_ls,
      TOP_c2_bop_rs,
      TOP_c2_bop_and,
      TOP_c2_bop_or,
      TOP_c2_bop_xor,
      TOP_c2_bop_andxor,
      TOP_c2_bop_ls_i,
      TOP_c2_bop_rs_i  ,
      TOP_c2_bop_and_i,
      TOP_c2_bop_or_i  ,
      TOP_c2_bop_xor_i,
      TOP_c2_bdep_l   ,
      TOP_c2_bdep_m ,
      TOP_c2_bxtr_u_l ,
      TOP_c2_bxtr_s_l ,
      TOP_c2_bxtr_u_m,
      TOP_c2_bxtr_s_m,
      TOP_c2_bxtrr48,
      TOP_c2_bxtrr48_i,
      TOP_c2_shor_l,
      TOP_c2_shor_rl,
      TOP_c2_shor_ra,
      TOP_c2_shor_l_i,
      TOP_c2_shor_rl_i,
      TOP_c2_shor_ra_i,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(1);
 Resource_Requirement(res_issue, 0);
 Resource_Requirement(res_sl2_bit, 0);

 Instruction_Group("sl2_br", 
      TOP_c2_fork_m,
      TOP_c2_fork_n ,
      TOP_c2_joint,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(3);
 Resource_Requirement(res_issue, 0);
 Resource_Requirement(res_sl2_br, 0);

 Instruction_Group("sl2_vspel_mul", 
      TOP_c2_vspel_mul_h,
      TOP_c2_vspel_mul_w,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(3);
 Resource_Requirement(res_issue, 0); 
 for(i = 0; i < 3; i++) {
   Resource_Requirement(res_sl2_vmult, i);
 }

 Instruction_Group("sl2_vspel_add",       
      TOP_c2_vspel_adds,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(3);
 Resource_Requirement(res_issue, 0); 
 for(i = 0; i< 3; i++) {
   Resource_Requirement(res_sl2_vadd, i);
 }

 Instruction_Group("sl2_vspel_mac",       
      TOP_c2_vspel_mac_h,
      TOP_c2_vspel_mac_w,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(3);
 Resource_Requirement(res_issue, 0); 
 Resource_Requirement(res_sl2_vmult, 0);
 Resource_Requirement(res_sl2_vadd, 1);

 Instruction_Group("sl2_vsad_tmp", 
      TOP_c2_sad, 
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(6);
 Resource_Requirement(res_issue, 0);
 Resource_Requirement(res_sl2_vadd, 0);
 for( i = 1; i < 5; i++) {
   Resource_Requirement(res_sl2_sum, i);
 }
 
 Instruction_Group("sl2_satd", 
      TOP_c2_satd, 
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(23);
 Resource_Requirement(res_issue, 0);
 for(i = 0; i < 10; i ++) {
   Resource_Requirement(res_sl2_vadd, i);
 }
 for(i = 10; i < 23; i++) {
   Resource_Requirement(res_sl2_vmult, i);
 }
      
 Instruction_Group("sl2_intra", 
      TOP_c2_intra,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(1);
 Resource_Requirement(res_issue, 0);
 Resource_Requirement(res_sl2_add, 0);
 Resource_Requirement(res_sl2_sum, 0);
 
 Instruction_Group("sl2_intra.mode.0.1.9.14.16", 
      TOP_c2_intra_0_1_9_14_16,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(7);
 Resource_Requirement(res_issue, 0);
 for(i = 0; i < 7; i++) {
   Resource_Requirement(res_sl2_sum, i);
 }


 Instruction_Group("sl2_intra.mode.15.17", 
      TOP_c2_intra_15_17,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(8);
 Resource_Requirement(res_issue, 0);
 for(i = 0; i < 8; i++) {
   Resource_Requirement(res_sl2_sum, i);
 }

 Instruction_Group("sl2_intra.mode.12.13", 
      TOP_c2_intra_12_13,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(4);
 Resource_Requirement(res_issue, 0);
 for(i = 0; i < 4; i++) {
   Resource_Requirement(res_sl2_sum, i);
  }


 Instruction_Group("sl2_intra.mode.2.3.8.10", 
      TOP_c2_intra_2_3_8_10,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(10);
 Resource_Requirement(res_issue, 0);
 for(i = 0; i < 4; i++) { 
   Resource_Requirement(res_sl2_add, i);
 }
 for(i = 4; i < 10; i++) {
   Resource_Requirement(res_sl2_sum, i);
 }

 Instruction_Group("sl2_intra.mode.4", 
      TOP_c2_intra_4,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(10);
 Resource_Requirement(res_issue, 0);
 for(i = 0; i < 5; i++) {
   Resource_Requirement(res_sl2_add, i);
 }
 for(i = 5; i < 10; i++) {
   Resource_Requirement(res_sl2_sum, i);
 }

 Instruction_Group("sl2_intra.mode.5.11", 
      TOP_c2_intra_5_11,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(7);
 Resource_Requirement(res_issue, 0);
for(i = 0; i < 3; i++) {
   Resource_Requirement(res_sl2_add, i);
}
for(i = 3; i < 7; i++) {
   Resource_Requirement(res_sl2_sum, i);
}

 Instruction_Group("sl2_intra.mode.6", 
      TOP_c2_intra_6,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(9);
 Resource_Requirement(res_issue, 0);
 for(i = 0; i < 9; i++) {
   Resource_Requirement(res_sl2_sum, i);
 }

 Instruction_Group("sl2_intra.mode.7", 
      TOP_c2_intra_7,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(8);
 Resource_Requirement(res_issue, 0); 
 for(i = 0; i < 4; i++) {
   Resource_Requirement(res_sl2_add, i);
 }
 for(i = 4; i < 8; i++) {
   Resource_Requirement(res_sl2_sum, i);
 }

 Instruction_Group("sl2_mvsel", 
      TOP_c2_mvsel_mode0,
      TOP_c2_mvsel_mode1,
      TOP_c2_mvsel_mode2,
      TOP_c2_mvsel_mode345,
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(2);
 Resource_Requirement(res_issue, 0);
 Resource_Requirement(res_sl2_add, 0);
 Resource_Requirement(res_sl2_mult, 1);

 Instruction_Group("sl2_smads", 
      TOP_c2_smads, 
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(1);
 Resource_Requirement(res_issue, 0);
 Resource_Requirement(res_sl2_mult, 0);
 Resource_Requirement(res_sl2_add, 1);
 

 Instruction_Group("sl2_mads", 
      TOP_c2_mads, 
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(2);
 Resource_Requirement(res_issue, 0);
 Resource_Requirement(res_sl2_mult, 0);
 Resource_Requirement(res_sl2_add, 1);

/* this macro instruction is used to represent two sequential c2.satd */ 
 Instruction_Group("sl2_macro", 
      TOP_c2_macro, 
      TOP_UNDEFINED);
 Any_Operand_Access_Time(0);
 Any_Result_Available_Time(25);
 Resource_Requirement(res_issue, 0);
 Resource_Requirement(res_sl2_vadd, 0);
 Resource_Requirement(res_sl2_vmult, 17);



  Instruction_Group("SL2",
      TOP_c2_min,
      TOP_c2_max,
      TOP_c2_clzob_zd, 
      TOP_c2_clzob_od, 
      TOP_c2_clzob_zd_i, 
      TOP_c2_clzob_od_i, 
      TOP_c2_thctrl_lock,
      TOP_c2_thctrl_unlock,
      TOP_c2_thctrl_deact,
      TOP_c2_thctrl_act,
      TOP_c2_thctrl_mode4, 
      TOP_c2_thctrl_mode5,
      TOP_c2_thctrl_mode6,
      TOP_c2_thctrl_mode7,
      TOP_c2_sum4_saddr, 
             TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_sl2, 0);
#endif // TARG_SL2



  Instruction_Group("sync",
		    TOP_sync,
		    TOP_UNDEFINED);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_integer_or_memory, 0);   
  Resource_Requirement(res_memory, 0);

  Instruction_Group("prefetch",
		    TOP_pref,
		    TOP_prefx,
		    TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_integer_or_memory, 0);   
  Resource_Requirement(res_memory, 0);

  Instruction_Group("nop",
		    TOP_nop,
		    TOP_break,
		    TOP_UNDEFINED);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_integer_or_memory, 0);   
  Resource_Requirement(res_integer, 0);

  Instruction_Group("dummy",
		    TOP_asm,
		    TOP_intrncall,
		    TOP_spadjust,
		    TOP_UNDEFINED);
  Any_Operand_Access_Time(0);
  Any_Result_Available_Time(1);
  Resource_Requirement(res_issue, 0);
  Resource_Requirement(res_integer_or_memory, 0);   
  Resource_Requirement(res_integer, 0);

  Machine_Done();
}
