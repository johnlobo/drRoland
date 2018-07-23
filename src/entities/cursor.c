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
#include "../defines.h"
#include "cursor.h"
#include "board.h"
#include "../game.h"

//////////////////////////////////////////////////////////////////
//  initCursor
//
//  Initialize a cursor
//
//  Input: cursor to print and coordinates... 1=current : 0=previous
//
//  Returns: void
//    
void initCursor(TCursor *cursor){
    cursor->px = 4;
    cursor->x = 4;
    cursor->py = 0;
    cursor->y = 0;
    cursor->position = 0;
    cursor->content[0] = 3;
    cursor->color[0] = (cpct_rand8() % 3);
    cursor->content[1] = 4;
    cursor->color[1] = (cpct_rand8() % 3);
    cursor->moved = 0;
    cursor->lastUpdate = i_time;
}

//////////////////////////////////////////////////////////////////
//  printCursor
//
//  Prints a Cursor on the screen on its current coordinates or the previous
//
//  Input: cursor to print and coordinates... 1=current : 0=previous
//
//  Returns: void
//    
void printCursor(TCursor *cursor, u8 currentCoordinates){
    u8 x,y;
    u8 incX, incY;
    u8 *pvmem;
    
    if (currentCoordinates){
        x = cursor->x;
        y = cursor->y;
    } else {
        x = cursor->px;
        y = cursor->py;
    }
        
    // the increment to draw the pills depend on the position of the pill
    incX = !cursor->position;
    incY = cursor->position;
    // First half of the pill
    pvmem = cpct_getScreenPtr(
        CPCT_VMEM_START,
        BOARD_ORIGIN_X + (x*3), 
        BOARD_ORIGIN_Y + (y*7));
    cpct_drawSpriteBlended(        
        pvmem, 
        dimension_H[cursor->color[0]][cursor->content[0]],
        dimension_W[cursor->color[0]][cursor->content[0]],
        sprites[cursor->color[0]][cursor->content[0]]
        );
    // Second half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
        BOARD_ORIGIN_X + (x*3) + dimension_W[cursor->color[0]][cursor->content[0]] * incX, 
        BOARD_ORIGIN_Y + (y*7) + dimension_H[cursor->color[0]][cursor->content[0]] * incY
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
    if (cursor->x == 0){
        return YES;
    }
    // Check one cell in the previous column if pill is horizaontal
    if (board->content[cursor->y][cursor->x-1]){
        return YES;
    // Check if pill is vertical and cell down-left is occupied 
    } else if ((cursor->position) && (board->content[cursor->y+1][cursor->x-1])){
        return YES;
    // No obstacles in the left
    } else return NO;
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
    if (cursor->x == 14){
        return YES;
    }
    // Check one cell in the next column if pill is horizaontal
    if (board->content[cursor->y][cursor->x+1]){
        return 1;
    // Check if pill is vertical and cell down-rigth is occupied 
    } else if ((cursor->position) && (board->content[cursor->y+1][cursor->x+1])){
        return 1;
    // No obstacles in the left
    } else return 0;
}