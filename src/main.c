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
#include "sprites/drroland01.h"
#include "sprites/feet.h"
#include "sprites/title.h"
#include "music/dr01.h"
#include "sprites/letterMarker.h"
#include "sprites/letterMarker2.h"
#include "sprites/okSign.h"

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
u16 score1, score2;


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
    	cpct_akp_musicPlay();
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
    cpct_akp_stop();
    cpct_akp_musicInit(g_song1);
    cpct_akp_SFXInit(g_song1);
    cpct_akp_musicPlay();
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
    cpct_akp_stop();
//    cpct_akp_musicInit(song00);
//    cpct_akp_SFXInit(song00);
//    cpct_akp_musicPlay();

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
    activateMusic();

    // Initilize Keys
    initKeys();

	initHallOfFame();

    playing = 1;
}

//////////////////////////////////////////////////////////////////
//  printSpecialMarker
//  
//  Input: void
//
//  Returns: void
// 
void printSpecialMarker(u8 x, u8 y){
	u8 *pvmem;
	
	pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(x*14), 60+(y*12) );
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER2_H, SP_LETTERMARKER2_W, sp_letterMarker2);	
}
//////////////////////////////////////////////////////////////////
//  updateText
//  
//  Input: void
//
//  Returns: void
// 
void updateText(u8 *result){
	u8 *pvmem;
	
	pvmem = cpct_getScreenPtr(SCR_VMEM, 20, 132);
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0), 40, 18);
	drawText(result, 14, 132,  COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);
}
//////////////////////////////////////////////////////////////////
//  updateTopScoreMarker
//  
//  Input: void
//
//  Returns: void
// 
void updateTopScoreMarker(u8 *x, u8 *y, u8 dir){
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(*x*3), 60+(*y*12) );
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
    
    switch (dir)
    {
        case UP:
            *y=*y-1;
            break;
        case DOWN:
            *y=*y+1;
            break;
        case LEFT:
            *x=*x-1;
            break;
        default:
            *x=*x+1;            
            break;
    }

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(*x*3), 60+(*y*12) );
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);    
}

//////////////////////////////////////////////////////////////////
//  getTopScoreName
//  
//  Input: void
//
//  Returns: void
// 

void getTopScoreName(TKeys *k, u8 *title){
    u8 i;
    u8 aux_txt[2];
    u8 *pvmem;
    u8 x,y;
    u8 end;
    u8 result[20];
	u8 resultLength;

    aux_txt[0] = 'A';
    aux_txt[1] = '\0';
    drawWindow(10,36,64,122, 15, 0);
    // Title
    drawText(title, 14, 40,  COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);
    // DrRonald
    pvmem = cpct_getScreenPtr(SCR_VMEM, 57, 62);
    cpct_drawSpriteMaskedAlignedTable(sp_drroland01, pvmem, SP_DRROLAND01_W, SP_DRROLAND01_H, g_tablatrans);
    pvmem = cpct_getScreenPtr(SCR_VMEM, 54, 74);
    cpct_drawSpriteMaskedAlignedTable(sp_okSign, pvmem, SP_OKSIGN_W, SP_OKSIGN_H, g_tablatrans);

    for (i=0; i<26; i++){
        drawText(aux_txt, 14+((i%13)*3), 62+((i/13)*12),  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        aux_txt[0] = 66+i;
    }
    aux_txt[0] = 'a';
    for (i=0; i<26; i++){
        drawText(aux_txt, 14+((i%13)*3), 86+((i/13)*12),  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        aux_txt[0] = 98+i;
    }
    drawText("space", 14, 110,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("del", 31, 110,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("end", 46, 110,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);   

    x = 0;
    y = 0;
    end = 0;
    result[0] = '\0';
	resultLength = 0;
    k->fireCooling = 0;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(x*3), 60+(y*12) );
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);

    while (!end){
        delay(20);
            // Check downwards movement
        if ((cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down))){
			if (y<3){
            	updateTopScoreMarker(&x,&y,DOWN);
			} else if (y==3){
				pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(x*3), 60+(y*12) );
    			cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
				y = 4;
				if (x < 3){
					x = 0;
				} else if (x < 8){
					x = 1;
				} else {
					x = 2;
				}
				printSpecialMarker(x,y);
			}
        } else if ((y>0) && (cpct_isKeyPressed(k->up) || cpct_isKeyPressed(k->j_up))){
			if (y==4){
				printSpecialMarker(x,y);
				y=3;
				if (x == 1){
					x = 4;
				} else if (x == 2){
					x = 12;
				} 
				pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(x*3), 60+(y*12) );
    			cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
			} else {
				updateTopScoreMarker(&x,&y,UP);	
			}
        }
        // Check left movement
        if ((x>0) && (cpct_isKeyPressed(k->left) || cpct_isKeyPressed(k->j_left))){
			if (y==4){
				printSpecialMarker(x,y);
				x--;
				printSpecialMarker(x,y);
			} else {
            	updateTopScoreMarker(&x,&y,LEFT);            
			}
        // Check right movement    
        } else if ((x<12) && (cpct_isKeyPressed(k->right) || cpct_isKeyPressed(k->j_right))){
			if (y<4){
            	updateTopScoreMarker(&x,&y,RIGHT);            
			} else if(x<2) {
				printSpecialMarker(x,y);
				x++;
				printSpecialMarker(x,y);
			}
        }

	    if (k->fireCooling > 0){
	    	k->fireCooling--;
	    } else {
        	if ((cpct_isKeyPressed(k->fire1) || cpct_isKeyPressed(k->j_fire1))){
				if (resultLength<20){
					if (y<4){
						// Get the selected character based on the row and the initial caracter for uppercase and lowercase
						// 65 is "a" and 97 is "A"
                		result[resultLength] = ((y<2) * (65 + x + (13*y))) + ((y>1) * (97 + x + (13 * (y-2))));  
						resultLength++;
                		result[resultLength] = '\0';
                		updateText((u8*) &result);                   
					} else  if (x==0){
								result[resultLength] = 32;  
								resultLength++;
                				result[resultLength] = '\0';
								updateText((u8*) &result);
							} else if (x==2){
								end = YES;
							}
				} 
				if ((y==4) && (x == 1)){
					resultLength--;
                	result[resultLength] = '\0';
					updateText((u8*) &result);	
				}
			}
																			
        	}
	    }
    wait4OneKey();
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
  
    pvmem = cpct_getScreenPtr(SCR_VMEM, 20, 0);
    cpct_drawSprite(sp_title, pvmem, SP_TITLE_W, SP_TITLE_H);
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
	
	drawText("Player", 18, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
	drawText("Level", 40, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
	drawText("Score", 59, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);

    drawText("Single Mode", 8, 53, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);    
    for (i = 0; i < 3; i++) {
        sprintf(aux_txt,"%1d", i+1);
        drawText(aux_txt, 9, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        drawText(hallOfFameSingle.entries[i].name, 17, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
		sprintf(aux_txt,"%0d", hallOfFameSingle.entries[i].level);
        drawText(aux_txt,44, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(aux_txt,"%06d", hallOfFameSingle.entries[i].score);
        drawText(aux_txt,58, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    }
	drawText("Versus Mode", 8, 113, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
	for (i = 0; i < 3; i++) {
        sprintf(aux_txt,"%1d", i+1);
        drawText(aux_txt, 9, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        drawText(hallOfFameVs.entries[i].name, 17, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
		sprintf(aux_txt,"%0d", hallOfFameVs.entries[i].level);
        drawText(aux_txt,44, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(aux_txt,"%06d", hallOfFameVs.entries[i].score);
        drawText(aux_txt,58, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
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
	
	cpct_waitVSYNC();
	
    printHeader("");
	
	drawText("How to play", 0, 30, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
	drawText("Destroy de viruses matching four or", 2, 40, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
	drawText("more elements with the same color", 2, 50, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);

	drawText("Player 1", 8, 71, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
	drawText("LEFT :", 9, 81, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("Cursor left", 25, 81, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("RIGHT:", 9, 91, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("Cursor right", 25, 91, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("DOWN :", 9, 101, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("Cursor down", 25, 101, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("TURN :", 9, 111, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("Cursor up", 25, 111, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("Player 2", 50, 71, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
	drawText("LEFT :", 51, 81, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("A", 67, 81, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("RIGHT:", 51, 91, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("D", 67, 91, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("DOWN :", 51, 101, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("S", 67, 101, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("TURN :", 51, 111, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("W", 67, 111, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("PAUSE:", 9, 125, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("H", 25, 125, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
	drawText("ABORT:", 51, 125, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("ESC", 67, 125, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);

	drawText("Versus mode", 0, 140, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
	drawText("Create viruses in your oponents board", 2, 150, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
	drawText("matching two or more viruses", 2, 160, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
	
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
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 28, 62 + (20 * selectedOption));
    // Print virus
    cpct_drawSpriteBlended(        
        pvmem, SP_VIRUS_6_H, SP_VIRUS_6_W, sprites[selectedVirus][(virusState%3)+6]
    );
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 63, 62 + (20 * selectedOption));
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
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 17, 117);
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

    drawText("1)", 33, 62, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("SINGLE MODE", 39, 62, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("2)", 33, 82, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("VERSUS MODE", 39, 82, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("3)", 33, 102, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("MUSIC", 39, 102, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    if (playing)
        drawText("OFF", 54, 102, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    else
        drawText("ON", 54, 102, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("4)", 33, 122, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("HELP", 39, 122, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);

    pvmem = cpct_getScreenPtr(SCR_VMEM, 11, 75);
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
        score1 = playSingleGame(&keys1);
        getTopScoreName(&keys1, "Well done Player");
        initMarker();
        drawMenu();
    }
    else if (( cpct_isKeyPressed(Key_2)) || (((cpct_isKeyPressed(keys1.fire1) || 
             (cpct_isKeyPressed(keys1.j_fire1)))  && (selectedOption == 1)))) {
        waitKeyUp(Key_2);
        selectedOption = 1;
        initVsGame();
        playVsGame(&keys1, &keys2, &score1, &score2);
        getTopScoreName(&keys1, "Well done Player 1");
        getTopScoreName(&keys1, "Good job Player 2");
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
