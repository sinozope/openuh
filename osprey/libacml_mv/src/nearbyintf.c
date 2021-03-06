
/*
*  Copyright (C) 2008-2009 Advanced Micro Devices, Inc. All Rights Reserved.
*
*  This file is part of libacml_mv.
*
*  libacml_mv is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  libacml_mv is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with libacml_mv.  If not, see
*  <http://www.gnu.org/licenses/>.
*
*/


#include "../inc/libm_amd.h"
#include "../inc/libm_util_amd.h"


float FN_PROTOTYPE(nearbyintf)(float x)
{
    /* Check for input range */
    UT32 checkbits,sign,val_2p23;
    checkbits.f32=x;

    /* Clear the sign bit and check if the value can be rounded(i.e check if exponent less than 23) */
    if( (checkbits.u32 & 0x7FFFFFFF) > 0x4B000000)
    {
      /* take care of nan or inf */
      if((checkbits.u32 & 0x7f800000)== 0x7f800000)
          return x+x;
      else
          return x;
    }

    sign.u32 =  checkbits.u32 & 0x80000000;   
    val_2p23.u32 = sign.u32 | 0x4B000000;
    val_2p23.f32 = (x + val_2p23.f32) - val_2p23.f32;
    /*This extra line is to take care of denormals and various rounding modes*/
    val_2p23.u32 = ((val_2p23.u32 << 1) >> 1) | sign.u32;
    return (val_2p23.f32);   
}

