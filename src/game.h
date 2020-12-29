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

#ifndef _GAME_H_
#define _GAME_H_

#include <cpctelera.h>
#include "keyboard/keyboard.h"

typedef struct
{
    u8 title[21];
    u16 cursorSpeed;
    u8 numberOfVirus;
    u8 hazardType; // 0:No hazard; 1:One line; 2:Add virus
    u16 hazardFreq;
    u8 maxRow;
    u8 capsuleStep;
    u8 capsulesPerSpeedp;
    u8 scenario[11]; // Only create extra blocks in the last 10 lines
                     // First byte indicates if virus scenario
} TLevel;

extern u8 *const sprites[3][9];
extern u8 level;
//extern u8 virus1, virus2;
extern const TLevel levels[21];

void printBackground(u8 color);
void getString(TKeys *k, u8 *result, u8 *title);
void initSingleGame(u8 l);
void playSingleGame(TKeys *keys);
void initVsGame(u8 l);
void playVsGame(TKeys *keys, TKeys *keys2);

#endif