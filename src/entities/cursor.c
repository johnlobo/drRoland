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
#include "cursor.h"
#include "board.h"
#include "../game.h"

void createCursor(TCursor *cursor){
    cursor->x = 4;
    cursor->y = 0;
    cursor->position = 0;
    cursor->content[0] = 3;
    cursor->color[0] = (cpct_rand8() % 3);
    cursor->content[1] = 4;
    cursor->color[1] = (cpct_rand8() % 3);
}

void printCursor(TCursor *cursor){
    u8 incX, incY;
    u8 *pvmem;
    
    // the increment to draw the pills depend on the position of the pill
    incX = !cursor->position;
    incY = cursor->position;
    // First half of the pill
    pvmem = cpct_getScreenPtr(
        CPCT_VMEM_START,
        BOARD_ORIGIN_X + (cursor->x*3), 
        BOARD_ORIGIN_Y + (cursor->y*6));
    cpct_drawSpriteBlended(        
        pvmem, 
        dimension_H[cursor->color[0]][cursor->content[0]],
        dimension_W[cursor->color[0]][cursor->content[0]],
        sprites[cursor->color[0]][cursor->content[0]]
        );
    // Second half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
        BOARD_ORIGIN_X + (cursor->x*3) + dimension_W[cursor->color[0]][cursor->content[0]] * incX, 
        BOARD_ORIGIN_Y + (cursor->y*6) + dimension_H[cursor->color[0]][cursor->content[0]] * incY
    );
    cpct_drawSpriteBlended(        
        pvmem, 
        dimension_H[cursor->color[1]][cursor->content[1]],
        dimension_W[cursor->color[1]][cursor->content[1]],
        sprites[cursor->color[1]][cursor->content[1]]
    );
}

void rotateCursor(TCursor *cursor){
    cursor->position = !cursor->position;
    //Change pills sense
    cursor->content[0]=cursor->position;
    cursor->content[1]=!cursor->position;
}




//////////////////////////////////////////////////////////////////
// CheckCollisionLeft
//
// 
// 
//
// Returns: 1 if the cursor hits something, 0 if not.
//
//

u8 checkCollisionLeft(TBoard *board, TCursor *cursor){
    // Check one cell in the previous column if pill is horizaontal
    if (board->content[cursor->y][cursor->x-1]){
        return 1;
    // Check if pill is vertical and cell down-left is occupied 
    } else if ((cursor->position) && (board->content[cursor->y+1][cursor->x-1])){
        return 1;
    // No obstacles in the left
    } else return 0;
}

//////////////////////////////////////////////////////////////////
// CheckCollisionRight
//
// 
// 
//
// Returns: 1 if the cursor hits something, 0 if not.
//
//
u8 checkCollisionRight(TBoard *board, TCursor *cursor){
    // Check one cell in the next column if pill is horizaontal
    if (board->content[cursor->y][cursor->x+1]){
        return 1;
    // Check if pill is vertical and cell down-rigth is occupied 
    } else if ((cursor->position) && (board->content[cursor->y+1][cursor->x+1])){
        return 1;
    // No obstacles in the left
    } else return 0;
}