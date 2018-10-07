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
#include <stdio.h>
#include "defines.h"
#include "game.h"
#include "keyboard/keyboard.h"
#include "text/text.h"
#include "util/util.h"
#include "entities/board.h"
#include "sprites/virus.h"
#include "sprites/poweredby-cpctelera.h"
#include "sprites/drRonald.h"
#include "sprites/drroland01.h"
#include "sprites/feet.h"

typedef struct{
	u8 name[20];
	u32 score;
	u8 level;
} THallOfFameEntry;

typedef struct{
	THallOfFameEntry entries[3];
	u32 topScore;
} THallOfFame;

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

const THallOfFame tmpHallSingle = {
						{
							{"David", 10000, 4},
							{"Martin", 5000, 2},
				   			{"Diego", 1000, 1}
				  		}
				  		, 10000
					  };
const THallOfFame tmpHallVs = {
						{
							{"Maria", 10000, 4},
							{"Diego", 5000, 2},
				   			{"Martin", 1000, 1}
				  		}
				  		, 10000
					  };

u8* const feetSprites[2] = {sp_feet_0, sp_feet_1}; 

// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x200, M0, 0);
TKeys keys1, keys2;
u8 g_nInterrupt = 0;	// Manage Interrupt and locate raytrace
u32 i_time;
THallOfFame hallOfFameSingle;
THallOfFame hallOfFameVs;
u8 selectedOption;
u8 aux_txt[20];
u8 playing;
u8 selectedVirus;
u8 virusState;
u8 footState;
u32 lapso;
u32 tick;


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
// initHAllOf Fame
//    Initializes the keys
// 
//
// Returns:
//    <u32> Number of iterations passed
//
void initHallOfFame(){
    cpct_memcpy(&hallOfFameSingle, &tmpHallSingle, sizeof(THallOfFame));
    cpct_memcpy(&hallOfFameVs, &tmpHallVs, sizeof(THallOfFame));
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

    // Sets Video mode 0
    cpct_setBlendMode(CPCT_BLEND_XOR);
    cpct_setVideoMode(0);
    cpct_setPalette(sp_palette0, 16);
    cpct_setBorder(HW_BLACK);
    // Clean up Screen filling them up with 0's
    clearScreen(BG_COLOR);
    
    // Shows Press any key message to initializate the random seed
    drawWindow(10,60,60,60,15,14); // 15 = white; 0 blue
    drawText("Dr.Roland is ready!!", 20, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
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

	initHallOfFame();

    
    playing = 0;
}

//////////////////////////////////////////////////////////////////
// printHeader
//
//  prints the header on the screen
//
// Returns:
//  void
void printHeader(u8 *text){
    u8 *pvmem;
    u8 offset;
  
    pvmem = cpct_getScreenPtr(SCR_VMEM, 18, 0);
    cpct_drawSprite(bk_drRonald_0, pvmem, BK_DRRONALD_0_W, BK_DRRONALD_0_H);
    pvmem = cpct_getScreenPtr(SCR_VMEM, 40, 0);
    cpct_drawSprite(bk_drRonald_1, pvmem, BK_DRRONALD_1_W, BK_DRRONALD_1_H);
    offset = 40 - (strLength(text));
    drawText((u8*) text, offset, 25, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
}


//////////////////////////////////////////////////////////////////
// printFooter
//
//  prints the footer on the screen
//
// Returns:
//  void
void printFooter(){
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 49, 182);
    cpct_drawSprite(bk_poweredby_cpctelera, pvmem, BK_POWEREDBY_CPCTELERA_W, BK_POWEREDBY_CPCTELERA_H);
    drawText("John Lobo", 16, 179, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("(c) Glasnost Corp 2018", 3, 191, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
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

    clearScreen(BG_COLOR);

    printHeader("");
	
	drawText("Player", 15, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
	drawText("Level", 37, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
	drawText("Score", 56, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);

    drawText("Single Mode", 5, 43, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);    
    for (i = 0; i < 3; i++) {
        sprintf(aux_txt,"%1d", i+1);
        drawText(aux_txt, 6, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        drawText(hallOfFameSingle.entries[i].name, 14, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
		sprintf(aux_txt,"%0d", hallOfFameSingle.entries[i].level);
        drawText(aux_txt,41, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(aux_txt,"%06d", hallOfFameSingle.entries[i].score);
        drawText(aux_txt,55, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    }
	drawText("Versus Mode", 5, 113, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
	for (i = 0; i < 3; i++) {
        sprintf(aux_txt,"%1d", i+1);
        drawText(aux_txt, 6, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        drawText(hallOfFameVs.entries[i].name, 14, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
		sprintf(aux_txt,"%0d", hallOfFameVs.entries[i].level);
        drawText(aux_txt,41, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(aux_txt,"%06d", hallOfFameVs.entries[i].score);
        drawText(aux_txt,55, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
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

    clearScreen(BG_COLOR);

    printHeader("HELP");

    printFooter();

    wait4OneKey();
    
}
//////////////////////////////////////////////////////////////////
// initMarker
//
//
// Returns:
//    void
//
void initMarker() {
    selectedVirus = (cpct_rand8() % 3);
    virusState = 0;
    lapso = 0; // init lapso to avoid showing scoreboard too fast	
    footState = 1;
}


//////////////////////////////////////////////////////////////////
// drawMarker
//
//
// Returns:
//    void
//
void drawMarker() {
    u8* pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 23, 60 + (20 * selectedOption));
    // Print virus
    cpct_drawSpriteBlended(        
        pvmem, SP_VIRUS_6_H, SP_VIRUS_6_W, sprites[selectedVirus][(virusState%3)+6]
    );
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 58, 60 + (20 * selectedOption));
    cpct_drawSpriteBlended(        
        pvmem, SP_VIRUS_6_H, SP_VIRUS_6_W, sprites[selectedVirus][(virusState%3)+6]
    );
}

//////////////////////////////////////////////////////////////////
// animMarker
//
//
// Returns:
//    void
//
void animMarker() {
    drawMarker();
    virusState++;
    drawMarker();
}

//////////////////////////////////////////////////////////////////
// drawFoot
//
//
// Returns:
//    void
//
void drawFoot() {
    u8* pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 12, 117);
    // Print feet
    cpct_drawSprite(feetSprites[footState],pvmem,SP_FEET_0_W,SP_FEET_0_H);
}

//////////////////////////////////////////////////////////////////
// animFoot
//
//
// Returns:
//    void
//
void animFoot() {
    drawFoot();
    footState = !footState;
    delay(40);
    drawFoot();
    footState = !footState;
    delay(40);
    drawFoot();
    footState = !footState;
    delay(40);
    drawFoot();
    footState = !footState;
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
    u8 *pvmem;

    cpct_waitVSYNC();

    clearScreen(BG_COLOR);

    printHeader("");

    drawText("1)", 28, 60, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("SINGLE MODE", 34, 60, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("2)", 28, 80, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("VERSUS MODE", 34, 80, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("3)", 28, 100, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("MUSIC", 34, 100, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    if (playing)
        drawText("OFF", 49, 100, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    else
        drawText("ON", 49, 100, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("4)", 28, 120, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("HELP", 34, 120, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);

    pvmem = cpct_getScreenPtr(SCR_VMEM, 6, 75);
    cpct_drawSprite(sp_drroland01, pvmem, SP_DRROLAND01_W, SP_DRROLAND01_H);

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

    delay(25);

    if (( cpct_isKeyPressed(Key_1)) || (((cpct_isKeyPressed(keys1.fire1) || 
        (cpct_isKeyPressed(keys1.j_fire1)))  && (selectedOption == 0)))) {
        waitKeyUp(Key_1);
        selectedOption = 0;
        initSingleGame();
        playSingleGame(&keys1);
        initMarker();
        drawMenu();
    }
    else if (( cpct_isKeyPressed(Key_2)) || (((cpct_isKeyPressed(keys1.fire1) || 
             (cpct_isKeyPressed(keys1.j_fire1)))  && (selectedOption == 1)))) {
        waitKeyUp(Key_2);
        selectedOption = 1;
        initVsGame();
        playVsGame(&keys1, &keys2);
        initMarker();
        drawMenu();
    }
    else if (( cpct_isKeyPressed(Key_3)) || (((cpct_isKeyPressed(keys1.fire1) || 
             (cpct_isKeyPressed(keys1.j_fire1))) && (selectedOption == 2)))) {
        drawMarker();
        selectedOption = 2;
        drawMarker();
        if (!playing) {
            activateMusic();
        } else {
            deActivateMusic();
        }
        drawMenu();
    }
    else if (( cpct_isKeyPressed(Key_4)) || (((cpct_isKeyPressed(keys1.fire1) || 
             (cpct_isKeyPressed(Joy0_Fire1))) && (selectedOption == 3)))) {
        waitKeyUp(Key_4);
        selectedOption = 3;
        help();
        initMarker();
        drawMenu();
    }
    else if ((cpct_isKeyPressed(keys1.up)) || (cpct_isKeyPressed(keys1.j_up))) {
        if (selectedOption > 0) {
            drawMarker();
            selectedOption--;
            drawMarker();
        } else {
            drawMarker();
            selectedOption = 3;
            drawMarker();
        }
    } else if ((cpct_isKeyPressed(keys1.down)) || (cpct_isKeyPressed(keys1.j_down))) {
        if (selectedOption < 3) {
            drawMarker();
            selectedOption++;
            drawMarker();
        } else {
            drawMarker();
            selectedOption = 0;
            drawMarker();
        }

    } else if ( cpct_isKeyPressed(keys1.music)) {
        if (!playing) {
            activateMusic();
        } else {
            deActivateMusic();
        }
    }
}


void main(void) {
	// Disable Firmware
    cpct_disableFirmware();
	
    // Relocate the stack right before the Video Memory
    cpct_setStackLocation(NEW_STACK_LOCATION);

    // Change the interruptions table
    cpct_setInterruptHandler(myInterruptHandler);
    
    initMain();

    tick = 0;
    initMarker();

    while (1) {
        drawMenu();
        tick = 0;
        while (lapso < SWITCH_SCREENS) {
            checkKeyboardMenu();
            lapso++;
            tick++;
            if ((tick%3) == 0){
                animMarker();
            }
            if ((tick%50) == 0){
                animFoot();
            }
        }
        drawScoreBoard();
        initMarker();
    }
}
