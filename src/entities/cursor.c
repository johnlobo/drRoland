//-----------------------------LICENSE NOTICE------------------------------------
//
//  /$$$$$$$                /$$$$$$$            /$$                           /$$
// | $$__  $$              | $$__  $$          | $$                          | $$
// | $$  \ $$  /$$$$$$     | $$  \ $$  /$$$$$$ | $$  /$$$$$$  /$$$$$$$   /$$$$$$$
// | $$  | $$ /$$__  $$    | $$$$$$$/ /$$__  $$| $$ |____  $$| $$__  $$ /$$__  $$
// | $$  | $$| $$  \__/    | $$__  $$| $$  \ $$| $$  /$$$$$$$| $$  \ $$| $$  | $$
// | $$  | $$| $$          | $$  \ $$| $$  | $$| $$ /$$__  $$| $$  | $$| $$  | $$
// | $$$$$$$/| $$       /$$| $$  | $$|  $$$$$$/| $$|  $$$$$$$| $$  | $$|  $$$$$$$
// |_______/ |__/      |__/|__/  |__/ \______/ |__/ \_______/|__/  |__/ \_______/
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
    cursor->px = 3;
    cursor->x = 3;
    cursor->py = 0;
    cursor->y = 0 ;
    cursor->position = 0;
    cursor->ppos = 0;
    cursor->content[0] = 3;
    cursor->content[1] = 4;
    cursor->color[0] = (cpct_rand8() % 3);
    cursor->color[1] = (cpct_rand8() % 3);
    cursor->pcontent[0] = cursor->content[0];
    cursor->pcontent[1] = cursor->content[1];
    cursor->pcolor[0] = cursor->color[0];
    cursor->pcolor[1] = cursor->color[1];
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
void printCursor(TBoard *b, TCursor *cursor, u8 currentCoordinates){
    u8 x,y,position,content0,content1,color0,color1;
    u8 *pvmem;
    
    if (currentCoordinates){
        x = cursor->x;
        y = cursor->y;
        position = cursor->position;
        content0 = cursor->content[0];
        content1 = cursor->content[1];
        color0 = cursor->color[0];
        color1 = cursor->color[1];
    } else {
        x = cursor->px;
        y = cursor->py;
        position = cursor->ppos;
        content0 = cursor->pcontent[0];
        content1 = cursor->pcontent[1];
        color0 = cursor->pcolor[0];
        color1 = cursor->pcolor[1];
    }
        
    // First half of the pill
    pvmem = cpct_getScreenPtr(
        CPCT_VMEM_START,
        b->originX + (x*CELL_WIDTH), 
        b->originY + (y*CELL_HEIGHT));
    cpct_drawSpriteBlended(        
        pvmem, 
        dimension_H[color0][content0],
        dimension_W[color0][content0],
        sprites[color0][content0] //substract 2 to get the vertical sprite
        );
    // Second half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
        b->originX + (x*CELL_WIDTH) + dimension_W[color0][content0] * (!position), 
        b->originY + (y*CELL_HEIGHT) + dimension_H[color0][content0] * position
    );
    cpct_drawSpriteBlended(        
        pvmem, 
        dimension_H[color1][content1],
        dimension_W[color1][content1],
        sprites[color1][content1] //substract 2 to get the vertical sprite
    );
}

//////////////////////////////////////////////////////////////////
//  printNextCursor
//
//  Prints the next Cursor on the screen
//
//  Input: cursor to print 
//
//  Returns: void
//    
void printNextCursor(TCursor *cursor, u8 player){
    u8 x,y,position,content0,content1,color0,color1;
    u8 *pvmem;
    
    if (player == PLAYER1){
        x = 63;
        y = 68;
    } else {
        x = 10;
        y = 68;
    }
    position = cursor->position;
    content0 = cursor->content[0];
    content1 = cursor->content[1];
    color0 = cursor->color[0];
    color1 = cursor->color[1];

    // First half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
    cpct_drawSprite(emptyCell, pvmem, dimension_W[color0][content0], dimension_H[color0][content0]);
    cpct_drawSprite(sprites[color0][content0], pvmem, dimension_W[color0][content0], dimension_H[color0][content0]);
    // Second half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
        x + (dimension_W[color0][content0] * (!position)), 
        y
        );
    cpct_drawSprite(emptyCell, pvmem, dimension_W[color1][content1], dimension_H[color1][content1]);
    cpct_drawSprite(sprites[color1][content1], pvmem, dimension_W[color1][content1], dimension_H[color1][content1]);
}

void exchangeCursors(TCursor *from, TCursor *to){
    TCursor aux;

    cpct_memcpy(&to, &aux, sizeof(TCursor));
    cpct_memcpy(&from, &to, sizeof(TCursor));
    cpct_memcpy(&aux, &from, sizeof(TCursor));
}


//////////////////////////////////////////////////////////////////
// CheckCollisionDown
//
//
//
// Returns: 1 if the cursor hits something, 0 if not.
//

u8 checkCollisionDown(TBoard *aux, TCursor *cursor){
    if (cursor->position == 1){
        if (cursor->y == 14){
            return YES;
        }
        // Check the cell two rows down if pill is vertical
        if (aux->content[cursor->y+2][cursor->x]){
            return YES;
        }
    } else {
        if (cursor->y == 15){
            return YES;
        }
        // Check two cells in the next row if pill is horizaontal
        if (aux->content[cursor->y+1][cursor->x] || aux->content[cursor->y+1][cursor->x+1]){
            return YES;
        }
    }
    return NO;
}

//////////////////////////////////////////////////////////////////
// CheckCollisionLeft
//
// 
//
// Returns: 1 if the cursor hits something, 0 if not.
//
//

u8 checkCollisionLeft(TBoard *b, TCursor *cursor){
    if (cursor->x == 0){
        return YES;
    }
    // Check one cell in the previous column if pill is horizaontal
    if (b->content[cursor->y][cursor->x-1]){
        return YES;
    // Check if pill is vertical and cell down-left is occupied 
    } else if ((cursor->position) && (b->content[cursor->y+1][cursor->x-1])){
        return YES;
    // No obstacles in the left
    } else return NO;
}

//////////////////////////////////////////////////////////////////
// CheckCollisionRight
//
// 
//
// Returns: 1 if the cursor hits something, 0 if not.
//
//
u8 checkCollisionRight(TBoard *b, TCursor *cursor){
    if (cursor->x == (7 - (!cursor->position))){  // If pill is horizontal substracts one to check
        return YES;
    }
    if (cursor->position){
        if ((b->content[cursor->y][cursor->x+1]) || (b->content[cursor->y+1][cursor->x+1])){
            return YES;
        }
    } else {
        // Check one cell in the next column if pill is horizaontal
        if (b->content[cursor->y][cursor->x+2]){
            return YES;    
        }
    }
    return NO;
}