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
#include "entities/board.h"
#include "entities/cursor.h"
#include "entities/match.h"
#include "text/text.h"
#include "util/util.h"
#include "keyboard/keyboard.h"
#include "sprites/upPills.h"
#include "sprites/downPills.h"
#include "sprites/leftPills.h"
#include "sprites/rightPills.h"
#include "sprites/blocks.h"
#include "sprites/virus.h"
#include "sprites/arm01.h"
#include "sprites/arm02.h"
#include "sprites/title.h"
#include "sprites/drroland01.h"
#include "sprites/drroland02.h"
#include "sprites/letterMarker.h"
#include "sprites/letterMarker2.h"
#include "sprites/okSign.h"
#include "sprites/crown.h"
#include "compressed/title_z.h"
#include "compressed/dr1_z.h"
#include "compressed/dr2_z.h"
#include "music/lose_song.h"
#include "music/win_song.h"
#include "music/fx04.h"

#define YPOS 44

TCursor activeCursor1;
TCursor activeCursor2;
TCursor nextCursor1;
TCursor nextCursor2;

u8 level;
u8 virus1, virus2;
u32 playerLastUpdate1;
u32 playerLastUpdate2;
u8 activePill1, activePill2;
u8 capsules1;
u16 currentDelay1;
u8 capsules2;
u16 currentDelay2;
u8 player1Wins;
u8 player2Wins;
u8 hazardLevelFlg;
u32 previousHazard1;
u32 previousHazard2;

u8 *const sprites[3][9] = {
    {emptyCell, sp_upPills_0, sp_downPills_0, sp_leftPills_0,
     sp_rightPills_0, sp_blocks_0, sp_virus_0, sp_virus_1, sp_virus_2},
    {emptyCell, sp_upPills_1, sp_downPills_1, sp_leftPills_1,
     sp_rightPills_1, sp_blocks_1, sp_virus_3, sp_virus_4, sp_virus_5},
    {emptyCell, sp_upPills_2, sp_downPills_2, sp_leftPills_2,
     sp_rightPills_2, sp_blocks_2, sp_virus_6, sp_virus_7, sp_virus_8}};

const TLevel levels[21] = {
    {{"FIRST CONTACT\0"},       150, 4, 0, 0, 10,       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //0
    {{"STEP BY STEP\0"},        130, 8, 0, 0, 10,       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //1
    {{"SPRINT\0"},              90, 8, 0, 0, 8,         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //2
    {{"GOING UP??\0"},          150, 8, 1, 16000, 10,   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //3
    {{"VIRUS ATTACK\0"},        130, 10, 2, 19000, 9,   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //4
    {{"UP THE IRONS\0"},        140, 12, 1, 15000, 10,  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //5
    {{"THE TOWER\0"},           150, 8, 0, 0, 8,        {0, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}}, //6
    {{"VIRUS MOUNTAIN\0"},      150, 0, 0, 0, 8,        {1, 0xff, 0xff, 0xff, 0x7E, 0x3C, 0x18, 0, 0, 0, 0}}, //7
    {{"SURPRISE, ITS ME\0"},    120, 16, 2, 17000, 7,   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //8
    {{"THE VALLEY\0"},          120, 0, 0, 0, 7,        {1, 0xff, 0xe7, 0xe7, 0xe7, 0xc3, 0xc3, 0, 0x81, 0x81, 0x81}}, //9
    {{"TWO STEPS AT A TIME\0"}, 110, 12, 3, 16000, 10,  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //10
    {{"HEATING UP\0"},          110, 16, 0, 0, 6,       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //11
    {{"MORE POWER\0"},          110, 20, 1, 6000, 6,    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //12
    {{"KEEP IT UP\0"},          100, 24, 0, 0, 6,       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //13
    {{"ROLLING ON\0"},          100, 28, 1, 4000, 6,    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //14
    {{"MORE??\0"},              100, 32, 0, 0, 6,       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //15
    {{"BRING ME MORE\0"},       90, 36, 1, 4000, 6,     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //16
    {{"HOLD ON\0"},             90, 40, 0, 0, 5,        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //17
    {{"GETTING CLOSE\0"},       80, 44, 1, 2000, 5,     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //18
    {{"ALMOST THERE\0"},        80, 48, 0, 0, 4,        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                 //19
    {{"OK, IT'S TIME\0"},       70, 52, 1, 2000, 4,     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}                 //20
};

// Inital coord: 61,81
// Final coord: 40, 51
u8 const throwCoordsX[5] = {57, 53, 49, 45, 40};
u8 const throwCoordsY[5] = {70, 50, 30, 40, 51};

//Forward declarations for code clarity
void printScreenVs();
void createSingleVirus(TBoard *b, u8 v);

// ********************************************************************************
/// <summary>
/// finishSong
/// play end music good and bad
/// Returns:
/// void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void finishSong(u8 win)
{
    cpct_akp_stop();
    if (win)
    {
        cpct_akp_musicInit(win_song);
    }
    else
    {
        cpct_akp_musicInit(end_song);
    }
    cpct_akp_musicPlay();
    while (1)
    {
        if (cpct_akp_songLoopTimes)
        {
            cpct_akp_stop();
            cpct_akp_musicInit(fx);
            cpct_akp_musicPlay();
            break;
        }
    }
}

// ********************************************************************************
/// <summary>
/// printBackground
/// Draws checkered background on the screen
/// Input:
/// Returns:    void.
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printBackground(u8 color) 
{
    u8 i, j;
    u8 *pvmem;

    for (j = 0; j < 12; j++)
    {
        for (i = 0; i < 20; i++)
        {
            //if ((i % 2) == (j % 2))
            if ((i & 1) == (j & 1))
            {
                pvmem = cpct_getScreenPtr(SCR_VMEM, i * 4, j * 16);
                cpct_drawSolidBox(pvmem, cpct_px2byteM0(color, color), 4, 16);
            }
        }
    }
}

// ********************************************************************************
/// <summary>
/// printScreenSingle
/// Draws "DrRoland" on the screen
/// Returns:    void.
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printScreenSingle()
{
    clearScreen(BG_COLOR); // Clear de Screen BGCOLOR=Black
    // Draw background
    printBackground(8);  //Green Background

    // draw title logo
    drawCompressToScreen(30, 7, G_TITLE_W, G_TITLE_H, G_TITLE_SIZE, (u8 *)&title_z_end);

    // print scoreboards
    drawScoreBoard1(&board1);
    drawScoreBoard2(&board1);

    // print Roland
    drawWindow(60, 76, 21, 73);
    drawCompressToScreen(64, 86, G_DR2_W, G_DR2_H, G_DR2_SIZE, (u8 *)&dr2_z_end);

    // Big Virus Container
    drawWindow(3, 95, 21, 80);
}

// ********************************************************************************
/// <summary>
/// animateThrow
/// Returns: void
/// </summary>
/// <param name="cur"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void animateThrow(TCursor *cur, u8 step)
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(SCR_VMEM, throwCoordsX[step], throwCoordsY[step]);
    cpct_getScreenToSprite(pvmem, (u8 *)&screenSpareBuffer01, 6, 7); // Capture screen background
    printCursor2(cur, throwCoordsX[step], throwCoordsY[step]);
    cpct_waitHalts(25);
    cpct_drawSprite(&screenSpareBuffer01, pvmem, 6, 7); // Screen background restore
}

// ********************************************************************************
/// <summary>
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void startAnimateThrow(TCursor *c)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm02, pvmem, SP_ARM02_W, SP_ARM02_H);
    animateThrow(c, 0);
}

// ********************************************************************************
/// <summary>
/// printArm01
/// Returns: void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printArm01()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm01, pvmem, SP_ARM01_W, SP_ARM01_H);
}

// ********************************************************************************
/// <summary>
/// cursorHit
/// Returns: void
/// </summary>
/// <param name="b"></param>
/// <param name="cur"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void cursorHit(TBoard *b, TCursor *cur, TBoard *foe)
{
    u8 countMatches;

    b->content[cur->y][cur->x] = cur->content[0];
    b->color[cur->y][cur->x] = cur->color[0];
    // Add position and neg position to change direction vertical & horizaontal
    b->content[cur->y + cur->position][cur->x + (!cur->position)] = cur->content[1];
    b->color[cur->y + cur->position][cur->x + (!cur->position)] = cur->color[1];

    // Disable active Cursor
    cur->activePill = NO;
    if (cur->y == 0)
    {
        cur->alive = NO;
    }

    // Clear matches until gravity stops
    countMatches = 0;
    while (clearMatches(b))
    {
        cpct_akp_SFXPlay(4, 13, 60, 0, 0, AY_CHANNEL_B);
        countMatches = countMatches + b->virusMatched;
        b->applyingGravity = YES;
    }
    if ((foe != NULL) && (countMatches > 0))
        createSingleVirus(foe, countMatches);
}

// ********************************************************************************
/// <summary>
/// updatePlayer
/// Updates cursor position based on player's keypresses
/// Returns: void && cursor updated
/// </summary>
/// <param name="cur"></param>
/// <param name="b"></param>
/// <param name="k"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void updatePlayer(TCursor *cur, TBoard *b, TKeys *k)
{
    u8 aux;

    // Check downwards movement
    if (cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down))
    {
        if (checkCollisionDown(b, cur) == NO)
        {

            cur->y++;
            cur->moved = YES;
        }
    }
    // Check left movement
    if ((cpct_isKeyPressed(k->left) || cpct_isKeyPressed(k->j_left)) &&
        (checkCollisionLeft(b, cur) == NO))
    {
        cur->x--;
        cur->moved = YES;
        // Check right movement
    }
    else if ((cpct_isKeyPressed(k->right) || cpct_isKeyPressed(k->j_right)) &&
             (checkCollisionRight(b, cur) == NO))
    {
        cur->x++;
        cur->moved = YES;
    }

    if (k->fireCooling > 0)
    {
        k->fireCooling--;
    }
    else
    {
        if (cpct_isKeyPressed(k->up) || cpct_isKeyPressed(k->j_fire1) || cpct_isKeyPressed(k->j_fire2))
        {
            // Check if there is enough space to rotate HOR->VER
            if ((cur->position == HORIZONTAL) && (cur->y > 1) &&
                (b->content[cur->y - 1][cur->x] == 0))
            {
                cur->y--;
                cur->content[0] = 1;
                cur->content[1] = 2;
                cur->moved = YES;
                cur->position = !cur->position;
                cpct_akp_SFXPlay(2, 15, 60, 0, 0, AY_CHANNEL_C);
                k->fireCooling = FIRE_COOL_TIME;
            }
            //Special check for y == 0
            else if ((cur->position == HORIZONTAL) && (cur->y <= 1) &&
                     (b->content[cur->y + 1][cur->x] == 0))
            {
                cur->content[0] = 1;
                cur->content[1] = 2;
                cur->moved = YES;
                cur->position = !cur->position;
                cpct_akp_SFXPlay(2, 15, 60, 0, 0, AY_CHANNEL_C);
                k->fireCooling = FIRE_COOL_TIME;
            }
            // Check if there is enough space to rotate VER->HOR
            else if ((cur->position == VERTICAL) &&
                     ((((cur->x < 7) && (b->content[cur->y + 1][cur->x + 1] == 0)) ||
                       ((cur->x == 7) && (b->content[cur->y + 1][cur->x - 1] == 0)))))
            {
                cur->y++;
                cur->x -= (cur->x == 7); //wall kick to the left if I'm in the last column
                cur->content[0] = 3;
                cur->content[1] = 4;
                aux = cur->color[0];
                cur->color[0] = cur->color[1];
                cur->color[1] = aux;
                cur->moved = YES;
                cur->position = !cur->position;
                cpct_akp_SFXPlay(2, 15, 60, 0, 0, AY_CHANNEL_C);
                k->fireCooling = FIRE_COOL_TIME;
            }
        }
    }
}

// ********************************************************************************
/// <summary>
/// printSpecialMarker
/// Returns: void
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printSpecialMarker(u8 x, u8 y)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 12 + (x * 14), (YPOS + 35) + (y * 16));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER2_H, SP_LETTERMARKER2_W, sp_letterMarker2);
}
// ********************************************************************************
/// <summary>
/// updateText
/// Returns: void
/// </summary>
/// <param name="result"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void updateText(u8 *result)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13, (u8)(YPOS + 90));
    cpct_drawSolidBox(pvmem, cpct_px2byteM0(0, 0), 40, 18);
    drawText(result, 13, (u8)(YPOS + 90), COLORTXT_YELLOW, DOUBLEHEIGHT);
}

// ********************************************************************************
/// <summary>
/// updateTopScoreMarker

/// Returns: void
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="dir"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void updateTopScoreMarker(u8 *x, u8 *y, u8 dir)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 12 + (*x * 3), (YPOS + 37) + (*y * 16));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);

    switch (dir)
    {
    case UP:
        *y = *y - 1;
        break;
    case DOWN:
        *y = *y + 1;
        break;
    case LEFT:
        *x = *x - 1;
        break;
    default:
        *x = *x + 1;
        break;
    }

    pvmem = cpct_getScreenPtr(SCR_VMEM, 12 + (*x * 3), (YPOS + 37) + (*y * 16));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
}

// ********************************************************************************
/// <summary>
/// getTopScoreName
/// Returns: void
/// </summary>
/// <param name="k"></param>
/// <param name="result"></param>
/// <param name="title"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void getTopScoreName(TKeys *k, u8 *result, u8 *title)
{
    u8 i;
    u8 txt[2];
    u8 *pvmem;
    u8 x, y;
    u8 end;
    u8 resultLength;

    activateMusic();
    txt[0] = 'A';
    txt[1] = '\0';
    drawWindow(9, YPOS, 64, 110);
    // Title
    drawText(title, 13, YPOS + 6, COLORTXT_YELLOW, DOUBLEHEIGHT);
    // DrRonald
    drawCompressToScreen(57, YPOS + 25, G_DR1_W, G_DR1_H, G_DR1_SIZE, (u8 *)&dr1_z_end);
    //OK Sign
    pvmem = cpct_getScreenPtr(SCR_VMEM, 53, YPOS + 36);
    //cpct_drawSpriteMaskedAlignedTable(sp_okSign, pvmem, SP_OKSIGN_W, SP_OKSIGN_H, g_tablatrans);
    cpct_drawSprite(sp_okSign, pvmem, SP_OKSIGN_W, SP_OKSIGN_H);

    for (i = 0; i < 26; i++)
    {
        drawText(txt, 13 + ((i % 13) * 3), (YPOS + 39) + ((i / 13) * 15), COLORTXT_WHITE, NORMALHEIGHT);
        txt[0] = 66 + i;
    }
    drawText("SPACE", 13, YPOS + 69, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("DEL", 30, YPOS + 69, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("END", 45, YPOS + 69, COLORTXT_WHITE, NORMALHEIGHT);

    x = 0;
    y = 0;
    end = 0;
    result[0] = '\0';
    resultLength = 0;
    k->fireCooling = 0;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 12 + (x * 3), (YPOS + 37) + (y * 16));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);

    while (!end)
    {
        //delay(20);
        cpct_waitHalts(20);
        // Check downwards movement
        if ((cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down)))
        {
            if (y == 0)
            {
                updateTopScoreMarker(&x, &y, DOWN);
            }
            else if (y == 1)
            {
                pvmem = cpct_getScreenPtr(SCR_VMEM, 12 + (x * 3), (YPOS + 37) + (y * 16));
                cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
                y++;
                if (x < 3)
                {
                    x = 0;
                }
                else if (x < 8)
                {
                    x = 1;
                }
                else
                {
                    x = 2;
                }
                printSpecialMarker(x, y);
            }
        }
        else if ((y > 0) && (cpct_isKeyPressed(k->up) || cpct_isKeyPressed(k->j_up)))
        {
            if (y == 2)
            {
                printSpecialMarker(x, y);
                y--;
                if (x == 1)
                {
                    x = 4;
                }
                else if (x == 2)
                {
                    x = 12;
                }
                pvmem = cpct_getScreenPtr(SCR_VMEM, 12 + (x * 3), (YPOS + 37) + (y * 16));
                cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
            }
            else
            {
                updateTopScoreMarker(&x, &y, UP);
            }
        }
        // Check left movement
        if ((x > 0) && (cpct_isKeyPressed(k->left) || cpct_isKeyPressed(k->j_left)))
        {
            if (y == 2)
            {
                printSpecialMarker(x, y);
                x--;
                printSpecialMarker(x, y);
            }
            else
            {
                updateTopScoreMarker(&x, &y, LEFT);
            }
            // Check right movement
        }
        else if ((x < 12) && (cpct_isKeyPressed(k->right) || cpct_isKeyPressed(k->j_right)))
        {
            if (y < 2)
            {
                updateTopScoreMarker(&x, &y, RIGHT);
            }
            else if (x < 2)
            {
                printSpecialMarker(x, y);
                x++;
                printSpecialMarker(x, y);
            }
        }

        if (k->fireCooling > 0)
        {
            k->fireCooling--;
        }
        else
        {
            if (cpct_isKeyPressed(k->fire1) || cpct_isKeyPressed(k->j_fire1) || cpct_isKeyPressed(k->j_fire2))
            {
                if (resultLength < 10)
                {
                    if (y < 2)
                    {
                        // Get the selected character based on the row and the initial caracter for uppercase and lowercase
                        // 65 is "a" and 97 is "A"
                        result[resultLength] = (65 + x + (13 * y));
                        resultLength++;
                        result[resultLength] = '\0';
                        updateText(result);
                    }
                    else if (x == 0)
                    {
                        result[resultLength] = 32;
                        resultLength++;
                        result[resultLength] = '\0';
                        updateText(result);
                    }
                }
                if (y == 2)
                {
                    if (x == 2)
                    {
                        end = YES;
                    }
                    else if ((x == 1) && (resultLength > 0))
                    {
                        resultLength--;
                        result[resultLength] = '\0';
                        updateText(result);
                    }
                }
                k->fireCooling = FIRE_COOL_TIME;
            }
        }
    }
    wait4OneKey();
}
// ********************************************************************************
/// <summary>
/// checkScoreInHallOfFame
/// Returns: void
/// </summary>
/// <param name="score"></param>
/// <param name="level"></param>
/// <param name="typeOfGame"></param>
/// <param name="keys"></param>
/// <param name="message"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void checkScoreInHallOfFame(u32 score, u8 level, u8 typeOfGame, TKeys *keys, u8 *message)
{
    THallOfFame *hall;
    u8 i, j;
    u8 name[10];

    //select the correpsonding Hall Of Fame
    if (typeOfGame == SINGLE)
        hall = &hallOfFameSingle;
    else
        hall = &hallOfFameVs;
    //Check if the score is higher than any ascore in the Hall Of Fame
    i = 0;
    while ((score < hall->entries[i].score) && (i < 3))
    {
        i++;
    }
    // We got one
    if (i < 3)
    {
        for (j = 2; j > i; j--)
        {
            hall->entries[j].score = hall->entries[j - 1].score;
            hall->entries[j].level = hall->entries[j - 1].level;
            strCopy(hall->entries[j - 1].name, hall->entries[j].name);
        }
        hall->entries[i].score = score;
        hall->entries[i].level = level;
        getTopScoreName(keys, (u8 *)&name, message);
        strCopy((u8 *)&name, hall->entries[i].name);
        if (score > hall->topScore)
            hall->topScore = score;
    }
}

// ********************************************************************************
/// <summary>
/// drawActiveCursor
/// Returns:
/// </summary>
/// <param name="b"></param>
/// <param name="cur"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void drawActiveCursor(TBoard *b, TCursor *cur)
{
    printCursor(b, cur, PREVIOUS); // 0 = previous coordinates
    printCursor(b, cur, CURRENT);  // 1 = current coordinates
    cur->px = cur->x;
    cur->py = cur->y;
    cur->ppos = cur->position;
    cur->pcolor[0] = cur->color[0];
    cur->pcolor[1] = cur->color[1];
    cur->pcontent[0] = cur->content[0];
    cur->pcontent[1] = cur->content[1];
    cur->lastUpdate = i_time;
    cur->moved = 0;
}

// ********************************************************************************
/// <summary>
/// setInitialBlocks
/// Set the blocks at the beginning

/// Returns: void
/// </summary>
/// <param name=""></param>
/// <created>johnlobo,28/09/2020</created>
/// <changed>johnlobo,28/09/2020</changed>
// ********************************************************************************
void setRandomCell(TBoard *b, u8 x, u8 y, u8 virus)
{
    if (virus)
    {
        createVirus(b, NO, x, y);
    }
    else
    {
        b->content[y][x] = 5;
        b->color[y][x] = (cpct_rand8() % 3);
    }
}

// ********************************************************************************
/// <summary>
/// setInitialBlocks
/// Set the blocks at the beginning

/// Returns: void
/// </summary>
/// <param name=""></param>
/// <created>johnlobo,28/09/2020</created>
/// <changed>johnlobo,28/09/2020</changed>
// ********************************************************************************
void setInitialBlocks(TBoard *b, u8 l)
{
    u8 i;
    u8 virus;

    virus = levels[l].scenario[0];

    for (i = 1; i < 11; i++)
    {
        if (levels[l].scenario[i] != 0)
        {
            if (levels[l].scenario[i] & 1)
                setRandomCell(b, 0, 17 - i, virus);
            if (levels[l].scenario[i] & 2)
                setRandomCell(b, 1, 17 - i, virus);
            if (levels[l].scenario[i] & 4)
                setRandomCell(b, 2, 17 - i, virus);
            if (levels[l].scenario[i] & 8)
                setRandomCell(b, 3, 17 - i, virus);
            if (levels[l].scenario[i] & 16)
                setRandomCell(b, 4, 17 - i, virus);
            if (levels[l].scenario[i] & 32)
                setRandomCell(b, 5, 17 - i, virus);
            if (levels[l].scenario[i] & 64)
                setRandomCell(b, 6, 17 - i, virus);
            if (levels[l].scenario[i] & 128)
                setRandomCell(b, 7, 17 - i, virus);
        }
    }
}

// ********************************************************************************
/// <summary>
/// initLevel
/// Initializes the level for vs mode
/// Returns: void
/// </summary>
/// <param name="resetScore"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void initLevel(u8 type, u8 resetScore)
{
    //Initializes the pill queue
    initPillQueue();
    // 1 PLAYER configuration
    if (type == PLAYER1)
    {
        // init bigvirusOnScreen flag array
        resetBigVirus();
        // Init board in single player position
        initBoard(&board1, PLAYER1, 27, 68, 16, 19, 74, 179);
        //Set Initial blocks
        setInitialBlocks(&board1, level);
    }
    else
    {
        // Init board1 in VS player position
        initBoard(&board1, PLAYER1, 53, 68, 29, 19, 47, 178);
        //Set Initial blocks
        setInitialBlocks(&board1, level);
        //Init board2 because we are in a VS game
        initBoard(&board2, PLAYER2, 3, 68, 57, 19, 29, 178);
        //Set Initial blocks
        setInitialBlocks(&board2, level);
    }
    // Reset score is necessary
    if (resetScore)
    {
        board1.score = 0; // Reset Player 1 Score
        if (type == PLAYER1_VS)
        {
            board2.score = 0; // Reset Player 2 Score if necesary
        }
    }

    // logical initializations
    createInitialSetOfVirus(&board1, level);
    pillQueueIndex1 = 0;
    capsules1 = 0;
    currentDelay1 = levels[level].cursorSpeed;
    keys1.fireCooling = 0;
    activeCursor1.activePill = NO;
    playerLastUpdate1 = i_time;
    board1.virList.lastUpdate = i_time;
    initCursor(&activeCursor1, &pillQueueIndex1);
    initCursor(&nextCursor1, &pillQueueIndex1);
    if (type == PLAYER1_VS)
    {
        createInitialSetOfVirus(&board2, level);
        pillQueueIndex2 = 0;
        capsules2 = 0;
        currentDelay2 = levels[level].cursorSpeed;
        keys2.fireCooling = 0;
        activeCursor2.activePill = NO;
        board2.virList.lastUpdate = i_time;
        playerLastUpdate2 = i_time;
        initCursor(&activeCursor2, &pillQueueIndex2);
        initCursor(&nextCursor2, &pillQueueIndex2);
    }

    // Visual initializations
    // Draw Screen
    if (type == PLAYER1)
    {
        printScreenSingle();
        printBigVirus(&board1);
    }
    else
    {
        printScreenVs();
    }
    drawBoard(&board1);
    clearMatches(&board1); // Clean the matches appeared after creating all the viruses
    printNextCursor(&nextCursor1, type);
    // Vs game configuration
    if (type == PLAYER1_VS)
    {
        drawBoard(&board2);
        clearMatches(&board2);
        printNextCursor(&nextCursor2, PLAYER2);
    }
    hazardLevelFlg = levels[level].hazardFreq > 0; // Set the hazard flag of the level
    // Show Level title
    showMessage(levels[level].title, NO);
}

// ********************************************************************************
/// <summary>
/// initSingleGame
/// Initializes the game
/// Returns: void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void initSingleGame(u8 l)
{

    // Initial values
    level = l;
    initLevel(PLAYER1, YES);
}

// ********************************************************************************
/// <summary>
/// updateFallingSpeed
/// Main loop of the game
/// Returns: void
/// </summary>
/// <param name="caps"></param>
/// <param name="curDelay"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void updateFallingSpeed(u8 *caps, u16 *curDelay)
{
    (*caps)++;
    if ((*caps & CAPSULES_PER_SPEED) == 0)   // *caps % 8
    {   
        if (*curDelay > 10)
            *curDelay -= CAPSULE_STEP;
        else
        {
            *curDelay = 0;
        }
    }
    //sprintf(auxTxt,".%d..%d.", *caps, *curDelay);
    //drawText(auxTxt,0,180,COLORTXT_YELLOW,NORMALHEIGHT);
}

// ********************************************************************************
/// <summary>
/// throwNextPill
/// Throws the next pill to the board
/// Input:
/// Returns: void
/// </summary>
/// <param name="activeCursor"></param>
/// <param name="nextCursor"></param>
/// <param name="pillQueueIndex"></param>
/// <param name="b"></param>
/// <param name="type"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void throwNextPill(TCursor *activeCursor, TCursor *nextCursor, u8 *pillQueueIndex, TBoard *b, u8 type)
{
    cpct_memcpy(activeCursor, nextCursor, sizeof(TCursor));
    if (type == PLAYER1)
    {
        startAnimateThrow(nextCursor); // In Single mode start throwing animation
        b->throwing = 1;
        activeCursor->activePill = CURSOR_ANIM;
    }
    else
    {
        initCursor(nextCursor, pillQueueIndex); // In VS mode init next Cursor
        printNextCursor(nextCursor, type);
        printCursor(b, activeCursor, CURRENT);
        if ((b->content[1][3]) || (b->content[1][4]))
        {
            activeCursor->alive = NO;
        }
        else
        {
            activeCursor->activePill = YES;
            activeCursor->lastUpdate = i_time;
        }
    }
}

// ********************************************************************************
/// <summary>
/// finishAnimations
/// Input: board
/// Returns: void
/// </summary>
/// <param name="board"></param>
/// <created>johnlobo,23/08/2019</created>
/// <changed>johnlobo,23/08/2019</changed>
// ********************************************************************************
void finishAnimations(u8 type, TBoard *b1, TBoard *b2)
{
    while (
        ((b1->applyingGravity) || (b1->animatedCells.count)) ||
        ((b2 != NULL) && ((b2->applyingGravity) || (b2->animatedCells.count))))
    {
        if (b1->applyingGravity)
        {
            applyGravity(b1);
            if (type == PLAYER1)
            {
                printBigVirus(b1);
            }
        }
        if ((b2 != NULL) && (b2->applyingGravity))
        {
            applyGravity(b2);
        }
        if (b1->animatedCells.count)
        {
            animateCells(b1, type);
        }
        if ((b2 != NULL) && (b2->animatedCells.count))
        {
            animateCells(b2, type);
        }
    }
}

// ********************************************************************************
/// <summary>
/// pushOneline
/// Inserts one line in the board b, pushing everything up
/// Input: b Board
/// Returns: TRUE if alive, FALSE if dead
/// </summary>
/// <param name="keys"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************

// TODO: push animated cells

u8 pushOneLine(TBoard *b)
{
    u8 i, j;
    u8 color, p_color;
    //Move all rows up
    for (j = 1; j < BOARD_HEIGHT; j++)
    {
        for (i = 0; i < BOARD_WIDTH; i++)
        {
            b->color[j - 1][i] = b->color[j][i];
            b->content[j - 1][i] = b->content[j][i];
        }
    }

    //push virus
    for (i = 0; i < 20; i++)
    {
        if (b->virList.virusList[i].type)
        {
            b->virList.virusList[i].y--;
        }
    }

    j = BOARD_HEIGHT - 1;
    p_color = 99; // Assign big number to avoid collision during first round
                  //Fill the last line with random color balls
    for (i = 0; i < BOARD_WIDTH; i++)
    {
        color = (cpct_rand8() % 3);
        while (color == p_color)
        {
            color = (cpct_rand8() % 3);
        }
        p_color = color;
        b->color[j][i] = color;
        b->content[j][i] = 5; // Balls
    }

    // Clear matches until gravity stops
    while (clearMatches(b))
    {
        //b->applyingGravity = YES;
        applyGravity(b);
    }
    //Check if something hitted the top
    i = 0;
    j = 0;
    do
    {
        if (b->content[j][i])
            return FALSE;
        i++;
    } while (i < BOARD_WIDTH);
    return TRUE;
}

// ********************************************************************************
/// <summary>
/// playSingleGame
/// Main loop of the game

/// Returns: void
/// </summary>
/// <param name="keys"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void playSingleGame(TKeys *keys)
{
    u8 abortGame = 0;
    u32 cycle = 0;
    printNextCursor(&activeCursor1, PLAYER1);
    throwNextPill(&activeCursor1, &nextCursor1, &pillQueueIndex1, &board1, PLAYER1);

    // Clear matches until gravity stops
    while (clearMatches(&board1)){
        board1.applyingGravity = YES;
        while (board1.applyingGravity)
        {
            applyGravity(&board1);
        }
    }

    previousHazard1 = cycle;
    // Loop forever
    do
    {

        //Increment cycle
        cycle++;

        //Check Abort Game
        if (cpct_isKeyPressed(keys->abort))
            abortGame = showMessage("ABORT THE GAME??", YES);

        //check Pause Game
        if (cpct_isKeyPressed(keys->pause))
            showMessage("GAME PAUSED", NO);

        //Switch on/off music
        if (cpct_isKeyPressed(keys->music))
            if (music)
                deActivateMusic();
            else
                activateMusic();

        //If there cells in the list of animatedCells... animate them
        if (board1.animatedCells.count)
        {
            if (cycle % 5 == 0) //Optmization of cycle%2
            {
                animateCells(&board1, PLAYER1);
            }
        }

        //If the flag for applying gravity is set, and there is no match animation left, then applygravity
        if ((board1.animatedCells.count == 0) && (board1.applyingGravity == YES))
        {
            if ((cycle & 1) == 0) //animate every two cycles
                applyGravity(&board1);
        }

        //Check for Hazards
        if ((levels[level].hazardType) && ((cycle - previousHazard1) > levels[level].hazardFreq))
        {
            previousHazard1 = cycle;
            if (activeCursor1.activePill == YES)
                printCursor(&board1, &activeCursor1, CURRENT); // Delete cursor

            if (levels[level].hazardType == 1)
            {
                if (pushOneLine(&board1))
                {
                    if (
                        (board1.content[activeCursor1.y][activeCursor1.x]) ||
                        (board1.content[activeCursor1.y + activeCursor1.position][activeCursor1.x + !activeCursor1.position]))
                    {
                        activeCursor1.y--;
                    }
                    drawBoardCells(&board1);
                }
                else
                {
                    activeCursor1.alive = NO;
                }
            }
            else if (levels[level].hazardType == 2)
            {
                createSingleVirus(&board1, 1);
            }
            else if (levels[level].hazardType == 3)
            {
                if (pushOneLine(&board1))
                {
                    drawBoardCells(&board1);

                    if (pushOneLine(&board1))
                    {
                        drawBoardCells(&board1);
                    }
                    else
                    {
                        activeCursor1.alive = NO;
                    }
                }
                else
                {
                    activeCursor1.alive = NO;
                }
            }

            if (activeCursor1.activePill == YES)
                printCursor(&board1, &activeCursor1, CURRENT); // Print cursor again;
        }

        //Update player1
        if ((activeCursor1.activePill == YES) && ((i_time - playerLastUpdate1) > PLAYER_SPEED))
        {
            updatePlayer(&activeCursor1, &board1, keys);
            playerLastUpdate1 = i_time;
        }

        // Update active Cursor if not in throwing animation and it's time
        if (
            (activeCursor1.activePill != CURSOR_ANIM) && 
            ((i_time - activeCursor1.lastUpdate) > currentDelay1) &&
            (board1.animatedCells.count == 0)
            )
        {
            if ((activeCursor1.activePill == NO) && (board1.applyingGravity == NO))
            {
                //Updates falling speed if necessary
                updateFallingSpeed(&capsules1, &currentDelay1);

                // Throw next Pill
                throwNextPill(&activeCursor1, &nextCursor1, &pillQueueIndex1, &board1, PLAYER1);
            }
            else if ((activeCursor1.activePill == YES) && (checkCollisionDown(&board1, &activeCursor1)))
            {
                cpct_akp_SFXPlay(1, 15, 60, 0, 0, AY_CHANNEL_A);
                cursorHit(&board1, &activeCursor1, NULL);
            }
            else
            {
                activeCursor1.y++;
                activeCursor1.moved = YES;
            }
        }

        // Draw active cursor
        if (activeCursor1.activePill && activeCursor1.moved)
        {
            drawActiveCursor(&board1, &activeCursor1);
        }
        //Update the throwing animation every two cycles
        if (((cycle & 1) == 0) && (board1.throwing != NO))
        {
            animateThrow(&nextCursor1, board1.throwing);
            board1.throwing++;
            //End of throwing animation??
            if (board1.throwing > 4)
            {
                board1.throwing = NO;
                initCursor(&nextCursor1, &pillQueueIndex1);
                printArm01();
                printNextCursor(&nextCursor1, PLAYER1);
                printCursor(&board1, &activeCursor1, CURRENT);
                if ((board1.content[1][3]) || (board1.content[1][4]))
                {
                    activeCursor1.alive = NO;
                }
                else
                {
                    activeCursor1.activePill = YES;
                    activeCursor1.lastUpdate = i_time;
                }
            }
        }
        // If no virus left, level is done
        if (board1.virList.count == 0)
        {
            finishAnimations(PLAYER1, &board1, NULL);
            finishSong(YES);
            sprintf(auxTxt, "LEVEL %d CLEARED", level);
            showMessage(auxTxt, 0);
            if (level < 20)
            {
                level++;
                initLevel(PLAYER1, NO);
                //activeCursor1.activePill = NO;
                //playerLastUpdate1 = i_time;
                //board1.virList.lastUpdate = i_time;
                cycle = 0;
                //initCursor(&nextCursor1, &pillQueueIndex1);
            }
            else
            {
                // You have finished all the levels.
                showMessage("CONGRATULATIONS.YOU HAVE DEFEATED THE VIRUS", 0);
                checkScoreInHallOfFame(board1.score, level, SINGLE, keys, "WINNER, ENTER YOUR NAME");
                return;
            }
        }
        //Animate Virus
        if ((i_time - board1.virList.lastUpdate) > VIRUS_ANIM_SPEED)
        {
            drawVirusList(&board1);
            board1.virList.lastUpdate = i_time;
        }

    } while ((activeCursor1.alive == YES) && (abortGame == NO));

    finishSong(NO);

    if (abortGame)
        showMessage("GAME TERMINATED", 0);
    else
    {
        finishAnimations(PLAYER1, &board1, NULL);
        showMessage("YOU ARE DEAD!!", 0);
    }
    // Checks if the score is among the top scores
    checkScoreInHallOfFame(board1.score, level, SINGLE, keys, "TOP SCORE.ENTER YOUR NAME");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Vs Section
//
////////////////////////////////////////////////////////////////////////////////////////////////////

// ********************************************************************************
/// <summary>
/// printCrowns

/// Returns: void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printCrowns()
{
    u8 i;
    u8 *pvmem;

    // print crowns
    for (i = 0; i < player2Wins; i++)
    {
        pvmem = cpct_getScreenPtr(SCR_VMEM, 33, 84 + (i * 20));
        cpct_drawSprite(sp_crown, pvmem, SP_CROWN_W, SP_CROWN_H);
    }
    for (i = 0; i < player1Wins; i++)
    {
        pvmem = cpct_getScreenPtr(SCR_VMEM, 42, 84 + (i * 20));
        cpct_drawSprite(sp_crown, pvmem, SP_CROWN_W, SP_CROWN_H);
    }
}

// ********************************************************************************
/// <summary>
/// createSingleVirus

/// Returns: void
/// </summary>
/// <param name="b"></param>
/// <param name="v"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void createSingleVirus(TBoard *b, u8 v)
{
    u8 x, y;

    do
    {
        do
        {
            x = (cpct_rand8() & 7);  //cpct_rand8() % 8
            y = (cpct_rand8() % 6) + 10;

        } while (b->content[y][x] != 0);
        //Make sound
        cpct_akp_SFXPlay(2, 15, 90, 0, 0, AY_CHANNEL_C);
        //start attack animation
        addAnimatedCell(&b->animatedCells, x, y, YES);
        v--;
    } while (v > 0);
}

// ********************************************************************************
/// <summary>
/// printScreenVs
/// Draws the game area
/// Input:
/// Returns:    void.
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printScreenVs()
{
    clearScreen(BG_COLOR); // Clear de Screen BGCOLOR=Black
                           // Draw background
    printBackground(2);  //Grey background

    // print scoreboards
    drawScoreBoardVs(&board1, &board2);

    printCrowns();
}

// ********************************************************************************
/// <summary>
/// initVsGame
/// Initializes the game in vs mode

/// Returns: void
/// </summary>
/// <param name="l"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void initVsGame(u8 l)
{

    // Initial values
    level = l;
    player1Wins = 0;
    player2Wins = 0;
    initLevel(PLAYER1_VS, YES);
}

// ********************************************************************************
/// <summary>
/// playVsGame:
/// Main loop of the game

/// Returns: void
/// </summary>
/// <param name="keys1"></param>
/// <param name="keys2"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void playVsGame(TKeys *keys1, TKeys *keys2)
{
    u8 abortGame = 0;
    u32 cycle = 0;

    printNextCursor(&activeCursor1, PLAYER1_VS);
    throwNextPill(&activeCursor1, &nextCursor1, &pillQueueIndex1, &board1, PLAYER1_VS);
    printNextCursor(&activeCursor2, PLAYER2_VS);
    throwNextPill(&activeCursor2, &nextCursor2, &pillQueueIndex2, &board2, PLAYER2_VS);
    // Clear matches until gravity stops for player1
    while (clearMatches(&board1)){
        board1.applyingGravity = YES;
        while (board1.applyingGravity)
        {
            applyGravity(&board1);
        }
    }

    // Clear matches until gravity stops for player2
    while (clearMatches(&board2)){
        board2.applyingGravity = YES;
        while (board2.applyingGravity)
        {
            applyGravity(&board2);
        }
    }

    previousHazard1 = cycle;
    previousHazard2 = cycle;
    // Loop forever
    do
    {
        do
        {
            //Increment cycle
            cycle++;

            //Abort Game
            if (cpct_isKeyPressed(keys1->abort))
                abortGame = showMessage("ABORT THE GAME??", YES);

            // Pause Game
            if (cpct_isKeyPressed(keys1->pause))
                showMessage("GAME PAUSED", NO);
            
             //Switch on/off music
            if (cpct_isKeyPressed(keys1->music))
                if (music)
                    deActivateMusic();
                else
                    activateMusic();

            //If there cells in the list of animatedCells... animate them
            if (board1.animatedCells.count)
            {
                if (cycle % 5 == 0) 
                {
                    animateCells(&board1, PLAYER1_VS);
                    //continue;
                }
            }

            //If there cells in the list of animatedCells... animate them
            if (board2.animatedCells.count)
            {
                if (cycle % 5 == 0) 
                {
                    animateCells(&board2, PLAYER2_VS);
                    //continue;
                }
            }

            //If the flag for applying gravity is set, and there is no match animation left, then applygravity
            if ((board1.animatedCells.count == 0) && (board1.applyingGravity))
            {
                if ((cycle & 1) == 0) //animate every two cycles
                    applyGravity(&board1);
            }
            //If the flag for applying gravity is set, and there is no match animation left, then applygravity
            if ((board2.animatedCells.count == 0) && (board2.applyingGravity))
            {
                if ((cycle & 1) == 0) //animate every two cycles
                    applyGravity(&board2);
            }

            //Check for Hazards Player 1
            if ((levels[level].hazardType) && ((cycle - previousHazard1) > levels[level].hazardFreq))
            {
                previousHazard1 = cycle;
                if (activeCursor1.activePill == YES)
                    printCursor(&board1, &activeCursor1, CURRENT); // Delete cursor

                if (levels[level].hazardType == 1)
                {
                    if (pushOneLine(&board1))
                    {
                        if (
                            (board1.content[activeCursor1.y][activeCursor1.x]) ||
                            (board1.content[activeCursor1.y + activeCursor1.position][activeCursor1.x + !activeCursor1.position]))
                        {
                            activeCursor1.y--;
                        }
                        drawBoardCells(&board1);
                    }
                    else
                    {
                        activeCursor1.alive = NO;
                    }
                }
                else if (levels[level].hazardType == 2)
                {
                    createSingleVirus(&board1, 1);
                }
                else if (levels[level].hazardType == 3)
                {
                    if (pushOneLine(&board1))
                    {
                        drawBoardCells(&board1);

                        if (pushOneLine(&board1))
                        {
                            drawBoardCells(&board1);
                        }
                        else
                        {
                            activeCursor1.alive = NO;
                        }
                    }
                    else
                    {
                        activeCursor1.alive = NO;
                    }
                }

                if (activeCursor1.activePill == YES)
                    printCursor(&board1, &activeCursor1, CURRENT); // Print cursor again;
            }

            //Check for Hazards Player 2
            if ((levels[level].hazardType) && ((cycle - previousHazard2) > levels[level].hazardFreq))
            {
                previousHazard2 = cycle;
                if (activeCursor2.activePill == YES)
                    printCursor(&board2, &activeCursor2, CURRENT); // Delete cursor

                if (levels[level].hazardType == 1)
                {
                    if (pushOneLine(&board2))
                    {
                        if (
                            (board2.content[activeCursor2.y][activeCursor2.x]) ||
                            (board2.content[activeCursor2.y + activeCursor2.position][activeCursor2.x + !activeCursor2.position]))
                        {
                            activeCursor2.y--;
                        }
                        drawBoardCells(&board2);
                    }
                    else
                    {
                        activeCursor2.alive = NO;
                    }
                }
                else if (levels[level].hazardType == 2)
                {
                    createSingleVirus(&board2, 1);
                }
                else if (levels[level].hazardType == 3)
                {
                    if (pushOneLine(&board2))
                    {
                        drawBoardCells(&board2);

                        if (pushOneLine(&board2))
                        {
                            drawBoardCells(&board2);
                        }
                        else
                        {
                            activeCursor2.alive = NO;
                        }
                    }
                    else
                    {
                        activeCursor2.alive = NO;
                    }
                }

                if (activeCursor2.activePill == YES)
                    printCursor(&board2, &activeCursor2, CURRENT); // Print cursor again;
            }

            //Update player1
            if ((activeCursor1.activePill == YES) && ((i_time - playerLastUpdate1) > PLAYER_SPEED))
            {
                updatePlayer(&activeCursor1, &board1, keys1);
                playerLastUpdate1 = i_time;
            }

            //Update player2
            if ((activeCursor2.activePill == YES) && ((i_time - playerLastUpdate2) > PLAYER_SPEED))
            {
                updatePlayer(&activeCursor2, &board2, keys2);
                playerLastUpdate2 = i_time;
            }

            // Update active Cursor Player 1
           if (
            ((i_time - activeCursor1.lastUpdate) > currentDelay1) &&
            (board1.animatedCells.count == 0)
            )
            {
                if ((activeCursor1.activePill == NO) && (board1.applyingGravity == NO))
                {
                    //Updates falling speed if necessary
                    updateFallingSpeed(&capsules1, &currentDelay1);

                    // Throw next Pill
                    throwNextPill(&activeCursor1, &nextCursor1, &pillQueueIndex1, &board1, PLAYER1_VS);
                }
                else if ((activeCursor1.activePill == YES) && (checkCollisionDown(&board1, &activeCursor1)))
                {
                    cpct_akp_SFXPlay(1, 15, 60, 0, 0, AY_CHANNEL_A);
                    cursorHit(&board1, &activeCursor1, &board2);
                }
                else
                {
                    activeCursor1.y++;
                    activeCursor1.moved = YES;
                }
            }

            if (
            ((i_time - activeCursor2.lastUpdate) > currentDelay2) &&
            (board2.animatedCells.count == 0)
            )
            {
                if ((activeCursor2.activePill == NO) && (board2.applyingGravity == NO))
                {
                    //Updates falling speed if necessary
                    updateFallingSpeed(&capsules2, &currentDelay2);

                    // Throw next Pill
                    throwNextPill(&activeCursor2, &nextCursor2, &pillQueueIndex2, &board2, PLAYER2_VS);
                }
                else if ((activeCursor2.activePill == YES) && (checkCollisionDown(&board2, &activeCursor2)))
                {
                    cpct_akp_SFXPlay(1, 15, 40, 0, 0, AY_CHANNEL_A);
                    cursorHit(&board2, &activeCursor2, &board1);
                }
                else
                {
                    activeCursor2.y++;
                    activeCursor2.moved = YES;
                }
            }

            // Draw active cursor
            if (activeCursor1.activePill && activeCursor1.moved)
            {
                drawActiveCursor(&board1, &activeCursor1);
            }
            if (activeCursor2.activePill && activeCursor2.moved)
            {
                drawActiveCursor(&board2, &activeCursor2);
            }

            // If no virus left, level is done
            if (board1.virList.count == 0)
            {
                finishSong(YES);
                finishAnimations(PLAYER1_VS, &board1, &board2);
                sprintf(auxTxt, "PLAYER 1 WINS LEVEL %d", level);
                showMessage(auxTxt, MESSAGE);
                player1Wins++;
                if (player1Wins < 3)
                {
                    level++;
                    initLevel(PLAYER1_VS, NO);
                }
            }
            else if (board2.virList.count == 0)
            {
                finishSong(YES);
                finishAnimations(PLAYER2_VS, &board1, &board2);
                sprintf(auxTxt, "PLAYER 2 WINS LEVEL %d", level);
                showMessage(auxTxt, MESSAGE);
                player2Wins++;
                if (player2Wins < 3)
                {
                    level++;
                    initLevel(PLAYER1_VS, NO);
                }
            }
            //Animate Virus
            if ((i_time - board1.virList.lastUpdate) > VIRUS_ANIM_SPEED)
            {
                drawVirusList(&board1);
                drawVirusList(&board2);
                board1.virList.lastUpdate = i_time;
            }

        } while ((activeCursor1.alive == YES) && (activeCursor2.alive == YES) && (abortGame == NO));

        finishSong(NO);

        if (abortGame == NO)
        {
            finishAnimations(PLAYER1_VS, &board1, &board2);
            sprintf(auxTxt, "PLAYER %d LOSES LEVEL %d", 1 + activeCursor2.alive, level);
            showMessage(auxTxt, 0);

            if (activeCursor1.alive == YES)
                player1Wins++;
            else
                player2Wins++;

            if ((player1Wins < 3) && (player2Wins < 3))
            {
                level++;
                initLevel(PLAYER1_VS, NO);
                cycle = 0;
            }
            else
                printCrowns();
        }

    } while ((player1Wins < 3) && (player2Wins < 3) && (abortGame == NO));

    if (abortGame)
        showMessage("GAME TERMINATED", 0);
    else
    {
        finishSong(YES);
        sprintf(auxTxt, "PLAYER %d WINS THE MATCH!!", (player2Wins == 3) + 1);
        showMessage(auxTxt, 0);
    }
    checkScoreInHallOfFame(board1.score, level, VS, keys1, "PLAYER1 ENTER YOUR NAME");
    checkScoreInHallOfFame(board2.score, level, VS, keys2, "PLAYER2 ENTER YOUR NAME");
}