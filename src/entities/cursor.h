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

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include <cpctelera.h>
#include "board.h"


typedef struct {
    u8 x, y;        // Position
    u8 px, py;      // Previous position
    u8 position;    // 0 = horizontal | 1 = vertical
    u8 content[2];  // Content of the two halves of pill
    u8 color[2];    // Color of the two halves of pill
} TCursor;

//u8 checkCollisionDown(TBoard *board, TCursor *cursor);
void createCursor(TCursor *cursor);
void printCursor(TCursor *cursor);
void rotateCursor(TCursor *cursor);

//u8 checkCollisionLeft(TBoard *board, TCursor *cursor);
//u8 checkCollisionRight(TBoard *board, TCursor *cursor);

#endif