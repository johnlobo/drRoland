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

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include <cpctelera.h>
#include "board.h"


typedef struct {
    u8 alive;
    u8 activePill;
    u8 moved;
    u8 x, y;        // Position
    u8 px, py;      // Previous position
    u8 position;    // 0 = horizontal | 1 = vertical
    u8 ppos;        // Previous position 
    u8 content[2];  // Content of the two halves of pill
    u8 color[2];    // Color of the two halves of pill
    u8 pcontent[2];
    u8 pcolor[2];
    u32 lastUpdate;
} TCursor;


void initCursor(TCursor *cursor, u8 *index);
void printCursor(TBoard *b, TCursor *cursor, u8 currentCoordinates);
void printCursor2(TCursor *cursor, u8 x, u8 y);
void printNextCursor(TCursor *cursor, u8 player);
u8 checkCollisionDown(TBoard *aux, TCursor *cursor);
u8 checkCollisionLeft(TBoard *b, TCursor *cursor);
u8 checkCollisionRight(TBoard *b, TCursor *cursor);


#endif