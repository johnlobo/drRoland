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
#include "compressed/powered_z.h"
#include "compressed/title_z.h"
#include "compressed/dr1_z.h"
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
u8 footStep;
u8 eyeStep;
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
__at(0xb000) u8 *screenBuffer0; //size: 0xe10
__at(0xb1f0) u8 *screenBuffer; //size: 0xe10


// ********************************************************************************
/// <summary>
/// myInterruptHandler
/// Interruphandler that subsitutes the default one. Includes calls for reading the keyboard and playing music, if activated
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
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

// ********************************************************************************
/// <summary>
/// activateMusic
/// Activate music
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void activateMusic()
{
    playing = 1;
    //cpct_akp_stop();
    //cpct_akp_musicInit(g_song1);
    //cpct_akp_SFXInit(g_fx1);
}

// ********************************************************************************
/// <summary>
/// deActivateMusic
/// deActivate music
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void deActivateMusic()
{
    playing = 1;
    //cpct_akp_stop();
    //cpct_akp_musicInit(g_fx1);
    //cpct_akp_SFXInit(g_fx1);
}

// ********************************************************************************
/// <summary>
/// initHAllOf Fame
/// Initializes the keys
/// Returns:
/// <u32> Number of iterations passed
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void initHallOfFame()
{
    cpct_memcpy(&hallOfFameSingle, &tmpHallSingle, sizeof(THallOfFame));
    cpct_memcpy(&hallOfFameVs, &tmpHallVs, sizeof(THallOfFame));
}

// ********************************************************************************
/// <summary>
/// initMain
/// main initialization
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
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

// ********************************************************************************
/// <summary>
/// printHeader
/// prints the header on the screen
/// Returns:
/// void
/// </summary>
/// <param name="text"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printHeader()
{
    // draw title logo
    drawCompressToScreen(20, 0, G_TITLE_W, G_TITLE_H, G_TITLE_SIZE, (u8*) &title_z_end, NO);
}

// ********************************************************************************
/// <summary>
/// printFooter
/// prints the footer on the screen
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printFooter()
{
    // draw Powered By CPCTelera logo
    drawCompressToScreen(49, 182, G_POW_W, G_POW_H, G_POW_SIZE, (u8*) &powered_z_end, NO);

    drawText("JOHN LOBO", 16, 179, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("@ GLASNOST CORP. 2019", 3, 191, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
}

// ********************************************************************************
/// <summary>
/// drawScoreBoard
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void drawScoreBoard()
{
    u8 i;
    u32 c = 0;


    clearScreen(BG_COLOR);

    printHeader();

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

// ********************************************************************************
/// <summary>
/// help
/// help screen
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void help()
{

    clearScreen(BG_COLOR);

    printHeader();

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
    drawText("FIRE :", 51, 116, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
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
// ********************************************************************************
/// <summary>
/// initMarker
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void initMarker()
{
    selectedVirus = (cpct_rand8() % 3);
    virusState = 0;
    lapso = 0; // init lapso to avoid showing scoreboard too fast
    footStep = 0;
    eyeStep = 0;
}

// ********************************************************************************
/// <summary>
/// drawEyes
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void drawEyes()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 15, 85);
    // Print feet
    cpct_drawSprite(eyeSprites[(eyeStep%2)], pvmem, SP_EYES_0_W, SP_EYES_0_H);
}

// ********************************************************************************
/// <summary>
/// animEyes
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void animEyes()
{
    //u8 i;
//
    //for (i = 0; i < 2; i++)
    //{
    //    drawEyes();
    //    eyeStep = !eyeStep;
    //    delay(40);
    //}
    if (!eyeStep){
        eyeStep = 1;
    } else if (eyeStep == 3){
        eyeStep = 0;
    } else {
        eyeStep++;
    }
    drawEyes();
}

// ********************************************************************************
/// <summary>
/// drawFoot
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void drawFoot()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 17, 117);
    // Print feet
    // if footStep is odd draw foot up, else draw foot down
    cpct_drawSprite(feetSprites[(footStep%2)], pvmem, SP_FEET_0_W, SP_FEET_0_H);
}

// ********************************************************************************
/// <summary>
/// animFoot
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void animFoot()
{
    if (!footStep){
        footStep = 1;
    } else if (footStep == 3){
        footStep = 0;
    } else {
        footStep++;
    }
    drawFoot();
}

// ********************************************************************************
/// <summary>
/// drawMarker
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
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

// ********************************************************************************
/// <summary>
/// animMarker
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void animMarker()
{
    drawMarker();
    virusState++;
    drawMarker();
}

// ********************************************************************************
/// <summary>
/// drawMenu
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void drawMenu()
{

    clearScreen(BG_COLOR);

    printHeader();

    drawText("1)", 33, 75, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("SINGLE MODE", 39, 75, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("2)", 33, 95, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("VERSUS MODE", 39, 95, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    drawText("3)", 33, 115, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
    drawText("HELP", 39, 115, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
    // Draw Roland character
    drawCompressToScreen(11, 75, G_DR1_W, G_DR1_H, G_DR1_SIZE, (u8*) &dr1_z_end, NO);

    printFooter();

    drawMarker();
}

// ********************************************************************************
/// <summary>
/// updateMarker
/// Updates the selected option marker
/// Returns:
/// void
/// </summary>
/// <param name="option"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void updateMarker(u8 option){
    drawMarker();
    selectedOption = option;
    drawMarker();    
}

// ********************************************************************************
/// <summary>
/// checkKeyboardMenu
/// Checks the keyboard for the menu options
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void checkKeyboardMenu()
{
    u8 l;

    //delay(25);
    cpct_waitHalts(25);

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
        l = showMessage("CHOOSE INITIAL LEVEL", NUMBER);
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


// ********************************************************************************
/// <summary>
/// Main process
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void main(void)
{
    // Disable Firmware
    cpct_disableFirmware();

    // Relocate the stack right before the Video Memory
    cpct_setStackLocation(NEW_STACK_LOCATION);
    
    // Activate music before changing interruptions
    activateMusic();
    
    // Change the interruptions table
    cpct_setInterruptHandler((void*) myInterruptHandler);

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

            if ((eyeStep) || ((tick % 20) == 0))
            {
                animEyes();
            }

            if ((footStep) || ((tick % 65) == 0))
            {
                animFoot();
            }
        }
        drawScoreBoard();
        initMarker();
    }
}
