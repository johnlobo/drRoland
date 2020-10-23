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


//extern void cpc_GetSp(int *buffer, char height, char width, int *origin) __z88dk_callee;


//void delay(u32 cycles);
void clearScreen(u8 bgColor);
void drawWindow(u8 x, u8 y, u8 width, u8 height );
void drawBottleNeck(u8 x, u8 y, u8 width, u8 height, u8 fgColor, u8 bgColor);

u8 showMessage(u8 *message, u8 type);

u8 getNumber(u8 *message, u8 yy, u8 start, u8 end);

void drawCompressToScreen(u8 x, u8 y, u8 w, u8 h, u16 size, u8* comp_end);

#endif
