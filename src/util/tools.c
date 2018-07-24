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

#include <cpctelera.h>
#include "../defines.h"
#include "util.h"
#include "../sprites/border.h"
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
// Name
//
//    Descriptio
//
//
// Returns:
//    

/*u8 hasReachedTarget(TEntity *e, u8 x, u8 y, i16 stepX, i16 stepY)
{
    u8 posX0, posY0;
    u8 posX1, posY1;

    posX0 = e->x[0] / SCALE;
    posY0 = e->y[0] / SCALE;
    posX1 = stepX / SCALE;
    posY1 = stepY / SCALE;

    //return ((((posX0 <= x) && (x <= posX1)) || ((posX0 >= x) && (x >= posX1))) &&
    //        (((posY0 <= y) && (y <= posY1)) || ((posY0 >= y) && (y >= posY1))));
    //return distance(posX0,posY0,posX1, posY1)<2;
    return (fast_abs(posX0 - x) <= fast_abs(posX1)) && (fast_abs(posY0 - y) <= fast_abs(posY1));
}
*/

//////////////////////////////////////////////////////////////////
// distance
//
//    Descriptio
//
//
// Returns:
//    

u16 distance (u16 x1, u16 y1, u16 x2, u16 y2)
{
    u16 x = fast_abs( x2 - x1 );  // x = valor absoluto de x2 – x1, es decir, la distancia entre las x
    u16 y = fast_abs( y2 - y1 );  // y = valor absoluto de y2 – y1, es decir, la distancia entre las y

    u16 min = x < y ? x : y; // Si x < y min = x, si no, vale y. Es decir, el menor de los 2

    return ( x + y - (min >> 1) - (min >> 2) + (min >> 4) );
}
//////////////////////////////////////////////////////////////////
// sign
//
//    Descriptio
//
//
// Returns:
//    

i16 sign(i16 x)
{
    return  (x > 0) - (x < 0);
}


//////////////////////////////////////////////////////////////////
// abs
//
//    Descriptio
//
//
// Returns:
//    
i16 abs(i16 j)
{
    return (j < 0) ? -j : j;
}

//////////////////////////////////////////////////////////////////
// clearScreen
//
//
//
// Returns:
//    void
//

void clearScreen() {
    // Clear Screen
    cpct_memset(CPCT_VMEM_START, cpct_px2byteM0(0,0), 0x4000);
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
    u8 *cornerUp;
    u8 *lineUp;
    u8 *cornerDown;
    u8 *lineDown;
    u8 *pvideo;
    
    cornerUp = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
    lineUp = cpct_getScreenPtr(CPCT_VMEM_START, x, y+1);
    cornerDown = cpct_getScreenPtr(CPCT_VMEM_START, x, y+height);
    lineDown = cpct_getScreenPtr(CPCT_VMEM_START, x, y+height-1);
    
    //cpct_waitVSYNC ();

    // -- WHITELINES: precalculated pattern color (15,15) = 0xff
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,fgColor), width-4, 2);
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+height);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,fgColor), width-4, 2);
    // -- BLACKLINES: precalculated pattern color (1,1) = 0xc0
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+2);
    cpct_drawSolidBox (pvideo, 0x00, width-4, 2);
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+height-2);
    cpct_drawSolidBox (pvideo, 0x00, width-4, 2);
	

    // -- BLUEBOX: precalculated pattern color (14,14) = 0x3f
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+1, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(bgColor,bgColor), width-4, height-6);
    //cpct_drawSolidBox (pvideo, 0x00, width-4, height-6);
    // -- LEFT & RIGHT BORDERS: precalculated pattern (15, 0) = 0xaa, (0,15) = 0x55 
    
    // top left corner
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(0,fgColor), 1, 2);
	
    // left vertical line
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,0), 1, height-6);
	
    //bottom left corner
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y+height-2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(0,fgColor), 1, 2);
    // top right corner
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-3, y+2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,0), 1, 2);
    // right vertical line
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-3, y+4);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(0,fgColor), 1, height-6);
    // bottom right corner
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x+width-3, y+height-2);
    cpct_drawSolidBox (pvideo, cpct_px2byteM0(fgColor,0), 1, 2);
}

//
// Function borrowed from Baba's Palace
// This function waits until raster pass the area where I want to draw a sprite.
// Much more faster than waitVSync
void waitRaster(u8 ty) {
	//*** SYNK WITH RASTER
	if(ty<3) while(g_nInterrupt<4);
	else {
		if(ty>=3 && ty<=5) while(g_nInterrupt<5);
		else while(g_nInterrupt>0);
	}
}


