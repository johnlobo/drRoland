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
#include "sprites/glasnost.h"
#include "compressed/powered_z.h"
#include "compressed/title_z.h"
#include "compressed/dr1_z.h"
#include "compressed/glasnost_z.h"
#include "audio/arkosPlayer2.h"

//const u8 sp_palette0[16] = {
//    0x54, // 0 - black
//    0x4d, // 1 - bright magenta
//    0x40, // 2 - white(gray)
//    0x5c, // 3 - red
//    0x4c, // 4 - bright red
//    0x47, // 5 - pink
//    0x4A, // 6 - bright yellow
//    0x52, // 7 - bright green
//    0x4e, // 8 - orange
//    0x5e, // 9 - yellow (pale green)
//    0x53, // 10 - bright cyan
//    0x5f, // 11 - pastel blue
//    0x55, // 12 - bright blue
//    0x58, // 13 - magenta
//    0x44, // 14 - blue
//    0x4b  // 15 - white
//};

const u8 sp_palette0[16] = {
    HW_BLACK,
    HW_BRIGHT_MAGENTA,
    HW_WHITE,
    HW_RED,
    HW_BRIGHT_RED,
    HW_ORANGE,
    HW_BRIGHT_YELLOW,
    HW_PINK,
    HW_GREEN,
    HW_YELLOW,
    HW_BRIGHT_CYAN,
    HW_PASTEL_BLUE,
    HW_BRIGHT_BLUE,
    HW_MAGENTA,
    HW_BLUE,
    HW_BRIGHT_WHITE};

const THallOfFame tmpHallSingle = {
    {{"MARTIN\0", 20000, 4},
     {"DIEGO\0", 10000, 2},
     {"DAVID\0", 1000, 1}},
    20000};
const THallOfFame tmpHallVs = {
    {{"DIEGO\0", 20000, 4},
     {"MARTIN\0", 10000, 2},
     {"MARIA\0", 1000, 1}},
    20000};
u8 *const feetSprites[2] = {sp_feet_0, sp_feet_1};
u8 *const eyeSprites[2] = {sp_eyes_0, sp_eyes_1};
const u8 passwords[21][6] = {
    {"AAAA\0"}, {"SRFG\0"}, {"YPTS\0"}, {"SQAU\0"}, {"KLLT\0"}, 
    {"SPSH\0"}, {"QSCV\0"}, {"WSZX\0"}, {"PLHJ\0"}, {"GFHD\0"}, 
    {"WRNB\0"}, {"KFGF\0"}, {"TGFC\0"}, {"JDSG\0"}, {"YTCB\0"}, 
    {"PRWK\0"}, {"HDVB\0"}, {"GGTT\0"}, {"PYYR\0"}, {"FMNC\0"}, 
    {"OPQA\0"}};

u8 g_nInterrupt; // Manage Interrupt
u32 i_time;
u8 selectedOption;
u8 selectedVirus;
u8 virusState;
u8 footStep;
u8 eyeStep;
u32 lapso;
u32 tick;
u16 score1, score2;
u8 debugMode;
u8 startingLevel;
u8 music;
u8 current_song;

// Relocated variables
// From 0xA700 to 0xa72c there are firmware varibles needed to load dsk
__at(0xa800) TBoard board1;                //size: 0x291
__at(0xaa91) TBoard board2;                //size: 0x291
__at(0xad22) TPill pillQueue[128];         //size: 0x100
__at(0xae22) THallOfFame hallOfFameSingle; //size: 0x4f
__at(0xae71) THallOfFame hallOfFameVs;     //size: 0x4f
__at(0xaec0) TKeys keys1;                  //size: 0x1f
__at(0xaedf) TKeys keys2;                  //size: 0x1f
__at(0xb000) u8 *screenBuffer0;            //size: 0xe10

// Spare space in Video Memory
__at(0xc7d0) u8 *screenSpareBuffer01; //size: 0x2f
__at(0xcfd0) u8 emptyCell[21];        //size: 0x2f used: 0x15
__at(0xd7d0) u8 auxTxt[40];           //size: 0x2f used: 0x28
__at(0xdfd0) u8 *screenSpareBuffer04; //size: 0x2f
__at(0xe7d0) u8 *screenSpareBuffer05; //size: 0x2f
__at(0xefd0) u8 *screenSpareBuffer06; //size: 0x2f
__at(0xf7d0) u8 *screenSpareBuffer07; //size: 0x2f
__at(0xffd0) u8 *screenSpareBuffer08; //size: 0x2f

// ********************************************************************************
// myInterruptHandler
//      Interruphandler that subsitutes the default one. Includes calls for reading
//      the keyboard and playing music, if activated
// Returns:
//      void
// ********************************************************************************
void myInterruptHandler()
{

    i_time++;
    g_nInterrupt++;

    if (g_nInterrupt == 3)
    {
        cpct_scanKeyboard();
    }
    else if ((g_nInterrupt == 5) && music)
    {
        __asm exx
            ex af', af  
            push af
            push bc
            push de
            push hl
            call _PLY_AKG_PLAY
            pop hl
            pop de
            pop bc
            pop af
            ex af', af  
            exx
        __endasm;
    }
    else if (g_nInterrupt == 6)
    {
        g_nInterrupt = 0;
    }
}

void changeSong(u8 song)
{
    music = NO;
    current_song = song;
    PLY_AKG_INIT(&DRROLANDSOUNDTRACK_START, current_song);
    music = YES;
}

// ********************************************************************************
// activateMusic
//      Activate music
// Returns:
//      void
// ********************************************************************************
void activateMusic(u8 random)
{
    u8 song;

    if (random)
    {
        song = (cpct_rand() % 3) + 1;
    }
    else
    {
        song = FEVER_MIX;
    }
    changeSong(song);
}

// ********************************************************************************
// deActivateMusic
//      deActivate music
// Returns:
//      void
// ********************************************************************************
void deActivateMusic()
{
    changeSong(SILENCE);
}

// ********************************************************************************
// initHAllOf Fame
//     Initializes the keys
// Returns:
//      <u32> Number of iterations passed
// ********************************************************************************
void initHallOfFame()
{
    cpct_memcpy(&hallOfFameSingle, &tmpHallSingle, sizeof(THallOfFame));
    cpct_memcpy(&hallOfFameVs, &tmpHallVs, sizeof(THallOfFame));
}

// ********************************************************************************
// initMain
//      main initialization
// Returns:
//      void
// ********************************************************************************
void initMain()
{
    u32 seed; // Value to initialize the random seed

    // Sets Video mode 0
    cpct_setBlendMode(CPCT_BLEND_XOR);
    cpct_setVideoMode(0);
    cpct_setPalette(sp_palette0, 16);
    cpct_setBorder(HW_BLACK);

    // Music on
    changeSong(FEVER_MIX);
    PLY_AKG_INITSOUNDEFFECTS(&FX_SOUNDEFFECTS);

    clearScreen(BG_COLOR);
    // Print Background
    printBackground(13); //Magenta background

    // Shows Press any key message to initializate the random seed
    drawWindow(10, 60, 60, 60); // 15 = white; 0 blue
    drawText("DR.ROLAND IS READY!!", 20, 77, COLORTXT_WHITE, DOUBLEHEIGHT);
    drawText("PRESS ANY KEY TO CONTINUE", 15, 102, COLORTXT_YELLOW, NORMALHEIGHT);

    seed = wait4UserKeypress();
    // Random seed may never be 0, so check first and add 1 if it was 0
    if (!seed)
        seed++;
    cpct_srand(seed);

    // Initilize Keys
    initKeys(SINGLE);

    initHallOfFame();

    // fill EMPTY_CELL buffer with zeroes
    cpct_memset(&emptyCell, 0, 21);

    // setting initially off the debug mode
    debugMode = 0;

    //starting level
    startingLevel = 0;
}

// ********************************************************************************
// printFooter
//      prints the footer on the screen
// Returns: void
// ********************************************************************************
void printFooter()
{
    // draw Powered By CPCTelera logo
    drawCompressToScreen(49, 182, G_POW_W, G_POW_H, G_POW_SIZE, (u8 *)&powered_z_end);

    // draw Powered By CPCTelera logo
    drawCompressToScreen(0, 184, G_GLASNOST_W, G_GLASNOST_H, G_GLASNOST_SIZE, (u8 *)&glasnost_z_end);
}

// ********************************************************************************
// drawScoreBoard
// Returns: void
// ********************************************************************************
void drawScoreBoard()
{
    u8 i;
    u32 c = 0;

    clearScreen(BG_COLOR);

    // draw title logo
    drawCompressToScreen(19, 0, G_TITLE_W, G_TITLE_H, G_TITLE_SIZE, (u8 *)&title_z_end);

    drawText("PLAYER", 18, 38, COLORTXT_ORANGE, NORMALHEIGHT);
    drawText("LEVEL", 40, 38, COLORTXT_ORANGE, NORMALHEIGHT);
    drawText("SCORE", 59, 38, COLORTXT_ORANGE, NORMALHEIGHT);

    drawText("SINGLE MODE", 8, 53, COLORTXT_YELLOW, NORMALHEIGHT);
    for (i = 0; i < 3; i++)
    {
        sprintf(auxTxt, "%1d", i + 1);
        drawText(auxTxt, 9, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT);
        drawText(hallOfFameSingle.entries[i].name, 17, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT);
        sprintf(auxTxt, "%0d", hallOfFameSingle.entries[i].level);
        drawText(auxTxt, 44, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT);
        sprintf(auxTxt, "%06d", hallOfFameSingle.entries[i].score);
        drawText(auxTxt, 58, 65 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT);
    }
    drawText("VERSUS MODE", 8, 113, COLORTXT_YELLOW, NORMALHEIGHT);
    for (i = 0; i < 3; i++)
    {
        sprintf(auxTxt, "%1d", i + 1);
        drawText(auxTxt, 9, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT);
        drawText(hallOfFameVs.entries[i].name, 17, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT);
        sprintf(auxTxt, "%0d", hallOfFameVs.entries[i].level);
        drawText(auxTxt, 44, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT);
        sprintf(auxTxt, "%06d", hallOfFameVs.entries[i].score);
        drawText(auxTxt, 58, 125 + (i * 12), COLORTXT_WHITE, NORMALHEIGHT);
    }
    printFooter();

    c = 30000; // Number of loops passed if not keypressed
    // Wait 'till the user presses a key, counting loop iterations
    do
    {
        c--; // One more cycle
    } while ((!cpct_isAnyKeyPressed_f()) && c > 0);
}

// ********************************************************************************
// void vsHelp()
// Returns: void
// ********************************************************************************
void vsHelp()
{
    drawWindow(8, 32, 64, 140); // 15 = white; 0 blue
    drawText("KEYS FOR VS GAME", 24, 112, COLORTXT_YELLOW, NORMALHEIGHT);
    drawText("FIRE-Q          FIRE-U", 14, 130, COLORTXT_RED, NORMALHEIGHT);
    drawText("       W               I", 14, 130, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("     A S D           J K L", 14, 145, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("P2              P1", 14, 145, COLORTXT_YELLOW, NORMALHEIGHT);
    drawText("JOYSTICK 2      JOYSTICK 1", 14, 160, COLORTXT_ORANGE, NORMALHEIGHT);
}

// ********************************************************************************
// void singleHelp()
// Returns: void
// ********************************************************************************
void singleHelp()
{
    drawWindow(8, 32, 64, 140); // 15 = white; 0 blue
    drawText("KEYS FOR SINGLE GAME", 19, 112, COLORTXT_YELLOW, NORMALHEIGHT);
    drawText("      O  P  Q  A", 22, 130, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("P1", 24, 130, COLORTXT_YELLOW, NORMALHEIGHT);
    drawText("      FIRE-SPACE", 22, 145, COLORTXT_RED, NORMALHEIGHT);
    drawText("      JOYSTICK 1", 22, 160, COLORTXT_ORANGE, NORMALHEIGHT);
}

// ********************************************************************************
// initMarker
// Returns: void
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
// drawEyes
// Returns: void
// ********************************************************************************
void drawEyes()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 15, 85);
    // Print feet
    cpct_drawSprite(eyeSprites[(eyeStep & 1)], pvmem, SP_EYES_0_W, SP_EYES_0_H); //eyeStep % 2
}

// ********************************************************************************
// animEyes
// Returns: void
// ********************************************************************************
void animEyes()
{
    eyeStep = ++eyeStep % 3;

    drawEyes();
    cpct_waitHalts(10);
}

// ********************************************************************************
// drawFoot
// Returns: void
// ********************************************************************************
void drawFoot()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 17, 117);
    // Print feet
    // if footStep is odd draw foot up, else draw foot down
    cpct_drawSprite(feetSprites[(footStep & 1)], pvmem, SP_FEET_0_W, SP_FEET_0_H); //footStep % 2
}

// ********************************************************************************
// animFoot
// Returns: void
// ********************************************************************************
void animFoot()
{
    footStep = ++footStep % 5;
    drawFoot();
    cpct_waitHalts(6);
}

// ********************************************************************************
// drawMarker
// Returns: void
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
// animMarker
// Returns: void
// ********************************************************************************
void animMarker()
{
    drawMarker();
    virusState++;
    drawMarker();
}

// ********************************************************************************
// drawMenu
//      Draw the menu
// Returns: void
// ********************************************************************************
void drawMenu()
{

    clearScreen(BG_COLOR);

    // draw title logo
    drawCompressToScreen(16, 0, G_TITLE_W, G_TITLE_H, G_TITLE_SIZE, (u8 *)&title_z_end);

    drawText("1)", 33, 75, COLORTXT_ORANGE, NORMALHEIGHT);
    drawText("SINGLE MODE", 39, 75, COLORTXT_MAUVE, NORMALHEIGHT);

    drawText("2)", 33, 95, COLORTXT_ORANGE, NORMALHEIGHT);
    drawText("PASSWORD", 39, 95, COLORTXT_MAUVE, NORMALHEIGHT);
    sprintf(auxTxt, "LEVEL %d - %s", startingLevel, &passwords[startingLevel]);
    drawText(auxTxt, 25, 145, COLORTXT_WHITE, NORMALHEIGHT);

    drawText("3)", 33, 115, COLORTXT_ORANGE, NORMALHEIGHT);
    drawText("VERSUS MODE", 39, 115, COLORTXT_MAUVE, NORMALHEIGHT);
    // Draw Roland character
    drawCompressToScreen(11, 75, G_DR1_W, G_DR1_H, G_DR1_SIZE, (u8 *)&dr1_z_end);

    printFooter();

    drawMarker();
}

// ********************************************************************************
// updateMarker
//      Updates the selected option marker
// Returns: void
// ********************************************************************************
void updateMarker(u8 option)
{
    drawMarker();
    selectedOption = option;
    drawMarker();
}

// ********************************************************************************
// checkKeyboardMenu
//      Checks the keyboard for the menu options
// Returns: void
// ********************************************************************************
void checkKeyboardMenu()
{
    u8 i;
    u8 l;
    u8 pass[6];

    //delay(25);
    cpct_waitHalts(25);

    // Play single game
    if (cpct_isKeyPressed(Key_1) ||
        ((
             cpct_isKeyPressed(keys1.fire1) ||
             cpct_isKeyPressed(keys1.j_fire1) ||
             cpct_isKeyPressed(keys1.j_fire2)) &&
         (selectedOption == 0)))
    {
        waitKeyUp(Key_1);
        selectedOption = 0;
        singleHelp();
        if (debugMode)
        {
            deActivateMusic();
            initSingleGame(getNumber("CHOOSE INITIAL LEVEL", 41, 0, 20)); // Debug Mode choose start level
        }
        else
        {
            if (startingLevel)
            {
                deActivateMusic();
                initSingleGame(getNumber("CHOOSE INITIAL LEVEL", 41, 0, startingLevel)); // Regular mode starts on last finished level
            }
            else
            {
                drawText("SINGLE MATCH", 27, 50, COLORTXT_MAUVE, DOUBLEHEIGHT);
                drawText("STARTING AT LEVEL", 20, 80, COLORTXT_WHITE, DOUBLEHEIGHT);
                drawText("0", 58, 80, COLORTXT_YELLOW, DOUBLEHEIGHT);
                wait4OneKey();
                //deActivateMusic();
                activateMusic(YES);
                initSingleGame(0);
            }
        }
        playSingleGame(&keys1);
        activateMusic(NO);
        drawScoreBoard();
        initMarker();
        drawMenu();
    }
    // Introduce password
    else if (
        cpct_isKeyPressed(Key_2) ||
        ((cpct_isKeyPressed(keys1.fire1) ||
          cpct_isKeyPressed(keys1.j_fire1) ||
          cpct_isKeyPressed(keys1.j_fire2)) &&
         (selectedOption == 1)))
    {
        waitKeyUp(Key_2);
        selectedOption = 1;
        cpct_memset(&pass, 0, sizeof(pass));
        getString(&keys1, (u8 *)&pass, "INTRODUCE LEVEL PASSWORD");
        i = 0;
        while ((i <= MAX_LEVEL) && (strCmp((u8 *)&passwords[i], (u8 *)&pass) == NO))
        {
            i++;
        }
        if (i <= MAX_LEVEL)
        {
            startingLevel = i;
            sprintf(auxTxt, "LEVEL %d PASSWORD CORRECT", startingLevel);
            showMessage(auxTxt, MESSAGE);
            initMarker();
            drawMenu();
        }
        else
        {
            showMessage("INCORRECT PASSWORD", MESSAGE);
            initMarker();
            drawMenu();
        }
    }
    // Play VS
    else if (
        cpct_isKeyPressed(Key_3) ||
        ((cpct_isKeyPressed(keys1.fire1) ||
          cpct_isKeyPressed(keys1.j_fire1) ||
          cpct_isKeyPressed(keys1.j_fire2)) &&
         (selectedOption == 2)))
    {
        waitKeyUp(Key_3);
        selectedOption = 2;
        vsHelp();
        if (debugMode)
        {
            //deActivateMusic();
            l=getNumber("CHOOSE INITIAL LEVEL", 41, 0, 20); // Debug Mode choose start level
        }
        else
        if (startingLevel)
            l = getNumber("CHOOSE INITIAL LEVEL", 41, 0, startingLevel);
        else
        {
            l = 0;
            drawText("VS MATCH", 30, 50, COLORTXT_MAUVE, DOUBLEHEIGHT);
            drawText("STARTING AT LEVEL", 20, 80, COLORTXT_WHITE, DOUBLEHEIGHT);
            drawText("0", 58, 80, COLORTXT_YELLOW, DOUBLEHEIGHT);
            wait4OneKey();
        }
        //deActivateMusic();
        activateMusic(YES);
        initKeys(VS);
        initVsGame(l);
        playVsGame(&keys1, &keys2);
        initKeys(SINGLE);
        activateMusic(NO);
        drawScoreBoard();
        initMarker();
        drawMenu();
    }

    else if ((cpct_isKeyPressed(keys1.up)) || (cpct_isKeyPressed(keys1.j_up)))
    {
        PLY_AKG_PLAYSOUNDEFFECT(SOUND_TURN, CHANNEL_B, 0);
        if (selectedOption > 0)
            updateMarker(selectedOption - 1);
        else
            updateMarker(2);
    }
    else if ((cpct_isKeyPressed(keys1.down)) || (cpct_isKeyPressed(keys1.j_down)))
    {
        PLY_AKG_PLAYSOUNDEFFECT(SOUND_TURN, CHANNEL_B, 0);
        if (selectedOption < 2)
            updateMarker(selectedOption + 1);
        else
            updateMarker(0);
    }
    if (cpct_isKeyPressed(Key_L) && cpct_isKeyPressed(Key_O) && cpct_isKeyPressed(Key_B))
    {
 
        debugMode = !debugMode;
        if (debugMode)
        {
            PLY_AKG_PLAYSOUNDEFFECT(SOUND_TURN, CHANNEL_B, 0);
            showMessage("DEBUG MODE ON", NO);
        }
        else
        {
            PLY_AKG_PLAYSOUNDEFFECT(SOUND_TURN, CHANNEL_B, 0);
            showMessage("DEBUG MODE OFF", NO);
        }
    }
}

// ********************************************************************************
// main
//      Main process
// Returns: void
// ********************************************************************************
void main(void)
{
    // Disable Firmware
    cpct_disableFirmware();

    // Change the interruptions table
    g_nInterrupt = 0;

    deActivateMusic();

    cpct_setInterruptHandler(&myInterruptHandler);

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

            if ((footStep) || ((tick & 63) == 0)) // tick % 64
            {
                animFoot();
            }
        }
        drawScoreBoard();
        initMarker();
    }
}
