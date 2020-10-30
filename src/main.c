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
//#include "music/dr07.h"
//#include "music/fx04.h"
#include "audio/sound.h"


//const u8 sp_palette0[16] = {
//    0x54, // 0 - black
//    0x4d, // 1 - bright magenta
//    0x40, // 2 - white(gray)
//    0x5c, // 3 - red
//    0x4c, // 4 - bright red
//    //0x4e, // 5 - orange
//    0x47, // 5 - pink
//    0x4A, // 6 - bright yellow
//    //0x52, // 7 - bright green
//    0x52, // 7 - bright green
//    0x4e, // 8 - orange
//    0x5e, // 9 - yellow (pale green)
//    0x53, // 10 - bright cyan
//    0x5f, // 11 - pastel blue
//    0x55, // 12 - bright blue
//    0x58, // 13 - magenta
//    0x44, // 14 - blue
//    0x4b  // 15 - white
//};        // Regular palette

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
        HW_BRIGHT_WHITE
};




const THallOfFame tmpHallSingle = {
    {{"DAVID\0", 20000, 4},
     {"MARTIN\0", 10000, 2},
     {"DIEGO\0", 1000, 1}},
    600};
const THallOfFame tmpHallVs = {
    {{"MARIA\0", 20000, 4},
     {"DIEGO\0", 10000, 2},
     {"MARTIN\0", 1000, 1}},
    600};
u8 *const feetSprites[2] = {sp_feet_0, sp_feet_1};
u8 *const eyeSprites[2] = {sp_eyes_0, sp_eyes_1};
const u8 passwords[21][6] = {
    {"AAAA\0"}, {"IHJK\0"}, {"OAUE\0"}, {"PKLS\0"}, {"ACGT\0"},
    {"SNUP\0"}, {"DPTG\0"}, {"FQZX\0"}, {"GDPE\0"}, {"HNUE\0"},
    {"JTGS\0"}, {"KMOU\0"}, {"LJHS\0"}, {"ZNXR\0"}, {"XHBV\0"},
    {"CFGD\0"}, {"VQYU\0"}, {"BDFG\0"}, {"NJHL\0"}, {"MTYR\0"},
    {"OPQA\0"}
};

// Máscara de transparencia
//cpctm_createTransparentMaskTable(g_tablatrans, 0x200, M0, 0);
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
u8 music;
u8 startingLevel;

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

//THallOfFame hallOfFameSingle; //size: 0x31
//THallOfFame hallOfFameVs;     //size: 0x31
//TKeys keys1;                  //size: 0x1f
//TKeys keys2;                  //size: 0x1f
//TBoard board1;                //size: 0x290
//TBoard board2;                //size: 0x290
//TPill pillQueue[128];         //size: 0x100
//u8 *screenBuffer0;            //size: 0xe10

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
/// <summary>
/// myInterruptHandler
/// Interruphandler that subsitutes the default one. Includes calls for reading the keyboard and playing music, if activated
/// Returns:
/// void
/// </summary>
// ********************************************************************************
void myInterruptHandler()
{

    i_time++;
    g_nInterrupt++;

    if (g_nInterrupt == 3){
        cpct_scanKeyboard();
    }
    else if (g_nInterrupt == 5)
    {
        //cpct_akp_musicPlay();
        PlaySound();
    }
    else if (g_nInterrupt == 6)
    {
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
// ********************************************************************************
void activateMusic()
{
    music = YES;
    //cpct_akp_stop();
    //cpct_akp_musicInit(drroland);
    //cpct_akp_SFXInit(fx);

}

// ********************************************************************************
/// <summary>
/// deActivateMusic
/// deActivate music
/// Returns:
/// void
/// </summary>
// ********************************************************************************
void deActivateMusic()
{
    music = NO;
    //cpct_akp_stop();
    //cpct_akp_musicInit(fx);
    //cpct_akp_SFXInit(fx);
}

// ********************************************************************************
/// <summary>
/// initHAllOf Fame
/// Initializes the keys
/// Returns:
/// <u32> Number of iterations passed
/// </summary>
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
    InitSound();
    activateMusic();

    clearScreen(BG_COLOR);
    // Print Background
    printBackground(13);  //Magenta background

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
/// <summary>
/// printFooter
/// prints the footer on the screen
/// Returns:
/// void
/// </summary>
// ********************************************************************************
void printFooter()
{
    // draw Powered By CPCTelera logo
    drawCompressToScreen(49, 182, G_POW_W, G_POW_H, G_POW_SIZE, (u8 *)&powered_z_end);

    // draw Powered By CPCTelera logo
    drawCompressToScreen(0, 185, G_GLASNOST_W, G_GLASNOST_H, G_GLASNOST_SIZE, (u8 *)&glasnost_z_end);
    //drawText("JOHN LOBO", 12, 179, COLORTXT_WHITE, NORMALHEIGHT);
    //drawText("@ GLASNOST CORP. 2020", 0, 191, COLORTXT_WHITE, NORMALHEIGHT);
}

// ********************************************************************************
/// <summary>
/// drawScoreBoard
/// Returns:
/// void
/// </summary>
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
        //cpct_scanKeyboard_f(); // Scan the keyboard
    } while ((!cpct_isAnyKeyPressed_f()) && c > 0);
}

// ********************************************************************************
/// <summary>
/// help
/// help screen
/// Returns:
/// void
/// </summary>
// ********************************************************************************
//void help()
//{
//
//    clearScreen(BG_COLOR);
//
//    printHeader();
//
//    drawText("HOW TO PLAY", 0, 28, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
//    drawText("DESTROY DE VIRUSES MATCHING 4 OR", 2, 38, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
//    drawText("MORE ELEMENTS IN THE SAME COLORr", 2, 48, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
//
//    drawText("PLAYER 1", 8, 66, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
//    drawText("LEFT :", 9, 76, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("J", 25, 76, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("RIGHT:", 9, 86, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("L", 25, 86, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("DOWN :", 9, 96, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("K", 25, 96, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("TURN :", 9, 106, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("I", 25, 106, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("FIRE :", 9, 116, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("U", 25, 116, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//
//    drawText("PLAYER 2", 50, 66, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
//    drawText("LEFT :", 51, 76, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("A", 67, 76, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("RIGHT:", 51, 86, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("D", 67, 86, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("DOWN :", 51, 96, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("S", 67, 96, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("TURN :", 51, 106, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("W", 67, 106, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("FIRE :", 51, 116, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("Q", 67, 116, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//
//    drawText("PAUSE:", 9, 130, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("H", 25, 130, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//    drawText("ABORT:", 51, 130, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
//    drawText("ESC", 67, 130, COLORTXT_MAUVE, NORMALHEIGHT, TRANSPARENT);
//
//    drawText("VERSUS MODE", 0, 142, COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
//    drawText("CREATE VIRUSES IN YOUR OPPONENT BOARD", 2, 152, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
//    drawText("MATCHING TWO OR MORE ELEMENTS", 2, 162, COLORTXT_ORANGE, NORMALHEIGHT, TRANSPARENT);
//
//    printFooter();
//
//    wait4OneKey();
//}


// ********************************************************************************
/// <summary>
/// void vsHelp()
/// Returns:
/// void
/// </summary>
// ********************************************************************************
//void vsHelp()
//{
//    drawWindow(8, 56, 64, 140); // 15 = white; 0 blue
//    drawText("KEYS FOR VS GAME", 24, 135, COLORTXT_YELLOW, NORMALHEIGHT);
//    drawText("LEFT RIGHT DOWN TURN FIRE", 18, 149, COLORTXT_MAUVE, NORMALHEIGHT);
//    drawText("P1   J     L    K    I    U", 10, 164, COLORTXT_WHITE, NORMALHEIGHT);
//    drawText("P2   A     D    S    W    Q", 10, 179, COLORTXT_WHITE, NORMALHEIGHT);
//    //wait4OneKey();
//}


// ********************************************************************************
/// <summary>
/// void vsHelp()
/// Returns:
/// void
/// </summary>
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
/// <summary>
/// void singleHelp()
/// Returns:
/// void
/// </summary>
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
/// <summary>
/// initMarker
/// Returns:
/// void
/// </summary>
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
// ********************************************************************************
void drawEyes()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 15, 85);
    // Print feet
    cpct_drawSprite(eyeSprites[(eyeStep & 1)], pvmem, SP_EYES_0_W, SP_EYES_0_H);  //eyeStep % 2
}

// ********************************************************************************
/// <summary>
/// animEyes
/// Returns:
/// void
/// </summary>
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
    if (!eyeStep)
    {
        eyeStep = 1;
    }
    else if (eyeStep == 3)
    {
        eyeStep = 0;
    }
    else
    {
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
/// <summary>
/// animFoot
/// Returns:
/// void
/// </summary>
// ********************************************************************************
void animFoot()
{
    if (!footStep)
    {
        footStep = 1;
    }
    else if (footStep == 3)
    {
        footStep = 0;
    }
    else
    {
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
    sprintf(auxTxt,"LEVEL %d - %s",startingLevel,&passwords[startingLevel]);
    drawText(auxTxt,25,145, COLORTXT_WHITE, NORMALHEIGHT);

    drawText("3)", 33, 115, COLORTXT_ORANGE, NORMALHEIGHT);
    drawText("VERSUS MODE", 39, 115, COLORTXT_MAUVE, NORMALHEIGHT);
    //drawText("3)", 33, 115, COLORTXT_ORANGE, NORMALHEIGHT);
    //drawText("HELP", 39, 115, COLORTXT_MAUVE, NORMALHEIGHT);
    // Draw Roland character
    drawCompressToScreen(11, 75, G_DR1_W, G_DR1_H, G_DR1_SIZE, (u8 *)&dr1_z_end);

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
// ********************************************************************************
void updateMarker(u8 option)
{
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
// ********************************************************************************
void checkKeyboardMenu()
{
    u8 i;
    u8 l;
    u8 pass[6];

    //delay(25);
    cpct_waitHalts(20);
    
    // Play single
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
        if (debugMode){
            deActivateMusic();
            initSingleGame(getNumber("CHOOSE INITIAL LEVEL", 41, 0, 20)); // Debug Mode choose start level
        }
        else
        {
            if (startingLevel){
                deActivateMusic();
                initSingleGame(getNumber("CHOOSE INITIAL LEVEL", 41, 0, startingLevel)); // Regular mode starts on last finished level
            }
            else
            {
                drawText("SINGLE MATCH", 27, 50, COLORTXT_MAUVE, DOUBLEHEIGHT);
                drawText("STARTING AT LEVEL", 20, 80, COLORTXT_WHITE, DOUBLEHEIGHT);
                drawText("0", 58, 80, COLORTXT_YELLOW, DOUBLEHEIGHT);
                wait4OneKey(); 
                deActivateMusic();
                initSingleGame(0);
            }
            
        }
        playSingleGame(&keys1);
        activateMusic();
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
        //strCopy(passwords[startingLevel],pass);
        cpct_memset(&pass,0,sizeof(pass));
        getString(&keys1, (u8 *)&pass, "INTRODUCE LEVEL PASSWORD");
        i = 0;
        while ((i<=MAX_LEVEL) && (strCmp((u8*) &passwords[i], (u8*) &pass) == NO)){
            i++;
        }
        if (i<=MAX_LEVEL)
        {
            startingLevel = i;
            sprintf(auxTxt,"LEVEL %d PASSWORD CORRECT", startingLevel);
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
        selectedOption = 1;
        vsHelp();
        if (startingLevel)
            l = getNumber("CHOOSE INITIAL LEVEL", 41, 0, startingLevel);
        else
        {
            l=0;
            drawText("VS MATCH", 30, 50, COLORTXT_MAUVE, DOUBLEHEIGHT);
            drawText("STARTING AT LEVEL", 20, 80, COLORTXT_WHITE, DOUBLEHEIGHT);
            drawText("0", 58, 80, COLORTXT_YELLOW, DOUBLEHEIGHT);
            wait4OneKey();
        }
        deActivateMusic();
        initKeys(VS);
        initVsGame(l);
        playVsGame(&keys1, &keys2);
        initKeys(SINGLE);
        activateMusic();
        drawScoreBoard();
        initMarker();
        drawMenu();
    }

    else if ((cpct_isKeyPressed(keys1.up)) || (cpct_isKeyPressed(keys1.j_up)))
    {
        cpct_akp_SFXPlay(4, 15, 10, 0, 0, AY_CHANNEL_ALL);
        if (selectedOption > 0)
            updateMarker(selectedOption - 1);
        else
            updateMarker(2);
    }
    else if ((cpct_isKeyPressed(keys1.down)) || (cpct_isKeyPressed(keys1.j_down)))
    {
        cpct_akp_SFXPlay(5, 15, 26, 0, 0, AY_CHANNEL_ALL);

        if (selectedOption < 2)
            updateMarker(selectedOption + 1);
        else
            updateMarker(0);
    }
    if (cpct_isKeyPressed(Key_Comma))
    {
        cpct_akp_SFXPlay(7, 14, 26 , 0, 0, AY_CHANNEL_C);
        debugMode = !debugMode;
        if (debugMode)
            showMessage("DEBUG MODE ON", NO);
        else
            showMessage("DEBUG MODE OFF", NO);
    }
}

// ********************************************************************************
/// <summary>
/// Main process
/// </summary>
// ********************************************************************************
void main(void)
{
    // Disable Firmware
    cpct_disableFirmware();

    // Relocate the stack right before the Video Memory
    //cpct_setStackLocation(NEW_STACK_LOCATION);

    // Activate music before changing interruptions
    //activateMusic();

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

            if ((eyeStep) || ((tick & 15) == 0))  // tick % 16
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
