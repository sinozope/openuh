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

 /* =========================================================================
  * =========================================================================
  * 
  * Module: loop_invar_hoist.h 
  * $Revision: 1.1.1.1 $
  * $Date: 2005/10/21 19:00:00 $ 
  * $Author: marcel $
  * $Source: /proj/osprey/CVS/open64/osprey1.0/be/cg/orc_ict/loop_invar_hoist.h,v $
  *
  * Revision comments:
  * 
  *    14-April-2003 - Initial version
  * 
  * ref the header of loop_invar_hoist.cxx for more descriptions. 
  *
  * =========================================================================
  * =========================================================================
  */
extern void Perform_Loop_Invariant_Code_Motion( LOOP_DESCR*, MEM_POOL*, BOOL );

#define OP_is_loop(o) (OP_code(o)==TOP_loop)
#define OP_is_mvtc(o) ( (OP_code(o)==TOP_mvtc_i) || (OP_code(o)==TOP_mvtc) )

static BOOL
Is_BB_Empty (BB *bb)
{
  for (OP *op = BB_first_op(bb); op != NULL; op = OP_next(op)) {
    if (OP_Real_Ops(op) != 0) return FALSE;
  }
  return TRUE;
}

static OP* BB_loop_op( BB *bb )
{
  OP *loop = NULL;
  FOR_ALL_BB_OPs_REV( bb, loop ){
    if( OP_is_loop(loop) )
      break;
  }
  return loop;
}


