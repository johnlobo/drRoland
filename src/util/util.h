//-----------------------------LICENSE NOTICE------------------------------------
///
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

#ifndef _UTIL_H_
#define _UTIL_H_

#include <cpctelera.h>
#include "../defines.h"


extern u16 fast_abs(i16 value) __z88dk_fastcall;
extern u8 fast_collision(u8 x1, u8 y1, u8 w1, u8 h1, u8 x2, u8 y2, u8 w2, u8 h2);
extern void reset_cpc();
extern void  cpc_GetSp(char *sprite, char alto, char ancho, int origin) __z88dk_callee;


//char *itoa(int value, char *result, int base);
void delay(u32 cycles);
//u8 hasReachedTarget(TEntity *e, u8 x, u8 y, i16 stepX, i16 stepY);
u16 distance (u16 x1, u16 y1, u16 x2, u16 y2);
i16 sign(i16 x);
u8 collision(u8 x1, u8 y1, u8 w1, u8 h1, u8 x2, u8 y2, u8 w2, u8 h2);
i16 abs(i16 value);

void clearScreen(u8 bgColor);

//void drawWindow2(u8 x, u8 y, u8 width, u8 height);
void drawWindow(u8 x, u8 y, u8 width, u8 height, u8 fgColor, u8 bgColor);
void drawBottleNeck(u8 x, u8 y, u8 width, u8 height, u8 fgColor, u8 bgColor);

void waitRaster(u8 ty);

#endif
