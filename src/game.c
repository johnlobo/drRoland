//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2015 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include "defines.h"
#include "keyboard/keyboard.h"
#include "sprites/dr.h"
#include "sprites/ams.h"
#include "sprites/trad.h"
#include "sprites/leftpills.h"
#include "sprites/rightpills.h"


TKeys keys;

void initGame(){
u8 *pvmem;
u8 i,j;

cpct_memset(CPCT_VMEM_START, cpct_px2byteM0(0,0), 0x4000);   // Clear de Screen BGCOLOR=Black

for (j=0;j<13;j++){
    for (i=0;i<40;i++){
        if ((i%2)==(j%2)){
            pvmem = cpct_getScreenPtr(SCR_VMEM,i*4,j*16);
            cpct_drawSolidBox(pvmem, cpct_px2byteM0(2,2),4,8);
        }
    }
}


pvmem = cpct_getScreenPtr(SCR_VMEM, 10, 14);
cpct_drawSprite(bk_dr, pvmem, BK_DR_W, BK_DR_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 20, 10);
cpct_drawSprite(bk_ams, pvmem, BK_AMS_W, BK_AMS_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 38, 7);
cpct_drawSprite(bk_trad, pvmem, BK_TRAD_W, BK_TRAD_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 29, 100);
cpct_drawSprite(sp_leftpills_0, pvmem, SP_LEFTPILLS_0_W, SP_LEFTPILLS_0_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 31, 100);
cpct_drawSprite(sp_rightpills_0, pvmem, SP_RIGHTPILLS_0_W, SP_RIGHTPILLS_0_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 29, 107);
cpct_drawSprite(sp_leftpills_1, pvmem, SP_LEFTPILLS_1_W, SP_LEFTPILLS_1_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 31, 107);
cpct_drawSprite(sp_rightpills_1, pvmem, SP_RIGHTPILLS_1_W, SP_RIGHTPILLS_1_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 29, 115);
cpct_drawSprite(sp_leftpills_2, pvmem, SP_LEFTPILLS_2_W, SP_LEFTPILLS_2_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 31, 115);
cpct_drawSprite(sp_rightpills_2, pvmem, SP_RIGHTPILLS_2_W, SP_RIGHTPILLS_2_H);
wait4OneKey();
}

void playGame(){

}

