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
#include "defines.h"
#include "game.h"
#include "keyboard/keyboard.h"
#include "text/text.h"
#include "util/util.h"
#include "entities/board.h"

TKeys keys;

const u8 sp_palette0[16] = {0x54, // 0 - black
                            0x4d, // 1 - bright magenta
                            0x40, // 2 - white(gray)
                            0x5c, // 3 - red
                            0x4c, // 4 - bright red
                            0x4e, // 5 - orange
                            0x4A, // 6 - bright yellow
                            0x52, // 7 - bright green
                            0x56, // 8 - green
                            0x5e, // 9 - yellow (pale green)
                            0x53, // 10 - bright cyan
                            0x5f, // 11 - pastel blue
                            0x55, // 12 - bright blue
                            0x58, // 13 - magenta
                            0x44, // 14 - blue
                            0x4b  // 15 - white
                           }; // Regular palette

//const u8 sp_palette1[16] = {  0x4d, 0x54, 0x40, 0x5c, 0x4c, 0x4e, 0x4A, 0x52, 0x56, 0x5e, 0x53, 0x5f, 0x55, 0x58, 0x44, 0x4b }; // Palette with transparent color

// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x101, M0, 0);

u8 g_nInterrupt = 0;	// Manage Interrupt and locate raytrace

u32 i_time;


//////////////////////////////////////////////////////////////////
// myInterruptHandler
//
//  Interruphandler that subsitutes the default one. Includes calls for reading the keyboard and playing music, if activated
//
// Returns:
//  void
//
void myInterruptHandler(){ 
    
   i_time++;
    
    if (++g_nInterrupt == 6) {
    	//cpct_akp_musicPlay();
    	cpct_scanKeyboard_if();
    	g_nInterrupt = 0;
   	}
}




void initMain()
{
    u32 seed;    // Value to initialize the random seed
    u8* vmem;

    // Sets Video mode 0
    cpct_setVideoMode(0);
    cpct_setPalette(sp_palette0, 16);
    cpct_setBorder(HW_BLACK);
    // Clean up Screen filling them up with 0's
    cpct_memset(CPCT_VMEM_START, cpct_px2byteM0(0,0), 0x4000);   // Clear de Screen BGCOLOR=Black
    
    vmem = cpct_getScreenPtr (CPCT_VMEM_START, 12, 32);
    
    // Shows Press any key message to initializate the random seed
    drawWindow2(10,60,60,60,15,14); // 15 = white; 0 blue
    drawText2("Dr.AMSTRAD is ready!!", 20, 82,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);
    drawText2("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
    
    seed = wait4UserKeypress();
    // Random seed may never be 0, so check first and add 1 if it was 0
    if (!seed)
        seed++;
    cpct_srand(seed);
    
    // Music on
    //activateMusic();

    // Initilize Keys
    initKeys();
}


void main(void) {
    // Relocate the stack right before the Video Memory
    cpct_setStackLocation(NEW_STACK_LOCATION);
    // Disable Firmware
    cpct_disableFirmware();
    // Change the interruptions table
    cpct_setInterruptHandler( myInterruptHandler );
    
    initMain();
    initGame();
    playGame(&keys);
    
    // Clean up Screen filling them up with 0's
    cpct_memset(CPCT_VMEM_START, cpct_px2byteM0(0,0), 0x4000);   // Clear de Screen BGCOLOR=Black
    // End message
    drawWindow();
    drawText2("PRESS ANY KEY TO END", 18, 98,  COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
    wait4OneKey();
    reset_cpc();
}
