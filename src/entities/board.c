//-----------------------------LICENSE NOTICE------------------------------------
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include "defines.h"
#include "../game.h"
#include "board.h"

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
            board->content[j][i] = (cpct_rand8() % 5)+1;
        }
    }
}

//////////////////////////////////////////////////////////////////
// createBacterias
//
//  Create an specific number of baterias in a board
//
//  Input: void
//
//  Returns: void
//
void createBacterias(u8 number, TBoard *board){
    u8 count;
    u8 x,y;

    count = 0;

    do {
        x = (cpct_rand8() % 8);
        y = (cpct_rand8() % 16);
        if (board->content[y][x] == 0){
            board->content[y][x] = 6;  // 6 is Bacteria order in the content array;
            board->color[y][x] = (cpct_rand8() % 3);  // Assign a random color 
            count++;
        }
    } while (count < number);
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