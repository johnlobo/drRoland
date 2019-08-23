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
#ifndef _MATCH_H_
#define _MATCH_H_

#include <cpctelera.h>

#define MAX_MATCH_LIST 4

typedef struct
{
	u8 player; // PLAYER1 or PLAYER2
    u8 x, y;
    u8 direction;
    u8 count;
    u8 virus;
	u8 animStep;
	u32 lastUpdate;
} TMatch;

typedef struct
{
    TMatch list[MAX_MATCH_LIST];
    u8 count;
} TMatchList;

extern TMatchList animateMatchList;

void initMatch(TMatch *m);
void setMatch(TMatch* m, u8 p, u8 x, u8 y, u8 dir, u8 c, u8 v, u8 step);
void initMatchList(TMatchList *l) ;
void addMatch(TMatchList *l, TMatch *m);

#endif