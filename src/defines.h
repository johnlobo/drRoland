
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
#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <cpctelera.h>

// Program Stack locations
#define NEW_STACK_LOCATION (void*)0x1ff

// Pointers to the hardware backbuffer, placed in bank 1
// of the memory (0x8000-0xBFFF)
#define SCR_VMEM  (u8*)0xC000
#define SCR_BUFF  (u8*)0x8000

#define YES 1
#define NO 0

#define HORIZONTAL 0
#define VERTICAL 1

#define PREVIOUS 0
#define CURRENT 1
#define NEXT 2

//Font Size
#define FONT_H 5
#define FONT_W 2

#define min(X, Y) ((X) < (Y) ? (X) : (Y))
#define max(X, Y) (X > Y ? X : Y)

extern const u8 sp_palette0[16]; // Regular palette
//extern const u8 sp_palette1[16]; // Palette with transparent color
extern u8 g_nInterrupt;	// Manage Interrupt and locate raytrace
extern u32 i_time;

// Declare am_tablatrans, which is defined in game.c, and used in more places
cpctm_declareMaskTable(g_tablatrans);

// FOR TEXT
#define COLORTXT_WHITE 		0
#define COLORTXT_YELLOW 	1
#define COLORTXT_ORANGE 	2
#define COLORTXT_BLUE 		3
#define COLORTXT_RED 		4
#define COLORTXT_MAUVE 		5

#define TRANSPARENT 	1
#define OPAQUE 			0

#define NORMALHEIGHT 	1
#define DOUBLEHEIGHT 	2

#define  VIEW_X 14
#define  VIEW_Y 17

#define BACT_ANIM_SPEED 100
#define PLAYER_SPEED 23

#define BG_COLOR 0

#define SWITCH_SCREENS 300

#define PLAYER1 0
#define PLAYER2 1

#define SINGLE 0
#define VS 1

#define CAPSULE_STEP 2


#endif
