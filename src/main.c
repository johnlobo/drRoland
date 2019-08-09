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
#include "sprites/eyes.h"
#include "sprites/title.h"
#include "music/dr07.h"
#include "music/fx02.h"


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
};        // Regular palette

const THallOfFame tmpHallSingle = {
    {{"DAVID\0", 600, 4},
     {"MARTIN\0", 400, 2},
     {"DIEGO\0", 200, 1}},
    600};
const THallOfFame tmpHallVs = {
    {{"MARIA\0", 600, 4},
     {"DIEGO\0", 400, 2},
     {"MARTIN\0", 200, 1}},
    600};

u8 *const feetSprites[2] = {sp_feet_0, sp_feet_1};
u8 *const eyeSprites[2] = {sp_eyes_0, sp_eyes_1};

// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x200, M0, 0);
u8 g_nInterrupt = 0; // Manage Interrupt
u32 i_time;
u8 selectedOption;
u8 playing;
u8 selectedVirus;
u8 virusState;
u8 footState;
u8 eyeState;
u32 lapso;
u32 tick;
u16 score1, score2;

// Relocated variables
__at(0xa700) TPill pillQueue[128]; //size: 0x100
__at(0xa800) u8 emptyCell[21]; //size: 0x15
__at(0xa815) u8 auxTxt[40]; //size: 0x28
__at(0xa83E) THallOfFame hallOfFameSingle; // size 0x4f
__at(0xa88D) THallOfFame hallOfFameVs; //size 0x4f
__at(0xa8DC) TKeys keys1; //size: 0x1f
__at(0xa92b) TKeys keys2; //size: 0x1f
__at(0xabcf) TBoard board1; //size: 0x2a4
__at(0xae73) TBoard board2; //size: 0x2a4
__at(0xb1f0) u8 *screenBuffer; //size: 0xe10


//////////////////////////////////////////////////////////////////
// myInterruptHandler
//
//  Interruphandler that subsitutes the default one. Includes calls for reading the keyboard and playing music, if activated
//
// Returns:
//  void
//
void myInterruptHandler()
{

    i_time++;

    if (++g_nInterrupt == 6)
    {
        cpct_akp_musicPlay();
        cpct_scanKeyboard_f();
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

void activateMusic()
{
    playing = 1;
    //cpct_akp_stop();
    cpct_akp_musicInit(g_song1);
    cpct_akp_SFXInit(g_fx1);
}

//////////////////////////////////////////////////////////////////
// deActivateMusic
//
//  deActivate music
//
// Returns:
//  void
//

void deActivateMusic()
{
    playing = 1;
    //cpct_akp_stop();
    cpct_akp_musicInit(g_fx1);
    cpct_akp_SFXInit(g_fx1);
}

//////////////////////////////////////////////////////////////////
// initHAllOf Fame
//    Initializes the keys
//
//
// Returns:
//    <u32> Number of iterations passed
//
void initHallOfFame()
{
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
    u32 seed; // Value to initialize the random seed

    // Sets Video mode 0
    cpct_setBlendMode(CPCT_BLEND_XOR);
    cpct_setVideoMode(0);
    cpct_setPalette(sp_palette0, 16);
    cpct_setBorder(HW_BLACK);
    // Clean up Screen filling them up with 0's
    clearScreen(BG_COLOR);

    // Shows Press any key message to initializate the random seed
    drawWindow(10, 60, 60, 60, 15, 14); // 15 = white; 0 blue
    drawText("DR.ROLAND IS READY!!", 20, 77, COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
    drawText("PRESS ANY KEY TO CONTINUE", 15, 102, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);

    seed = wait4UserKeypress();
    // Random seed may never be 0, so check first and add 1 if it was 0
    if (!seed)
        seed++;
    cpct_srand(seed);

    // Music on
    //activateMusic();
    activateMusic();


    // Initilize Keys
    initKeys();

    initHallOfFame();

    playing = 1;

    // fill EMPTY_CELL buffer with zeroes
    cpct_memset(&emptyCell, 0, 21);
}

//////////////////////////////////////////////////////////////////
// printHeader
//
//  prints the header on the screen
//
// Returns:
//  void
void printHeader(u8 *text)
{
    u8 *pvmem;
    u8 offset;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 20, 0);
    cpct_drawSprite(sp_title, pvmem, SP_TITLE_W, SP_TITLE_H);
    offset = 40 - (strLength(text));
    drawText((u8 *)text, offset, 25, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
}

//////////////////////////////////////////////////////////////////
// printFooter
//
//  prints the footer on the screen
//
// Returns:
//  void
void printFooter()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 49, 182);
    cpct_drawSprite(bk_poweredby_cpctelera, pvmem, BK_POWEREDBY_CPCTELERA_W, BK_POWEREDBY_CPCTELERA_H);
    drawText("JOHN LOBO", 16, 179, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("@ GLASNOST CORP. 2018", 3, 191, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
}

//////////////////////////////////////////////////////////////////
// drawScoreBoard
//
//
// Returns:
//    void
//

void drawScoreBoard()
{
    u8 i;
    u32 c = 0;

    cpct_waitVSYNC();

    clearScreen(BG_COLOR);

    printHeader("");

    drawText("PLAYER", 18, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("LEVEL", 40, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("SCORE", 59, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);

    drawText("SINGLE MODE", 8, 53, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
    for (i = 0; i < 3; i++)
    {
        sprintf(auxTxt, "%1d", i + 1);
        drawText(auxTxt, 9, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        drawText(hallOfFameSingle.entries[i].name, 17, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(auxTxt, "%0d", hallOfFameSingle.entries[i].level);
        drawText(auxTxt, 44, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(auxTxt, "%06d", hallOfFameSingle.entries[i].score);
        drawText(auxTxt, 58, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    }
    drawText("VERSUS MODE", 8, 113, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
    for (i = 0; i < 3; i++)
    {
        sprintf(auxTxt, "%1d", i + 1);
        drawText(auxTxt, 9, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        drawText(hallOfFameVs.entries[i].name, 17, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(auxTxt, "%0d", hallOfFameVs.entries[i].level);
        drawText(auxTxt, 44, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        sprintf(auxTxt, "%06d", hallOfFameVs.entries[i].score);
        drawText(auxTxt, 58, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    }
    printFooter();

    c = 40000; // Number of loops passed if not keypressed
    // Wait 'till the user presses a key, counting loop iterations
    do
    {
        c--;                   // One more cycle
        cpct_scanKeyboard_f(); // Scan the keyboard
    } while ((!cpct_isAnyKeyPressed_f()) && c > 0);
}

/////////////////////////////////////////////////////////////////
// help
//  help screen
//
//
// Returns:
//    void
//

void help()
{

    clearScreen(BG_COLOR);

    cpct_waitVSYNC();

    printHeader("");

    drawText("HOW TO PLAY", 0, 28, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
    drawText("DESTROY DE VIRUSES MATCHING 4 OR", 2, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("MORE ELEMENTS IN THE SAME COLORr", 2, 48, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);

    drawText("PLAYER 1", 8, 66, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
    drawText("LEFT :", 9, 76, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("J", 25, 76, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("RIGHT:", 9, 86, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("L", 25, 86, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("DOWN :", 9, 96, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("K", 25, 96, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("TURN :", 9, 106, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("I", 25, 106, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("FIRE :", 9, 116, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("U", 25, 116, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);

    drawText("PLAYER 2", 50, 66, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
    drawText("LEFT :", 51, 76, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("A", 67, 76, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("RIGHT:", 51, 86, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("D", 67, 86, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("DOWN :", 51, 96, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("S", 67, 96, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("TURN :", 51, 106, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("W", 67, 106, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("FIRE :", 51, 1116, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("Q", 67, 116, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);

    drawText("PAUSE:", 9, 130, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("H", 25, 130, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("ABORT:", 51, 130, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("ESC", 67, 130, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);

    drawText("VERSUS MODE", 0, 142, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
    drawText("CREATE VIRUSES IN YOUR OPPONENT BOARD", 2, 152, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("MATCHING TWO OR MORE ELEMENTS", 2, 162, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);

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
void initMarker()
{
    selectedVirus = (cpct_rand8() % 3);
    virusState = 0;
    lapso = 0; // init lapso to avoid showing scoreboard too fast
    footState = 1;
    eyeState = 1;
}

//////////////////////////////////////////////////////////////////
// drawEyes
//
//
// Returns:
//    void
//
void drawEyes()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 15, 85);
    // Print feet
    cpct_drawSprite(eyeSprites[eyeState], pvmem, SP_EYES_0_W, SP_EYES_0_H);
}

//////////////////////////////////////////////////////////////////
// animEyes
//
//
// Returns:
//    void
//
void animEyes()
{
    u8 i;

    for (i = 0; i < 2; i++)
    {
        drawEyes();
        eyeState = !eyeState;
        delay(40);
    }
}

//////////////////////////////////////////////////////////////////
// drawFoot
//
//
// Returns:
//    void
//
void drawFoot()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 17, 117);
    // Print feet
    cpct_drawSprite(feetSprites[footState], pvmem, SP_FEET_0_W, SP_FEET_0_H);
}

//////////////////////////////////////////////////////////////////
// animFoot
//
//
// Returns:
//    void
//
void animFoot()
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        drawFoot();
        footState = !footState;
        delay(40);
    }
}

//////////////////////////////////////////////////////////////////
// drawMarker
//
//
// Returns:
//    void
//
void drawMarker()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 28, 75 + (20 * selectedOption));
    // Print virus
    cpct_drawSpriteBlended(
        pvmem, SP_VIRUS_6_H, SP_VIRUS_6_W, sprites[selectedVirus][(virusState % 3) + 6]);
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 63, 75 + (20 * selectedOption));
    cpct_drawSpriteBlended(
        pvmem, SP_VIRUS_6_H, SP_VIRUS_6_W, sprites[selectedVirus][(virusState % 3) + 6]);
}

//////////////////////////////////////////////////////////////////
// animMarker
//
//
// Returns:
//    void
//
void animMarker()
{
    drawMarker();
    virusState++;
    drawMarker();
}

//////////////////////////////////////////////////////////////////
// drawMenu
//
//
//
// Returns:
//    void
//
void drawMenu()
{
    u8 *pvmem;

    cpct_waitVSYNC();

    clearScreen(BG_COLOR);

    printHeader("");

    drawText("1)", 33, 75, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("SINGLE MODE", 39, 75, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("2)", 33, 95, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("VERSUS MODE", 39, 95, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("3)", 33, 115, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("HELP", 39, 115, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    // Draw Roland character
    pvmem = cpct_getScreenPtr(SCR_VMEM, 11, 75);
    cpct_drawSprite(sp_drroland01, pvmem, SP_DRROLAND01_W, SP_DRROLAND01_H);

    printFooter();

    drawMarker();
}

//////////////////////////////////////////////////////////////////
// updateMarker
//    Updates the selected option marker
//
// Returns:
//    void

void updateMarker(u8 option){
    drawMarker();
    selectedOption = option;
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
void checkKeyboardMenu()
{
    u8 l;

    delay(25);

    if (cpct_isKeyPressed(Key_1) ||
        ((
             cpct_isKeyPressed(keys1.fire1) ||
             cpct_isKeyPressed(keys1.j_fire1) ||
             cpct_isKeyPressed(keys1.j_fire2)) &&
         (selectedOption == 0)))
    {
        waitKeyUp(Key_1);
        selectedOption = 0;
        //deActivateMusic();
        initSingleGame();
        playSingleGame(&keys1);
        //activateMusic();
        drawScoreBoard();
        initMarker();
        drawMenu();
    }
    else if (
        cpct_isKeyPressed(Key_2) ||
        ((cpct_isKeyPressed(keys1.fire1) ||
          cpct_isKeyPressed(keys1.j_fire1) ||
          cpct_isKeyPressed(keys1.j_fire2)) &&
         (selectedOption == 1)))
    {
        waitKeyUp(Key_2);
        selectedOption = 1;
        //deActivateMusic();
        l = showMessage("Choose Initial Level", NUMBER);
        initVsGame(l);
        playVsGame(&keys1, &keys2);
        //activateMusic();
        drawScoreBoard();
        initMarker();
        drawMenu();
    }
    else if (
        cpct_isKeyPressed(Key_3) ||
        ((cpct_isKeyPressed(keys1.fire1) ||
          cpct_isKeyPressed(keys1.j_fire1) ||
          cpct_isKeyPressed(keys1.j_fire2)) &&
         (selectedOption == 2)))
    {
        waitKeyUp(Key_4);
        selectedOption = 2;
        help();
        initMarker();
        drawMenu();
    }
    else if ((cpct_isKeyPressed(keys1.up)) || (cpct_isKeyPressed(keys1.j_up)))
    {
        cpct_akp_SFXPlay(4, 15, 10, 0, 0, AY_CHANNEL_ALL);
        if (selectedOption > 0)
            updateMarker(selectedOption-1);
        else
            updateMarker(2);
    }
    else if ((cpct_isKeyPressed(keys1.down)) || (cpct_isKeyPressed(keys1.j_down)))
    {
        cpct_akp_SFXPlay(5, 15, 26, 0, 0, AY_CHANNEL_ALL);
        
        if (selectedOption < 2)
            updateMarker(selectedOption+1);
        else
            updateMarker(0);
    }
}


//////////////////////////////////////////////////////////////////
// Main process
//
//
//
void main(void)
{
    // Disable Firmware
    cpct_disableFirmware();

    // Relocate the stack right before the Video Memory
    cpct_setStackLocation(NEW_STACK_LOCATION);
    
    // Activate music before changing interruptions
    activateMusic();
    
    // Change the interruptions table
    cpct_setInterruptHandler(myInterruptHandler);

    initMain();

    tick = 0;
    initMarker();

    while (1)
    {
        drawMenu();
        tick = 0;
        while (lapso < SWITCH_SCREENS)
        {
            checkKeyboardMenu();
            lapso++;
            tick++;
            if ((tick % 3) == 0)
            {
                animMarker();
            }

            if ((tick % 20) == 0)
            {
                animEyes();
            }

            if ((tick % 50) == 0)
            {
                animFoot();
            }
        }
        drawScoreBoard();
        initMarker();
    }
}
