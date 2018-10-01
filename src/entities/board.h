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

#ifndef _BOARD_H_
#define _BOARD_H_

#include <cpctelera.h>

#define BOARD_HEIGHT 16
#define BOARD_WIDTH 8
#define MAX_VIR_LIST 20

typedef struct{
    u8 x;
    u8 y;
    u8 type;
    u8 color;
} TVirus;

typedef struct{
    u8 count;
    TVirus virusList[MAX_VIR_LIST];
    u8 step;
    u32 lastUpdate;
} TVirusList;

typedef struct {
    u8 originX, originY;
    u8 scoreX, scoreY;
    u8 virusX, virusY;
    u8 color[16][8];
    u8 content[16][8];
    TVirusList virList;
    u32 score;
    u8 virusMatched;
} TBoard;

extern TBoard board1;
extern TBoard board2;

extern u8 const enemiesPerLevel[11];

void createVirus(TBoard *b, u8 l);
void addVirus(TVirusList *virlist, u8 x, u8 y, u8 type, u8 color);
void printVirusList(TBoard *b);
void initBoard(TBoard *b, u8 x, u8 y, u8 scX, u8 scY, u8 viX, u8 viY);
void fillRandomBoard(TBoard *b);
void printBoard(TBoard *b);
void clearGameArea(TBoard *b);
void printScoreBoard1(TBoard *b);
void printScoreBoard2(TBoard *b);
u8 clearMatches(TBoard *b);
void applyGravity(TBoard *b);
void animateVirusList(TBoard *b);
void printSingleVirusCount(TBoard *b);
void printScoreBoardVs1(TBoard *b1, TBoard *b2);
void printScoreBoardVs2(TBoard *b1, TBoard *b2);

#endif