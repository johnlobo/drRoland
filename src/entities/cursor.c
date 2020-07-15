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
void initCursor(TCursor *cursor, u8 *index)
{
    cursor->px = 3;
    cursor->x = 3;
    cursor->py = 0;
    cursor->y = 0;
    cursor->position = 0;
    cursor->ppos = 0;
    cursor->content[0] = 3;
    cursor->content[1] = 4;
    cursor->color[0] = pillQueue[*index].color[0];
    cursor->color[1] = pillQueue[*index].color[1];
    // pillQueue is a circular buffer, so we have to check if we have reached the end
    if (*index == 128)
    {
        *index = 0;
    }
    else
    {
        *index += 1;
    }
    cursor->pcontent[0] = cursor->content[0];
    cursor->pcontent[1] = cursor->content[1];
    cursor->pcolor[0] = cursor->color[0];
    cursor->pcolor[1] = cursor->color[1];
    cursor->moved = NO;
    cursor->alive = YES;
    cursor->activePill = NO;
    cursor->lastUpdate = i_time;
}

//////////////////////////////////////////////////////////////////
//  printCursor2
//
//  Prints a Cursor on the screen on its current coordinates or the previous
//  Input: cursor to print and coordinates... 1=current : 0=previous
//  Returns: void
//
void printCursor2(TCursor *cursor, u8 x, u8 y)
{
    u8 *pvmem;
    // First half of the pill
    pvmem = cpct_getScreenPtr(
        CPCT_VMEM_START, x, y);
    cpct_drawSprite(
        sprites[cursor->color[0]][cursor->content[0]],
        pvmem,
        CELL_WIDTH,
        CELL_HEIGHT);
    // Second half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, x + CELL_WIDTH, y);
    cpct_drawSprite(
        sprites[cursor->color[1]][cursor->content[1]],
        pvmem,
        CELL_WIDTH,
        CELL_HEIGHT);
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
void printCursor(TBoard *b, TCursor *cursor, u8 currentCoordinates)
{
    u8 x, y, position, content0, content1, color0, color1;
    u8 *pvmem;

    if (currentCoordinates)
    {
        x = cursor->x;
        y = cursor->y;
        position = cursor->position;
        content0 = cursor->content[0];
        content1 = cursor->content[1];
        color0 = cursor->color[0];
        color1 = cursor->color[1];
    }
    else
    {
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
        b->originX + (x * CELL_WIDTH),
        b->originY + (y * CELL_HEIGHT));
    cpct_drawSpriteBlended(
        pvmem,
        CELL_HEIGHT,
        CELL_WIDTH,
        sprites[color0][content0] //substract 2 to get the vertical sprite
    );
    // Second half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
                              b->originX + (x * CELL_WIDTH) + CELL_WIDTH * (!position),
                              b->originY + (y * CELL_HEIGHT) + CELL_HEIGHT * position);
    cpct_drawSpriteBlended(
        pvmem,
        CELL_HEIGHT,
        CELL_WIDTH,
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
void printNextCursor(TCursor *cursor, u8 player)
{
    u8 x, y, position, content0, content1, color0, color1;
    u8 *pvmem;

    if (player == PLAYER1)
    {
        x = 62;
        y = 82;
    }
    else if (player == PLAYER1_VS)
    {
        x = 62;
        y = 56;
    }
    else
    {
        x = 12;
        y = 56;
    }
    position = cursor->position;
    content0 = cursor->content[0];
    content1 = cursor->content[1];
    color0 = cursor->color[0];
    color1 = cursor->color[1];

    // First half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
    cpct_drawSprite(emptyCell, pvmem, CELL_WIDTH, CELL_HEIGHT);
    cpct_drawSprite(sprites[color0][content0], pvmem, CELL_WIDTH, CELL_HEIGHT);
    // Second half of the pill
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
                              x + (CELL_WIDTH * (!position)),
                              y);
    cpct_drawSprite(emptyCell, pvmem, CELL_WIDTH, CELL_HEIGHT);
    cpct_drawSprite(sprites[color1][content1], pvmem, CELL_WIDTH, CELL_HEIGHT);
}

void exchangeCursors(TCursor *from, TCursor *to)
{
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

u8 checkCollisionDown(TBoard *b, TCursor *cur)
{
    if (cur->position == VERTICAL)
    {
        // Check the cell two rows down if pill is vertical
        if ((cur->y == 14) || (b->content[cur->y + 2][cur->x]))
        {
            return YES;
        }
    }
    // Check two cells in the next row if pill is horizaontal
    else if ((cur->y == 15) || (b->content[cur->y + 1][cur->x] || b->content[cur->y + 1][cur->x + 1]))
    {
        return YES;
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

u8 checkCollisionLeft(TBoard *b, TCursor *cursor)
{
    if (cursor->x == 0)
    {
        return YES;
    }
    // Check one cell in the previous column if pill is horizaontal
    if (b->content[cursor->y][cursor->x - 1])
    {
        return YES;
        // Check if pill is vertical and cell down-left is occupied
    }
    else if ((cursor->position) && (b->content[cursor->y + 1][cursor->x - 1]))
    {
        return YES;
        // No obstacles in the left
    }
    else
        return NO;
}

//////////////////////////////////////////////////////////////////
// CheckCollisionRight
//
//
//
// Returns: 1 if the cursor hits something, 0 if not.
//
//
u8 checkCollisionRight(TBoard *b, TCursor *cursor)
{
    if (cursor->x == (7 - (!cursor->position)))
    { // If pill is horizontal substracts one to check
        return YES;
    }
    if (cursor->position)
    {
        if ((b->content[cursor->y][cursor->x + 1]) || (b->content[cursor->y + 1][cursor->x + 1]))
        {
            return YES;
        }
    }
    else
    {
        // Check one cell in the next column if pill is horizaontal
        if (b->content[cursor->y][cursor->x + 2])
        {
            return YES;
        }
    }
    return NO;
}