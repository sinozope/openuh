/*
  Copyright (C) 2000-2003, Institute of Computing Technology, Chinese Academy of Sciences
  All rights reserved.
  
  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:
  
  Redistributions of source code must retain the above copyright notice, this list
  of conditions and the following disclaimer. 

  Redistributions in binary form must reproduce the above copyright notice, this list
  of conditions and the following disclaimer in the documentation and/or other materials
  provided with the distribution. 

  Neither the name of the owner nor the names of its contributors may be used to endorse or
  promote products derived from this software without specific prior written permission. 

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
 
//-*-c++-*-

//*********************************************************************
//
// Module: ipfec.h
// $Date: 2005/12/30 01:47:13 $
// $Author: weitang $
// $Source: /depot/CVSROOT/javi/src/sw/cmplr/be/cg/region/ipfec.h,v $
//
// Description:
//
// Interface to ORC phases.
// This file should only contain declarations of types, variables, and
// functions used in CG driver (CG_Generate_Code).
//
//*********************************************************************

#ifndef ipfec_INCLUDED
#define ipfec_INCLUDED

#include "region.h"
#include "prdb.h"
#include "if_conv.h"

// Driver of the local instruction scheduling.
extern void Local_Insn_Sched(BOOL before_regalloc);

// Driver of the sepearted bundling phase.
extern void CGGRP_Bundle();

// Driver of the global instruction scheduling.
extern void Global_Insn_Sched(REGION_TREE* region_tree, BOOL before_regalloc);
extern void Global_Insn_Merge_Splitted_BBs () ;

// Driver of recovery code generation.
extern int Generate_Recovery_Code();

// Multi-Branch Post process 
extern void Post_Multi_Branch();
extern void Check_Cross_Boundary();
#endif

