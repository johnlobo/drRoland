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
#include "util.h"
#include "../keyboard/keyboard.h"


//////////////////////////////////////////////////////////////////
// delay
//
//    Wait for an specific number of cycles
//
//
// Returns:
//    void
//
void delay(u32 cycles)
{
    u32 i;
    for (i = 0; i < cycles; i++)
    {
        __asm
        halt
        __endasm;
    }
}


//////////////////////////////////////////////////////////////////
// clearScreen
//
//
//
// Returns:
//    void
//

void clearScreen(u8 bgColor) {
    // Clear Screen
    cpct_memset(CPCT_VMEM_START, cpct_px2byteM0(bgColor,bgColor), 0x4000);
}


/////////////////////////////////////////////////////////////////
// drawWindow
//
//
//
// Returns:
//    void
//
void drawWindow(u8 x, u8 y, u8 width, u8 height, u8 fgColor, u8 bgColor){
    u8 *pvideo;
    
    //cpct_waitVSYNC ();

	// top and bottom fgColor horizontal lines
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,fgColor), width-4, 2);
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+height);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,fgColor), width-4, 2);
    // top and bottom BG_COLOR horizontal lines
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR,BG_COLOR), width-4, 2);
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+height-2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR,BG_COLOR), width-4, 2);
    // Internal box
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(bgColor,bgColor), width-4, height-6);
          
    // top left corner
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR,fgColor), 1, 2);
	
    // left vertical line
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, height-6);
	
    //bottom left corner
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+height-2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR,fgColor), 1, 2);
    // top right corner
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-3, y+2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, 2);
    // right vertical line
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-3, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR,fgColor), 1, height-6);
    // bottom right corner
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-3, y+height-2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, 2);
}

/////////////////////////////////////////////////////////////////
// drawBottleNeck
//
//
//
// Returns:
//    void
//
void drawBottleNeck(u8 x, u8 y, u8 width, u8 height, u8 fgColor, u8 bgColor){
    u8 *pvideo;
	
	// Internal box
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(bgColor,bgColor), width, (height/2)-1);
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1+(width/4), y+3+(height/2));
	cpct_drawSolidBox (pvideo, cpct_px2byteM0(bgColor,bgColor), (width/2), (height/2)-4);
    
	// top and bottom fgColor horizontal lines
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,fgColor), width-1, 2);
	
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+(height/2)+3);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,fgColor), (width/4), 2);
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-(width/4), y+(height/2)+3);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,fgColor), (width/4), 2);

    // top and bottom BG_COLOR horizontal lines
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR,BG_COLOR), width-1, 2);
	
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+(height/2)+5);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR,BG_COLOR), (width/4), 2);
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-(width/4), y+(height/2)+5);
	cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR,BG_COLOR), (width/4), 2);

	
	 // top left connector
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR, fgColor), 1, 2);
	
	// left vertical line
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, (height/2)-2);
	
	 // bottom left connector
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+(height/2)+1);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR, fgColor), 1, 2);
	
	 // top right connector
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width, y+2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, 2);
	
	// right vertical line
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR, fgColor), 1, (height/2)-2);
	
	 // bottom right connector
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width, y+(height/2)+1);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, 2);
	
	// Second half of bottleneck
	
	 // top left connector
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1+(width/4), y+5+(height/2));
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, 2);
	
	// left vertical line
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1+(width/4), y+7+(height/2));
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR, fgColor), 1, (height/2)-12);
	
	// bottom left connector
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1+(width/4), y+height-5);
   	cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, 2);
	
	// top right connector
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-(width/4)-1, y+5+(height/2));
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR, fgColor), 1, 2);
	
	// right vertical line
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-(width/4)-1, y+7+(height/2));
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,BG_COLOR), 1, (height/2)-12);
	
	// bottom right connector
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-(width/4)-1, y+height-5);
   	cpct_drawSolidBox (pvideo, cpct_px2byteM0(BG_COLOR, fgColor), 1, 2);

}



