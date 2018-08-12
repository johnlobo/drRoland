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
#include <stdio.h>
#include "defines.h"
#include "game.h"
#include "keyboard/keyboard.h"
#include "text/text.h"
#include "util/util.h"
#include "entities/board.h"
#include "sprites/blocks.h"

TKeys keys;

const u8 sp_palette0[16] = {
                            0x54, // 0 - black
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
cpctm_createTransparentMaskTable(g_tablatrans, 0x200, M0, 0);

u8 g_nInterrupt = 0;	// Manage Interrupt and locate raytrace

u32 i_time;
u32 scoreHallOfFame[8];
u8 nameHallOfFame[8][15];
u8 newNameHighScore[15] = {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 0};
u8 selectedOption;
u8 aux_txt[20];
u8 playing;


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


//////////////////////////////////////////////////////////////////
// activateMusic
//
//  Activate music
//
// Returns:
//  void
//

void activateMusic() {
    playing = 1;
    //cpct_akp_stop();
    //cpct_akp_musicInit(song02);
    //cpct_akp_SFXInit(song02);
    //cpct_akp_musicPlay();
}

//////////////////////////////////////////////////////////////////
// deActivateMusic
//
//  deActivate music
//
// Returns:
//  void
//

void deActivateMusic() {
    playing = 0;
    //cpct_akp_stop();
    //cpct_akp_musicInit(song00);
    //cpct_akp_SFXInit(song00);
    //cpct_akp_musicPlay();

}

//////////////////////////////////////////////////////////////////
// initMain
//
//  main initialization
//
// Returns:
//  void
void initMain()
{
    u32 seed;    // Value to initialize the random seed
    u8* vmem;

    // Sets Video mode 0
    cpct_setBlendMode(CPCT_BLEND_XOR);
    cpct_setVideoMode(0);
    cpct_setPalette(sp_palette0, 16);
    cpct_setBorder(HW_BLACK);
    // Clean up Screen filling them up with 0's
    clearScreen();
    
    vmem = cpct_getScreenPtr (CPCT_VMEM_START, 12, 32);
    
    // Shows Press any key message to initializate the random seed
    drawWindow(10,60,60,60,15,14); // 15 = white; 0 blue
    drawText("Dr.AMSTRAD is ready!!", 18, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
    drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
    
    seed = wait4UserKeypress();
    // Random seed may never be 0, so check first and add 1 if it was 0
    if (!seed)
        seed++;
    cpct_srand(seed);
    
    // Music on
    //activateMusic();

    // Initilize Keys
    initKeys();

    playing = 0;
    top = 10000;
}

void printFooter(){
    drawText("John Lobo", 31, 172, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
    drawText("(c) Glasnost Corp 2018", 18, 185, COLORTXT_BLUE, NORMALHEIGHT, TRANSPARENT);
}

//////////////////////////////////////////////////////////////////
// drawScoreBoard
//
//
// Returns:
//    void
//

void drawScoreBoard() {
    u8 i;
    u32 c = 0;

    cpct_waitVSYNC();

    clearScreen();

    drawText("Dr.AMSTRAD : Scoreboard", 17, 2, COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);

    for (i = 0; i < 8; i++) {
        sprintf(aux_txt,"%2d", i+1);
        drawText(aux_txt, 5, 30 + (i * 15), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        drawText(nameHallOfFame[i], 14, 30 + (i * 15), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(aux_txt,"%d", scoreHallOfFame[i]);
        drawText(aux_txt,69, 30 + (i * 15), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    }

    printFooter();

    c = 40000;     // Number of loops passed if not keypressed
    // Wait 'till the user presses a key, counting loop iterations
    do {
        c--;                       // One more cycle
        cpct_scanKeyboard_f();     // Scan the keyboard
    } while (( ! cpct_isAnyKeyPressed_f() ) && c > 0);
}

/////////////////////////////////////////////////////////////////
// help
//  help screen
//
//
// Returns:
//    void
//

void help() {

    clearScreen();

    drawText("Dr.AMSTRAD : Help", 23, 2, COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);

    printFooter();

    wait4OneKey();
    
}

//////////////////////////////////////////////////////////////////
// drawMarker
//
//
//
// Returns:
//    void
//


void drawMarker() {
    u8* pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 23, 60 + (20 * selectedOption));
    cpct_drawSpriteBlended(pvmem, SP_BLOCKS_1_H, SP_BLOCKS_1_W, sp_blocks_1);
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 58, 60 + (20 * selectedOption));
    cpct_drawSpriteBlended(pvmem, SP_BLOCKS_1_H, SP_BLOCKS_1_W, sp_blocks_1);
}

//////////////////////////////////////////////////////////////////
// drawMenu
//
//
//
// Returns:
//    void
//
void drawMenu() {

    cpct_waitVSYNC();

    clearScreen();

    drawText("Dr.AMSTRAD", 30, 2, COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);


    drawText("1) SINGLE MODE", 28, 60, COLORTXT_BLUE, NORMALHEIGHT, TRANSPARENT);
    drawText("2) MUSIC", 28, 80, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    if (playing)
        drawText("OFF", 49, 80, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    else
        drawText("ON", 49, 80, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("3) HELP", 28, 100, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("4) PLAY", 28, 120, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);


    printFooter();

    drawMarker();
}


//////////////////////////////////////////////////////////////////
// checkKeyboardMenu
//    Checks the keyboard for the menu options
//
//
// Returns:
//    void
//
void checkKeyboardMenu() {

    delay(20);

    if (( cpct_isKeyPressed(Key_1)) || (((cpct_isKeyPressed(keys.fire1) || (cpct_isKeyPressed(Joy0_Fire1)))  && (selectedOption == 0)))) {
        drawMarker();
        selectedOption = 0;
        drawMarker();
        waitKeyUp(Key_1);
    }
    else if (( cpct_isKeyPressed(Key_2)) || (((cpct_isKeyPressed(keys.fire1) || (cpct_isKeyPressed(Joy0_Fire1)))  && (selectedOption == 1)))) {
        drawMarker();
        selectedOption = 1;
        drawMarker();
        if (!playing) {
            activateMusic();
        } else {
            deActivateMusic();
        }
        drawMenu();
    }
    else if (( cpct_isKeyPressed(Key_3)) || (((cpct_isKeyPressed(keys.fire1) || (cpct_isKeyPressed(Joy0_Fire1))) && (selectedOption == 2)))) {
        waitKeyUp(Key_3);
        help();
        drawMenu();
    }
    else if (( cpct_isKeyPressed(Key_4)) || (((cpct_isKeyPressed(keys.fire1) || (cpct_isKeyPressed(Joy0_Fire1))) && (selectedOption == 3)))) {
        waitKeyUp(Key_4);
        initGame();
        playGame(&keys);
        drawMenu();
    }
    else if ((cpct_isKeyPressed(keys.up)) || (cpct_isKeyPressed(Joy0_Up))) {
        if (selectedOption > 0) {
            drawMarker();
            selectedOption--;
            drawMarker();
        } else {
            drawMarker();
            selectedOption = 3;
            drawMarker();
        }
    } else if ((cpct_isKeyPressed(keys.down)) || (cpct_isKeyPressed(Joy0_Down))) {
        if (selectedOption < 3) {
            drawMarker();
            selectedOption++;
            drawMarker();
        } else {
            drawMarker();
            selectedOption = 0;
            drawMarker();
        }

    } else if ( cpct_isKeyPressed(keys.music)) {
        if (!playing) {
            activateMusic();
        } else {
            deActivateMusic();
        }
    }
}


void main(void) {
    u32 lapso;

    // Relocate the stack right before the Video Memory
    cpct_setStackLocation(NEW_STACK_LOCATION);
    // Disable Firmware
    cpct_disableFirmware();
    // Change the interruptions table
    cpct_setInterruptHandler( myInterruptHandler );
    
    initMain();

    lapso = 0;

    while (1) {
        drawMenu();
        lapso = 0;
        while (lapso < SWITCH_SCREENS) {
            checkKeyboardMenu();
            lapso++;
        }
        drawScoreBoard();
    }
}
