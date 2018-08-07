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

#ifndef _BOARD_H_
#define _BOARD_H_

#include <cpctelera.h>
#include "bacteria.h"

#define BOARD_HEIGHT 16
#define BOARD_WIDTH 8
#define BOARD_ORIGIN_X 28
#define BOARD_ORIGIN_Y 76

typedef struct {
    u8 originX, originY;
    u8 color[16][8];
    u8 content[16][8];
    TBacteriaList bactList;
} TBoard;

extern TBoard board;
extern u8 const enemiesPerLevel[10];

void initBoard(TBoard *board);
void fillRandomBoard(TBoard *board);
void printBoard(TBoard *board);
void clearGameArea();
void printScoreBoard1();
void printScoreBoard2(TBoard *b);
u8 clearMatches(TBoard *b);
void applyGravity(TBoard *b);
void createBacterias(TBoard *b, u8 l);

#endif