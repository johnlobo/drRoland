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

#ifndef _BACTERIA_H_
#define _BACTERIA_H_

#include <cpctelera.h>
#include "board.h"

typedef struct{
    u8 x;
    u8 y;
    u8 type;
    u8 color;
} TBacteria;

typedef struct{
    TBacteria bacteriaList[20];
    u8 count;
    u8 step;
    u32 lastUpdate;
} TBacteriaList;

extern TBacteriaList bacteriaList;

void initBacteriaList(TBacteriaList *bactlist);
void addBacteria(TBacteriaList *bactlist, u8 x, u8 y, u8 type, u8 color);
void deleteBacteria(TBacteriaList *bactlist, u8 index);
void printBacteriaList(TBacteriaList *bactlist);
void animateBacteriaList(TBacteriaList *bactlist);

#endif