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
#include "sprites/win.h"
#include "compressed/title_z.h"
#include "compressed/dr1_z.h"
#include "compressed/dr2_z.h"
#include "compressed/win_z.h"
#include "audio/arkosPlayer2.h"

#define YPOS 44

TCursor activeCursor1;
TCursor activeCursor2;
TCursor nextCursor1;
TCursor nextCursor2;

u8 level;
//u8 virus1, virus2;
u32 playerLastUpdate1;
u32 playerLastUpdate2;
u8 activePill1, activePill2;
u8 player1Wins;
u8 player2Wins;
u8 hazardLevelFlg;
u32 previousHazard1;
u32 previousHazard2;

u8 *const sprites[3][9] = {
    {emptyCell, sp_upPills_0, sp_downPills_0, sp_leftPills_0, sp_rightPills_0, sp_blocks_0, sp_virus_0, sp_virus_1, sp_virus_2},
    {emptyCell, sp_upPills_1, sp_downPills_1, sp_leftPills_1, sp_rightPills_1, sp_blocks_1, sp_virus_3, sp_virus_4, sp_virus_5},
    {emptyCell, sp_upPills_2, sp_downPills_2, sp_leftPills_2, sp_rightPills_2, sp_blocks_2, sp_virus_6, sp_virus_7, sp_virus_8}};

// title, cursor_speed, #_of_virus, hazard_type, hazard_freq, maxrow, capsuleStep, capsulesPerSpeed, scenario
const TLevel levels[21] = {
    {{"FIRST CONTACT\0"}, 150, 4, 0, 0, 10, 10, 9, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                               //0
    {{"SWORD\0"}, 100, 0, 0, 0, 0, 10, 9, {1, 0x10, 0x10, 0x7C, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x10}},          //1
    {{"THE WALLS\0"}, 90, 0, 0, 0, 6, 10, 9, {1, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81}},      //2
    {{"SPRINT 01\0"}, 70, 8, 0, 0, 8, 10, 9, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                                     //3
    {{"SMILE\0"}, 110, 0, 0, 0, 6, 10, 9, {1, 0x00, 0x3c, 0x42, 0x81, 0x00, 0x00, 0x00, 0x66, 0x66, 0x00}},          //4
    {{"GOING UP??\0"}, 140, 8, 1, 16000, 10, 10, 9, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                              //5
    {{"X\0"}, 110, 0, 1, 16000, 6, 10, 9, {1, 0x00, 0x81, 0x42, 0x20, 0x3c, 0x3c, 0x42, 0x81, 0x00, 0x00}},          //6
    {{"VIRUS ATTACK\0"}, 120, 10, 2, 19000, 9, 10, 9, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                            //7
    {{"THE TOWER\0"}, 140, 0, 0, 0, 8, 10, 9, {1, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}},      //8
    {{"UP THE IRONS\0"}, 130, 12, 1, 15000, 10, 10, 9, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                           //9
    {{"VIRUS MOUNTAIN\0"}, 140, 0, 0, 0, 8, 10, 9, {1, 0xff, 0xff, 0xff, 0x7E, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00}}, //10
    {{"SURPRISE, ITS ME\0"}, 110, 16, 2, 17000, 7, 10, 9, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                        //11
    {{"THE VALLEY\0"}, 110, 0, 0, 0, 7, 10, 9, {1, 0xff, 0xe7, 0xe7, 0xe7, 0xc3, 0xc3, 0xc3, 0x81, 0x81, 0x81}},     //12
    {{"TWO STEPS AT A TIME\0"}, 100, 12, 3, 16000, 10, 10, 9, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                    //13
    {{"SPRINT 02\0"}, 70, 16, 0, 0, 8, 8, 12, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                                    //14
    {{"FULL OR EMPTY?\0"}, 90, 0, 0, 0, 6, 8, 12, {1, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00}}, //15
    {{"BRING ME MORE\0"}, 80, 20, 1, 12000, 10, 8, 12, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                            //16
    {{"THE NET\0"}, 90, 0, 0, 0, 5, 8, 13, {1, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x00, 0x00, 0x00}},        //17
    {{"CHAOS\0"}, 70, 44, 2, 10000, 7, 8, 13, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},                                     //18
    {{"BULLS EYE\0"}, 70, 0, 0, 0, 4, 8, 14, {1, 0x42, 0x99, 0x24, 0x42, 0x5A, 0x5A, 0x42, 0x24, 0x99, 0x42}},       //19
    {{"OK, IT'S TIME\0"}, 60, 50, 2, 10000, 6, 7, 14, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}                              //20
};

// Inital coord: 61, 81
// Final coord: 40, 51
u8 const throwCoordsX[5] = {57, 53, 49, 45, 40};
u8 const throwCoordsY[5] = {70, 50, 30, 40, 51};

//Forward declarations for code clarity
void printScreenVs();
void createSingleVirus(TBoard *b, u8 v);

// ********************************************************************************
// finishSong
//      play end music good and bad
// Returns:
//      void
// ********************************************************************************
void finishSong(u8 win)
{
    if (win)
    {
        music = NO;
        PLY_AKG_INIT(&DRROLANDSOUNDTRACK_START, WIN_SONG);
        music = YES;
    }
    else
    {
        music = NO;
        PLY_AKG_INIT(&DRROLANDSOUNDTRACK_START, LOSE_SONG);
        music = YES;
    }
}

// ********************************************************************************
// printBackground
//      Draws checkered background on the screen
// Input:
// Returns:
//      void.
// ********************************************************************************
void printBackground(u8 color)
{
    u8 i, j;
    u8 *pvmem;

    for (j = 0; j < 20; j++)
    {
        for (i = 0; i < 20; i++)
        {
            //if ((i % 2) == (j % 2))
            if ((i & 1) == (j & 1))
            {
                pvmem = cpct_getScreenPtr(SCR_VMEM, i * 4, j * 10);
                cpct_drawSolidBox(pvmem, cpct_px2byteM0(color, color), 4, 10);
            }
        }
    }
}

// ********************************************************************************
// printScreenSingle
//      Draws "DrRoland" on the screen
// Returns:
//      void.
// ********************************************************************************
void printScreenSingle()
{
    clearScreen(BG_COLOR); // Clear de Screen BGCOLOR=Black
    // Draw background
    printBackground(8); //Green Background

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
// animateThrow
// Returns:
//      void
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
// startAnimateThrow
// Returns:
//      void
// ********************************************************************************
void startAnimateThrow(TCursor *c)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 83);
    cpct_drawSprite(sp_arm02, pvmem, SP_ARM02_W, SP_ARM02_H);
    animateThrow(c, 0);
}

// ********************************************************************************
// printArm01
//      Draws the arm in regular position
// Returns:
//      void
// ********************************************************************************
void printArm01()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 83);
    cpct_drawSprite(sp_arm01, pvmem, SP_ARM01_W, SP_ARM01_H);
}

// ********************************************************************************
// flushMatches
//  Clear the matches that may contain the board 
// Input:
//  b: board
// Returns:
//  void
// ********************************************************************************
void flushMatches(TBoard *b, TBoard *foe){

    // Clear matches until gravity stops
    while (clearMatches(b))
    {
        PLY_AKG_PLAYSOUNDEFFECT(SOUND_LINE, CHANNEL_B, 0);
        if ((foe != NULL) && (b->virusMatched > 1))
            createSingleVirus(foe, b->virusMatched  - 1);
        b->applyingGravity = YES;

        //Apply gravity
        //while (b->applyingGravity)
        //{
        //    applyGravity(b);
        //}
    }
}

// ********************************************************************************
// cursorHit
// Returns:
//      void
// ********************************************************************************
void cursorHit(TBoard *b, TCursor *cur, TBoard *foe)
{
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
    flushMatches(b, foe);
}

// ********************************************************************************
// updatePlayer
//      Updates cursor position based on player's keypresses
// Returns:
//      void
//      cursor updated
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
                //cpct_akp_SFXPlay(2, 15, 60, 0, 0, AY_CHANNEL_C);
                PLY_AKG_PLAYSOUNDEFFECT(SOUND_TURN, CHANNEL_B, 0);
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
                //cpct_akp_SFXPlay(2, 15, 60, 0, 0, AY_CHANNEL_C);
                PLY_AKG_PLAYSOUNDEFFECT(SOUND_TURN, CHANNEL_B, 0);
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
                //cpct_akp_SFXPlay(2, 15, 60, 0, 0, AY_CHANNEL_C);
                PLY_AKG_PLAYSOUNDEFFECT(SOUND_TURN, CHANNEL_B, 0);
                k->fireCooling = FIRE_COOL_TIME;
            }
        }
    }
}

// ********************************************************************************
// printSpecialMarker
// Returns:
//      void
// ********************************************************************************
void printSpecialMarker(u8 x, u8 y)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 12 + (x * 14), (YPOS + 35) + (y * 16));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER2_H, SP_LETTERMARKER2_W, sp_letterMarker2);
}
// ********************************************************************************
// updateText
// Returns:
//      void
// ********************************************************************************
void updateText(u8 *result)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13, (u8)(YPOS + 90));
    cpct_drawSolidBox(pvmem, cpct_px2byteM0(0, 0), 40, 18);
    drawText(result, 13, (u8)(YPOS + 90), COLORTXT_YELLOW, DOUBLEHEIGHT);
}

// ********************************************************************************
// updateTopScoreMarker
// Returns:
//      void
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
// getString
// Returns:
//      void
// ********************************************************************************
void getString(TKeys *k, u8 *result, u8 *title)
{
    u8 i;
    u8 txt[2];
    u8 *pvmem;
    u8 x, y;
    u8 end;
    u8 resultLength;

    activateMusic(NO);
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
    resultLength = strLength(result);
    updateText(result);
    k->fireCooling = 0;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 12 + (x * 3), (YPOS + 37) + (y * 16));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);

    while (!end)
    {
        cpct_waitHalts(20);
        // Check escape
        if (cpct_isKeyPressed(k->abort))
        {
            end = YES;
        }
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
// checkScoreInHallOfFame
// Returns:
//      void
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
        cpct_memset(&name, 0, sizeof(name));
        getString(keys, (u8 *)&name, message);
        strCopy((u8 *)&name, hall->entries[i].name);
        if (score > hall->topScore)
            hall->topScore = score;
    }
}

// ********************************************************************************
// drawActiveCursor
// Returns:
//      void
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
// setInitialBlocks
//      Set the blocks at the beginning
// Returns:
//      void
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
// setInitialBlocks
//      Set the blocks at the beginning
// Returns:
//      void
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
// initLevel
//      Initializes the level for vs mode
// Returns:
//      void
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
        initBoard(&board1, PLAYER1, 53, 68, 57, 19, 47, 178);
        //Set Initial blocks
        setInitialBlocks(&board1, level);
        //Init board2 because we are in a VS game
        initBoard(&board2, PLAYER2, 3, 68, 29, 19, 29, 178);
        //Set Initial blocks
        //setInitialBlocks(&board2, level);
        cpct_memcpy(&board2.color, &board1.color, BOARD_WIDTH*BOARD_HEIGHT*2);
        cpct_memcpy(&board2.virList, &board1.virList, sizeof(TVirusList));
    }
    // Reset score is necessary
    if (resetScore)
    {
        board1.score = 0; // Reset Player 1 Score
        if (type != PLAYER1)
        {
            board2.score = 0; // Reset Player 2 Score if necesary
        }
    }

    // logical initializations
    createInitialSetOfVirus(&board1, level);
    board1.currentDelay = levels[level].cursorSpeed;
    keys1.fireCooling = 0;
    activeCursor1.activePill = NO;
    playerLastUpdate1 = i_time;
    board1.virList.lastUpdate = i_time;
    initCursor(&activeCursor1, &board1.pillQueueIndex);
    initCursor(&nextCursor1, &board1.pillQueueIndex);
    if (type == PLAYER1_VS)
    {
        //createInitialSetOfVirus(&board2, level);
        // Copy content and color
        cpct_memcpy(&board2.color, &board1.color, BOARD_WIDTH*BOARD_HEIGHT*2);
        cpct_memcpy(&board2.virList, &board1.virList, sizeof(TVirusList));
        board2.currentDelay = levels[level].cursorSpeed;
        keys2.fireCooling = 0;
        activeCursor2.activePill = NO;
        playerLastUpdate2 = i_time;
        board2.virList.lastUpdate = i_time;
        initCursor(&activeCursor2, &board2.pillQueueIndex);
        initCursor(&nextCursor2, &board2.pillQueueIndex);
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
    printNextCursor(&nextCursor1, type);
    
    // Vs game configuration
    if (type != PLAYER1)
    {
        drawBoard(&board2);
        printNextCursor(&nextCursor2, PLAYER2);
    }
    hazardLevelFlg = levels[level].hazardFreq > 0; // Set the hazard flag of the level
}

// ********************************************************************************
// initSingleGame
//      Initializes the game
// Returns:
//      void
// ********************************************************************************
void initSingleGame(u8 l)
{

    // Initial values
    level = l;
    initLevel(PLAYER1, YES);
}

// ********************************************************************************
// updateFallingSpeed
//      Main loop of the game
// Returns:
//      void
// ********************************************************************************
void updateFallingSpeed(TBoard *b)
{
    b->capsules++;
    if ((b->capsules % levels[level].capsulesPerSpeedp) == 0) // update current delay every 9 capsules
    {
        if (b->currentDelay > 50)
        {
            b->currentDelay -= levels[level].capsuleStep;
            if (b->currentDelay < b->playerLapse)
                b->playerLapse = b->currentDelay;
        }
        else
        {
            b->currentDelay = 40;
        }
    }
}

// ********************************************************************************
// throwNextPill
//      Throws the next pill to the board
// Input:
// Returns:
//      void
// ********************************************************************************
void throwNextPill(TCursor *activeCursor, TCursor *nextCursor, TBoard *b, u8 type)
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
        initCursor(nextCursor, &b->pillQueueIndex); // In VS mode init next Cursor
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
// finishAnimations
// Input:
//      board
// Returns:
//      void
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
// pushOneline
//      Inserts one line in the board b, pushing everything up
// Input: b Board
// Returns:
//      TRUE if alive, FALSE if dead
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
// runHazard
//      Run the corresponding hazard
// Returns:
//      void
// ********************************************************************************
void runHazard(TCursor *cursor, TBoard *board)
{
    if (cursor->activePill == YES)
        printCursor(board, cursor, CURRENT); // Delete cursor
    if (levels[level].hazardType == 1)
    {
        if (pushOneLine(board))
        {
            if (
                (board->content[cursor->y][cursor->x]) ||
                (board->content[cursor->y + cursor->position][cursor->x + !cursor->position]))
            {
                cursor->y--;
            }
            drawBoardCells(&board1);
        }
        else
        {
            cursor->alive = NO;
        }
    }
    else if (levels[level].hazardType == 2)
    {
        createSingleVirus(board, 1);
    }
    else if (levels[level].hazardType == 3)
    {
        if (pushOneLine(board))
        {
            drawBoardCells(board);
            if (pushOneLine(board))
            {
                drawBoardCells(board);
            }
            else
            {
                cursor->alive = NO;
            }
        }
        else
        {
            cursor->alive = NO;
        }
    }

    if (cursor->activePill == YES)
        printCursor(board, cursor, CURRENT); // Print cursor again;
}
// ********************************************************************************
// capsuleUpdate
// Main loop of the game
// Returns: void
// ********************************************************************************
void capsuleUpdate(TCursor *cursor, TCursor *nextCursor, TBoard *board, u8 type, TBoard *foe)
{
    if ((cursor->activePill == NO) && (board->applyingGravity == NO))
    {
        //Updates falling speed if necessary
        updateFallingSpeed(board);
        // Throw next Pill
        throwNextPill(cursor, nextCursor, board, type);
    }
    else if ((cursor->activePill == YES) && (checkCollisionDown(board, cursor)))
    {
        //cpct_akp_SFXPlay(1, 15, 60, 0, 0, AY_CHANNEL_A);
        //PlaySFX(1);
        PLY_AKG_PLAYSOUNDEFFECT(SOUND_HIT, CHANNEL_B, 0);
        cursorHit(board, cursor, foe);
    }
    else
    {
        cursor->y++;
        cursor->moved = YES;
    }
}

// ********************************************************************************
// winScreen
// Win message after beating the 21 levels
// Returns:
// void
// ********************************************************************************
void winScreen()
{
    drawWindow(10, 32, 64, 122); // 15 = white; 0 blue
    // draw dr win
    drawCompressToScreen(12, 42, G_WIN_W, G_WIN_H, G_WIN_SIZE, (u8 *)&win_z_end);
    drawText("WELL DONE, DOC!!", 35, 47, COLORTXT_YELLOW, DOUBLEHEIGHT);
    drawText("YOU HAVE", 52, 75, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("COMPLETELY", 50, 85, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("DEFEATED", 52, 95, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("THE VIRUS", 50, 105, COLORTXT_WHITE, NORMALHEIGHT);
    drawText("YOU ARE A HERO!!", 34, 133, COLORTXT_RED, DOUBLEHEIGHT);
    wait4OneKey();
}



// ********************************************************************************
// showLevelTitle
//  Shows the indicated level title 
// Input:
//  l: level
// Returns:
//  void
// ********************************************************************************
void showLevelTitle(u8 l){
    sprintf(auxTxt,"LEVEL %d - %s", l, levels[l].title);
    showMessage(auxTxt, NO);
}

// ********************************************************************************
// playSingleGame
// Main loop of the game
// Returns: void
// ********************************************************************************
void playSingleGame(TKeys *keys)
{
    u8 abortGame = 0;
    u32 cycle = 0;

    // Show Level title
    showLevelTitle(level);

    printNextCursor(&activeCursor1, PLAYER1);
    throwNextPill(&activeCursor1, &nextCursor1, &board1, PLAYER1);

    flushMatches(&board1, NULL);

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
        {
            waitKeyUp(keys->music);
            if (current_song != SILENCE)
            {
                showMessage("MUSIC OFF", TEMPORAL);
                deActivateMusic();
            }
            else
            {
                showMessage("MUSIC ON", TEMPORAL);
                activateMusic(YES);
            }
        }

        //If there cells in the list of animatedCells... animate them
        if (board1.animatedCells.count)
        {
            if (cycle % 4 == 0) //Optmization of cycle%2
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
            runHazard(&activeCursor1, &board1);
        }

        //Update player1
        if ((activeCursor1.activePill == YES) && ((i_time - playerLastUpdate1) > board1.playerLapse))
        {
            updatePlayer(&activeCursor1, &board1, keys);
            playerLastUpdate1 = i_time;
        }

        // Draw active cursor
        if (activeCursor1.activePill && activeCursor1.moved)
        {
            drawActiveCursor(&board1, &activeCursor1);
        }

        // Update active Cursor if not in throwing animation and it's time
        if (
            (activeCursor1.activePill != CURSOR_ANIM) &&
            ((i_time - activeCursor1.lastUpdate) > board1.currentDelay) &&
            (board1.animatedCells.count == 0))
        {
            capsuleUpdate(&activeCursor1, &nextCursor1, &board1, PLAYER1, NULL);
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
                initCursor(&nextCursor1, &board1.pillQueueIndex);
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
        // If no virus left, LEVEL IS DONE
        if (board1.virList.count == 0)
        {
            finishAnimations(PLAYER1, &board1, NULL);
            finishSong(YES);
            sprintf(auxTxt, "LEVEL %d CLEARED", level);
            showMessage(auxTxt, 0);
            if (level < 20)
            {
                level++;
                if (level > startingLevel)
                {
                    startingLevel = level;
                }
                initLevel(PLAYER1, NO);
                cycle = 0;
                // Show Level title
                showLevelTitle(level);
                // Flush initial matches
                flushMatches(&board1, NULL);
                previousHazard1 = cycle;
            }
            else
            {
                // You have finished all the levels.
                winScreen();
                checkScoreInHallOfFame(board1.score, level, SINGLE, keys, "WINNER, ENTER YOUR NAME");
                return;
            }
        }
        //Animate Virus
        if ((board1.currentDelay > 80) && ((i_time - board1.virList.lastUpdate) > VIRUS_ANIM_SPEED))
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
        showMessage("YOU ARE DEAD!!", MESSAGE);
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
// printCrowns
// Returns: void
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
// createSingleVirus
// Returns: void
// </summary>
// ********************************************************************************
void createSingleVirus(TBoard *b, u8 v)
{
    u8 x, y;

    do
    {
        do
        {
            x = (cpct_rand8() & 7); //cpct_rand8() % 8
            y = (cpct_rand8() % 6) + 10;

        } while (b->content[y][x] != 0);
        //Make sound
        //cpct_akp_SFXPlay(2, 15, 90, 0, 0, AY_CHANNEL_C);
        PLY_AKG_PLAYSOUNDEFFECT(SOUND_VIRUS, CHANNEL_B, 0);
        //start attack animation
        addAnimatedCell(&b->animatedCells, x, y, YES);
        v--;
    } while (v > 0);
}

// ********************************************************************************
// printScreenVs
// Draws the game area
// Input:
// Returns:    void.
// ********************************************************************************
void printScreenVs()
{
    clearScreen(BG_COLOR); // Clear de Screen BGCOLOR=Black
                           // Draw background
    printBackground(2);    //Grey background

    // print scoreboards
    drawScoreBoardVs(&board1, &board2);

    printCrowns();
}

// ********************************************************************************
// initVsGame
// Initializes the game in vs mode
// Returns: void
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
// resetLevel:
// 
// Returns: void
// ********************************************************************************
void resetLevel(u32 *cycle){
    level = ++level % 21;
    initLevel(PLAYER1_VS, NO);
    // Show Level title
    showLevelTitle(level);
    // Flush initial matches
    flushMatches(&board1, &board2);
    flushMatches(&board2, &board1);
    previousHazard1 = *cycle;
    previousHazard2 = *cycle;
    cycle = 0;
}


// ********************************************************************************
// playVsGame:
// Main loop of the game
// Returns: void
// ********************************************************************************
void playVsGame(TKeys *keys1, TKeys *keys2)
{
    u8 abortGame = 0;
    u32 cycle = 0;

    // Show Level title
    showLevelTitle(level);

    printNextCursor(&activeCursor1, PLAYER1_VS);
    throwNextPill(&activeCursor1, &nextCursor1, &board1, PLAYER1_VS);
    printNextCursor(&activeCursor2, PLAYER2_VS);
    throwNextPill(&activeCursor2, &nextCursor2, &board2, PLAYER2_VS);
    
    // Clear matches until gravity stops for player1
    flushMatches(&board1, &board2);
    // Clear matches until gravity stops for player1
    flushMatches(&board2, &board1);

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
            {
                waitKeyUp(keys1->music);
                if (current_song != SILENCE)
                {
                    showMessage("MUSIC OFF", TEMPORAL);
                    deActivateMusic();
                }
                else
                {
                    showMessage("MUSIC ON", TEMPORAL);
                    activateMusic(YES);
                }
            }

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
                runHazard(&activeCursor1, &board1);
            }
            //Check for Hazards Player 2
            if ((levels[level].hazardType) && ((cycle - previousHazard2) > levels[level].hazardFreq))
            {
                previousHazard2 = cycle;
                runHazard(&activeCursor2, &board2);
            }

            //Update player1
            if ((activeCursor1.activePill == YES) && ((i_time - playerLastUpdate1) > board1.playerLapse))
            {
                updatePlayer(&activeCursor1, &board1, keys1);
                playerLastUpdate1 = i_time;
            }
            // Draw active cursor Player 1
            if (activeCursor1.activePill && activeCursor1.moved)
            {
                drawActiveCursor(&board1, &activeCursor1);
            }

            //Update player2
            if ((activeCursor2.activePill == YES) && ((i_time - playerLastUpdate2) > board2.playerLapse))
            {
                updatePlayer(&activeCursor2, &board2, keys2);
                playerLastUpdate2 = i_time;
            }
            // Draw active cursor Player 2
            if (activeCursor2.activePill && activeCursor2.moved)
            {
                drawActiveCursor(&board2, &activeCursor2);
            }

            // Update active Cursor Player 1
            if (
                ((i_time - activeCursor1.lastUpdate) > board1.currentDelay) &&
                (board1.animatedCells.count == 0))
            {
                capsuleUpdate(&activeCursor1, &nextCursor1, &board1, PLAYER1_VS, &board2);
            }
            // Update active Cursor Player 2
            if (
                ((i_time - activeCursor2.lastUpdate) > board2.currentDelay) &&
                (board2.animatedCells.count == 0))
            {
                capsuleUpdate(&activeCursor2, &nextCursor2, &board2, PLAYER2_VS, &board1);
            }

            // Draw active cursor Player 1
            if (activeCursor1.activePill && activeCursor1.moved)
            {
                drawActiveCursor(&board1, &activeCursor1);
            }
            // Draw active cursor Player 2
            if (activeCursor2.activePill && activeCursor2.moved)
            {
                drawActiveCursor(&board2, &activeCursor2);
            }

            // If no virus left, LEVEL IS DONE
            if (board1.virList.count == 0)
            {
                finishSong(YES);
                finishAnimations(PLAYER1_VS, &board1, &board2);
                sprintf(auxTxt, "PLAYER 1 WINS LEVEL %d", level);
                showMessage(auxTxt, MESSAGE);
                player1Wins++;
                if (player1Wins < 3)
                {
                    resetLevel(&cycle);
                }
            }
            else if (board2.virList.count == 0)
            {
                finishSong(YES);
                finishAnimations(PLAYER2_VS, &board2, &board1);
                sprintf(auxTxt, "PLAYER 2 WINS LEVEL %d", level);
                showMessage(auxTxt, MESSAGE);
                player2Wins++;
                if (player2Wins < 3)
                {
                    resetLevel(&cycle);
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
            sprintf(auxTxt, "PLAYER %d LOSES LEVEL %d", 2 - activeCursor2.alive, level);
            showMessage(auxTxt, 0);

            if (activeCursor1.alive == YES)
                player1Wins++;
            else
                player2Wins++;

            if ((player1Wins < 3) && (player2Wins < 3))
            {
                resetLevel(&cycle);
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