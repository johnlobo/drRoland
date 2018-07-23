//-----------------------------LICENSE NOTICE------------------------------------
//
//	|  _  \     / _ \              | |               | |
//	| | | |_ __/ /_\ \_ __ ___  ___| |_ _ __ __ _  __| |
//	| | | | '__|  _  | '_ ` _ \/ __| __| '__/ _` |/ _` |
//	| |/ /| |_ | | | | | | | | \__ \ |_| | | (_| | (_| |
//	|___/ |_(_)\_| |_/_| |_| |_|___/\__|_|  \__,_|\__,_|
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
#include <stdio.h>  //because sprintf
#include "defines.h"
#include "board.h"
#include "../game.h"
#include "../util/util.h"
#include "../text/text.h"

//////////////////////////////////////////////////////////////////
// initBoard
//
//  initializes the board
//
//  Input: void
//
//  Returns: void
//    

void initBoard(TBoard *board){
    u8 i,j;

    for (j=0;j<BOARD_HEIGHT;j++){
        for (i=0;i<BOARD_WIDTH;i++){
            board->color[j][i] = 0;
            board->content[j][i] = 0;
        }
    }
}

//////////////////////////////////////////////////////////////////
// fillRandomBoard
//
//  Fills the board with random tiles (debug)
//
//  Input: void
//
//  Returns: void
//    
void fillRandomBoard(TBoard *board){
    u8 i,j;

    for (j=0;j<BOARD_HEIGHT;j++){
        for (i=0;i<BOARD_WIDTH;i++){
            board->color[j][i] = (cpct_rand8() % 3)+1;
            board->content[j][i] = (cpct_rand8() % 6)+1;
        }
    }
}


//////////////////////////////////////////////////////////////////
// printBoard
//
//  prints the board on the screen
//
//  Input: void
//
//  Returns: void
//    
void printBoard(TBoard *board){
    u8 i,j;
    u8* pvmem;

    for (j=0;j<BOARD_HEIGHT;j++){
        for (i=0;i<BOARD_WIDTH;i++){
            if (board->content[j][i] != 0){
                pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (i*3), BOARD_ORIGIN_Y + (j*7));
                cpct_drawSprite(
                    sprites[board->color[j][i]][board->content[j][i]],
                    pvmem, 
                    dimension_W[board->color[j][i]][board->content[j][i]],
                    dimension_H[board->color[j][i]][board->content[j][i]]
                );
            }
        }
    }
}

void clearGameArea(){
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, BOARD_ORIGIN_X - SP_DOWNPILLS_0_W, BOARD_ORIGIN_Y - SP_DOWNPILLS_0_H);
    cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0), 10*SP_DOWNPILLS_0_W, 10*(SP_DOWNPILLS_0_H+1));
    pvmem = cpct_getScreenPtr(SCR_VMEM, BOARD_ORIGIN_X - SP_DOWNPILLS_0_W, BOARD_ORIGIN_Y+9*(SP_DOWNPILLS_0_H+1));
    cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0), 10*SP_DOWNPILLS_0_W, 8*(SP_DOWNPILLS_0_H+1));
}

void printScoreBoard1(){
    u8 aux_txt[20];

    drawWindow2(1,3,26,33,15,14);
    //Top
    drawText2("Top", 3, 9,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
    sprintf(aux_txt, "%5d", top);
    drawText2(aux_txt, 14, 9,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);   
    //Score
    drawText2("Score", 3, 18,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
    sprintf(aux_txt, "%5d", score);
    drawText2(aux_txt, 14, 18,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);   
    wait4OneKey();
}

void printScoreBoard2(){
    u8 aux_txt[20];

    drawWindow2(63,160,18,35, 15, 14);
    drawText2("Level", 65, 166,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
    sprintf(aux_txt, "%2d", level);
    drawText2(aux_txt, 74, 166,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);   
}
