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

#ifndef _GAME_H_
#define _GAME_H_

#include <cpctelera.h>
#include "keyboard/keyboard.h"

#define EMPTYCELL_WIDTH 3
#define EMPTYCELL_HEIGHT 7




extern u8* const sprites[3][9];
extern u8 const dimension_W[3][9];
extern u8 const dimension_H[3][9];
extern u8 const emptyCell[EMPTYCELL_WIDTH * EMPTYCELL_HEIGHT];
extern u16 top;
extern u16 score;
extern u8 level;
extern u8 virus;

void initGame();
void addScore(u16 sc);
void playGame(TKeys *keys);



#endif