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
#include "sprites/upPills.h"
#include "sprites/downPills.h"
#include "sprites/leftPills.h"
#include "sprites/rightPills.h"
#include "sprites/blocks.h"
#include "sprites/virus.h"
#include "util/util.h"
#include "entities/board.h"
#include "entities/cursor.h"
#include "text/text.h"
#include "sprites/drroland02.h"
#include "sprites/arm01.h"
#include "sprites/arm02.h"
#include "sprites/title.h"
#include "sprites/viruses-big.h"
#include "sprites/drroland01.h"
#include "sprites/letterMarker.h"
#include "sprites/letterMarker2.h"
#include "sprites/okSign.h"

TBoard board1;
TBoard board2;
TCursor activeCursor1;
TCursor activeCursor2;
TCursor nextCursor1;
TCursor nextCursor2;

u8 level;
u8 virus1, virus2;
u32 playerLastUpdate;
u8 activePill1, activePill2;
u8 capsules1;
u8 speedDelta1;
u16 currentSpeed1;
u8 capsules2;
u8 speedDelta2;
u16 currentSpeed2;
u8 bigVirusOnScreen[3];

u8 *const sprites[3][9] = {
    {EMPTY_CELL, sp_upPills_0, sp_downPills_0, sp_leftPills_0,
     sp_rightPills_0, sp_blocks_0, sp_virus_0, sp_virus_1, sp_virus_2},
    {EMPTY_CELL, sp_upPills_1, sp_downPills_1, sp_leftPills_1,
     sp_rightPills_1, sp_blocks_1, sp_virus_3, sp_virus_4, sp_virus_5},
    {EMPTY_CELL, sp_upPills_2, sp_downPills_2, sp_leftPills_2,
     sp_rightPills_2, sp_blocks_2, sp_virus_6, sp_virus_7, sp_virus_8}};
u8 *const spritesBigVirus[9] = {sp_viruses_big_0, sp_viruses_big_1, sp_viruses_big_2};
u8 const dimension_W[3][9] = {
    {EMPTYCELL_WIDTH, SP_UPPILLS_0_W, SP_DOWNPILLS_0_W, SP_LEFTPILLS_0_W,
     SP_RIGHTPILLS_0_W, SP_BLOCKS_0_W, SP_VIRUS_0_W, SP_VIRUS_1_W, SP_VIRUS_2_W},
    {EMPTYCELL_WIDTH, SP_UPPILLS_1_W, SP_DOWNPILLS_1_W, SP_LEFTPILLS_1_W,
     SP_RIGHTPILLS_1_W, SP_BLOCKS_1_W, SP_VIRUS_3_W, SP_VIRUS_4_W, SP_VIRUS_5_W},
    {EMPTYCELL_WIDTH, SP_UPPILLS_2_W, SP_DOWNPILLS_2_W, SP_LEFTPILLS_2_W,
     SP_RIGHTPILLS_2_W, SP_BLOCKS_2_W, SP_VIRUS_6_W, SP_VIRUS_7_W, SP_VIRUS_8_W}};
u8 const dimension_H[3][9] = {
    {EMPTYCELL_HEIGHT, SP_UPPILLS_0_H, SP_DOWNPILLS_0_H, SP_LEFTPILLS_0_H,
     SP_RIGHTPILLS_0_H, SP_BLOCKS_0_H, SP_VIRUS_0_H, SP_VIRUS_1_H, SP_VIRUS_2_H},
    {EMPTYCELL_HEIGHT, SP_UPPILLS_1_H, SP_DOWNPILLS_1_H, SP_LEFTPILLS_1_H,
     SP_RIGHTPILLS_1_H, SP_BLOCKS_1_H, SP_VIRUS_3_H, SP_VIRUS_4_H, SP_VIRUS_5_H},
    {EMPTYCELL_HEIGHT, SP_UPPILLS_2_H, SP_DOWNPILLS_2_H, SP_LEFTPILLS_2_H,
     SP_RIGHTPILLS_2_H, SP_BLOCKS_2_H, SP_VIRUS_6_H, SP_VIRUS_7_H, SP_VIRUS_8_H}};

u16 const cursorSpeedPerLevel[20] = {150, 140, 140, 130, 130, 120, 120, 120, 110, 110, 110, 100, 100, 100, 90, 90, 80, 80, 70, 70};

// Inital coord: 61,81
// Final coord: 40, 51
u8 const throwCoordsX[5] = {57, 53, 49, 45, 40};
u8 const throwCoordsY[5] = {70, 50, 30, 40, 51};

//////////////////////////////////////////////////////////////////
//  initBigVirusOnScreen
//
//  Input: void
//
//  Returns: void
//
void initBigVirusOnScreen()
{
    u8 n;

    for (n = 0; n < 3; n++)
    {
        bigVirusOnScreen[n] = 0;
    }
}

//////////////////////////////////////////////////////////////////
//  printBigVirus
//
//  Input: void
//
//  Returns: void
//
void printBigVirus(TBoard *b)
{
    u8 n;
    u8 *pvmem;

    for (n = 0; n < 3; n++)
    {
        if ((u8)(b->virList.colorCount[n] > 0) != bigVirusOnScreen[n])
        {
            pvmem = cpct_getScreenPtr(SCR_VMEM, 5 + (SP_VIRUSES_BIG_1_W * (n == 1)), 100 + (SP_VIRUSES_BIG_1_H * n));
            cpct_drawSpriteBlended(pvmem, SP_VIRUSES_BIG_1_H, SP_VIRUSES_BIG_1_W, (u8 *)spritesBigVirus[n]);
            bigVirusOnScreen[n] = (b->virList.colorCount[n] > 0);
        }
    }
}

//////////////////////////////////////////////////////////////////
//  printScreenSingle
//  Draws "DrRoland" on the screen
//  Input:      Level
//
//  Returns:    void.
//
void printScreenSingle()
{
    u8 *pvmem;
    u8 i, j;

    clearScreen(BG_COLOR); // Clear de Screen BGCOLOR=Black
    cpct_waitVSYNC();      // Sync with the raster to avoid flickering
    // Draw background
    for (j = 0; j < 13; j++)
    {
        for (i = 0; i < 40; i++)
        {
            if ((i % 2) == (j % 2))
            {
                pvmem = cpct_getScreenPtr(SCR_VMEM, i * 4, j * 16);
                cpct_drawSolidBox(pvmem, cpct_px2byteM0(2, 2), 4, 8);
            }
        }
    }
    // print title
    cpct_waitVSYNC(); // Sync with the raster to avoid flickering
    pvmem = cpct_getScreenPtr(SCR_VMEM, 30, 7);
    cpct_drawSpriteMaskedAlignedTable(sp_title, pvmem, SP_TITLE_W, SP_TITLE_H, g_tablatrans);

    // clear game area
    printScoreBoard1(&board1);
    printScoreBoard2(&board1);

    pvmem = cpct_getScreenPtr(SCR_VMEM, 64, 86);
    cpct_drawSprite(sp_drroland02, pvmem, SP_DRROLAND02_W, SP_DRROLAND02_H);
    // Big Virus Container
    drawWindow(3, 95, 21, 80, 15, 0);
}

//////////////////////////////////////////////////////////////////
//  animateThrow
//
//  Input: void
//
//  Returns: void
//
void animateThrow(TCursor *cur)
{
    u8 *pvmem;
    u8 n;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm02, pvmem, SP_ARM02_W, SP_ARM02_H);
    for (n = 0; n < 5; n++)
    {
        pvmem = cpct_getScreenPtr(SCR_VMEM, throwCoordsX[n], throwCoordsY[n]);
        cpc_GetSp((u8 *)screenBuffer, 7, 6, pvmem); // Capture screen background
        printCursor2(cur, throwCoordsX[n], throwCoordsY[n]);
        delay(25);
        cpct_drawSprite((u8 *)screenBuffer, pvmem, 6, 7); // Screen background restore
    }
    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm01, pvmem, SP_ARM01_W, SP_ARM01_H);
}

//////////////////////////////////////////////////////////////////
//  printArm01
//
//  Input: void
//
//  Returns: void
//
void printArm01()
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm01, pvmem, SP_ARM01_W, SP_ARM01_H);
}

//////////////////////////////////////////////////////////////////
//  cursorHitSingle
//
//  Input: void
//
//  Returns: void
//
void cursorHitSingle(TBoard *b, TCursor *cur)
{
    b->content[cur->y][cur->x] = cur->content[0];
    b->color[cur->y][cur->x] = cur->color[0];
    // Add position and neg position to change direction vertical & horizaontal
    b->content[cur->y + cur->position][cur->x + (!cur->position)] = cur->content[1];
    b->color[cur->y + cur->position][cur->x + (!cur->position)] = cur->color[1];

    // Clear matches until gravity stops
    while (clearMatches(b))
    {
        applyGravity(b);
        printBigVirus(b);
    }

    cur->activePill = NO;
    if (cur->y == 0)
    {
        cur->alive = NO;
    }
}

//////////////////////////////////////////////////////////////////
// animateAttack
//
//  Input:
//  Output:
//
//
void animateAttack(TBoard *b, u8 x, u8 y)
{
    u8 i;

    for (i = 0; i < 3; i++)
    {
        printHitSpriteXY(x, y, i);
        delay(60);
        deleteCell(b, x, y);
    }
}

//////////////////////////////////////////////////////////////////
//  attackFoe
//
//  Input: void
//
//  Returns: void
//
void attackFoe(TBoard *b, u8 v)
{
    u8 x, y;
    u8 color;

    do
    {
        do
        {
            x = (cpct_rand8() % 8);
            y = (cpct_rand8() % 6) + 10;

        } while (b->content[y][x] != 0);
        animateAttack(b, x, y); // animate the creation of the new virus
        color = (cpct_rand8() % 3);
        b->content[y][x] = 6;                  // 6 is Virus order in the content array;
        b->color[y][x] = color;                // Assign a random color
        addVirus(&b->virList, x, y, 6, color); // add Virus to de list of baterias
        printVirusList(b);
        printSingleVirusCount(b);
        v--;
    } while (v > 0);
}

//////////////////////////////////////////////////////////////////
//  cursorHitVs
//
//  Input: void
//
//  Returns: void
//
void cursorHitVs(TBoard *b, TCursor *cur, TBoard *foe)
{
    u8 countMatches;

    b->content[cur->y][cur->x] = cur->content[0];
    b->color[cur->y][cur->x] = cur->color[0];
    // Add position and neg position to change direction vertical & horizaontal
    b->content[cur->y + cur->position][cur->x + (!cur->position)] = cur->content[1];
    b->color[cur->y + cur->position][cur->x + (!cur->position)] = cur->color[1];

    // Clear matches until gravity stops
    countMatches = 0;
    while (clearMatches(b) > 0)
    {
        countMatches = countMatches + b->virusMatched;
        applyGravity(b);
    }
    if (countMatches > 1)
        attackFoe(foe, countMatches);

    cur->activePill = 0;
    if (cur->y == 0)
    {
        cur->alive = NO;
    }
}

//////////////////////////////////////////////////////////////////
//  updatePlayer
//  Updates cursor position based on player's keypresses
//
//  Input: cursor, board & keys
//
//  Returns: void && cursor updated
//
void updatePlayer(TCursor *cur, TBoard *b, TBoard *foe, TKeys *k, u8 typeOfGame)
{
    u8 aux;

    // Check downwards movement
    if (cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down))
    {
        if (checkCollisionDown(b, cur) == YES)
        {
            if (typeOfGame == SINGLE)
                cursorHitSingle(b, cur);
            else     
                cursorHitVs(b, cur, foe);
        }
        else
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
            if ((cur->position == HORIZONTAL) && (cur->y>0) && (b->content[cur->y-1][cur->x] == 0))  
            {
                cur->y--;
                cur->content[0] = 1;
                cur->content[1] = 2;
                cur->moved = YES;
                cur->position = !cur->position;
            }
            // Check if there is enough space to rotate VER->HOR
            else if (((cur->y<7) && (b->content[cur->y+1][cur->x+1] == 0)) ||
                ((cur->y == 7) && (b->content[cur->y+1][cur->x-1] == 0)))
            {
                cur->y++;
                cur->x -= (cur->x==7); //wall kick to the left if I'm in the last column
                cur->content[0] = 3;
                cur->content[1] = 4;
                aux = cur->color[0];
                cur->color[0] = cur->color[1];
                cur->color[1] = aux;
                cur->moved = YES;
                cur->position = !cur->position;
            }
            k->fireCooling = FIRE_COOL_TIME;
        }
    }
}

//////////////////////////////////////////////////////////////////
//  printSpecialMarker
//
//  Input: void
//
//  Returns: void
//
void printSpecialMarker(u8 x, u8 y)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13 + (x * 14), 64 + (y * 12));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER2_H, SP_LETTERMARKER2_W, sp_letterMarker2);
}
//////////////////////////////////////////////////////////////////
//  updateText
//
//  Input: void
//
//  Returns: void
//
void updateText(u8 *result)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 20, 134);
    cpct_drawSolidBox(pvmem, cpct_px2byteM0(0, 0), 40, 18);
    drawText(result, 14, 134, COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);
}
//////////////////////////////////////////////////////////////////
//  updateTopScoreMarker
//
//  Input: void
//
//  Returns: void
//
void updateTopScoreMarker(u8 *x, u8 *y, u8 dir)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13 + (*x * 3), 64 + (*y * 12));
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

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13 + (*x * 3), 64 + (*y * 12));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
}

//////////////////////////////////////////////////////////////////
//  getTopScoreName
//
//  Input: void
//
//  Returns: void
//

void getTopScoreName(TKeys *k, u8 *result, u8 *title)
{
    u8 i;
    u8 txt[2];
    u8 *pvmem;
    u8 x, y;
    u8 end;
    u8 resultLength;

    txt[0] = 'A';
    txt[1] = '\0';
    drawWindow(10, 36, 64, 122, 15, 0);
    // Title
    drawText(title, 14, 42, COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);
    // DrRonald
    pvmem = cpct_getScreenPtr(SCR_VMEM, 57, 66);
    cpct_drawSpriteMaskedAlignedTable(sp_drroland01, pvmem, SP_DRROLAND01_W, SP_DRROLAND01_H, g_tablatrans);
    pvmem = cpct_getScreenPtr(SCR_VMEM, 54, 78);
    cpct_drawSpriteMaskedAlignedTable(sp_okSign, pvmem, SP_OKSIGN_W, SP_OKSIGN_H, g_tablatrans);

    for (i = 0; i < 26; i++)
    {
        drawText(txt, 14 + ((i % 13) * 3), 66 + ((i / 13) * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        txt[0] = 66 + i;
    }
    txt[0] = 'a';
    for (i = 0; i < 26; i++)
    {
        drawText(txt, 14 + ((i % 13) * 3), 90 + ((i / 13) * 12), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        txt[0] = 98 + i;
    }
    drawText("space", 14, 114, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("del", 31, 114, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("end", 46, 114, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);

    x = 0;
    y = 0;
    end = 0;
    result[0] = '\0';
    resultLength = 0;
    k->fireCooling = 0;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 13 + (x * 3), 64 + (y * 12));
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);

    while (!end)
    {
        delay(20);
        // Check downwards movement
        if ((cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down)))
        {
            if (y < 3)
            {
                updateTopScoreMarker(&x, &y, DOWN);
            }
            else if (y == 3)
            {
                pvmem = cpct_getScreenPtr(SCR_VMEM, 13 + (x * 3), 64 + (y * 12));
                cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
                y = 4;
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
            if (y == 4)
            {
                printSpecialMarker(x, y);
                y = 3;
                if (x == 1)
                {
                    x = 4;
                }
                else if (x == 2)
                {
                    x = 12;
                }
                pvmem = cpct_getScreenPtr(SCR_VMEM, 13 + (x * 3), 64 + (y * 12));
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
            if (y == 4)
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
            if (y < 4)
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
                if (resultLength < 20)
                {
                    if (y < 4)
                    {
                        // Get the selected character based on the row and the initial caracter for uppercase and lowercase
                        // 65 is "a" and 97 is "A"
                        result[resultLength] = ((y < 2) * (65 + x + (13 * y))) + ((y > 1) * (97 + x + (13 * (y - 2))));
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
                if (y == 4)
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

//////////////////////////////////////////////////////////////////
// checkScoreInHallOfFame
//
//  Input: void
//
//  Returns: void
//

void checkScoreInHallOfFame(u16 score, u8 level, u8 typeOfGame, TKeys *keys, u8 *message)
{
    THallOfFame *hall;
    u8 i, j;
    u8 name[20];

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
        getTopScoreName(keys, (u8*)&name, message);
        strCopy(hall->entries[i].name, (u8 *)&name);
        if (score > hall->topScore)
            hall->topScore = score;
    }
}

//////////////////////////////////////////////////////////////////
// drawActiveCursor
//
//  Input:
//
//  Returns:
//
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

//////////////////////////////////////////////////////////////////
//  initSingleLevel
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//
void initSingleLevel()
{
    clearScreen(BG_COLOR);
    initBigVirusOnScreen();
    // Init board
    initBoard(&board1, 30, 76, 16, 19, 74, 179);
    createVirus(&board1, level);
    initPillQueue();
    pillQueueIndex1 = 0;
    printScreenSingle();
    printBigVirus(&board1);
    printBoard(&board1);
    capsules1 = 0;
    speedDelta1 = 0;
    currentSpeed1 = cursorSpeedPerLevel[level];
    keys1.fireCooling = 0;
}

//////////////////////////////////////////////////////////////////
//  initSingleGame
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//
void initSingleGame()
{

    // Initial values
    level = 1;
    board1.score = 0;
    initSingleLevel();
}

//////////////////////////////////////////////////////////////////
// updateFallingSpeed
//  Main loop of the game
//
//  Input: void
//  Returns: void
//
void updateFallingSpeed(u8 *caps, u8 *speedD, u16 *curSpeed)
{
    (*caps)++;
    //Update cursor speed
    if ((*curSpeed > 0) && (*speedD < 25) && ((*caps % CAPSULES_PER_SPEED) == 0))
    {
        (*speedD)++;
        if (*curSpeed > (*speedD * CAPSULE_STEP))
        {
            (*curSpeed) -= (*speedD * CAPSULE_STEP);
        }
        else
        {
            *curSpeed = 0;
        }
    }
}

//////////////////////////////////////////////////////////////////
// playSingleGame
//  Main loop of the game
//
//  Input: void
//
//  Returns: void
//
void playSingleGame(TKeys *keys)
{
    u8 abortGame = 0;

    playerLastUpdate = i_time;
    board1.virList.lastUpdate = i_time;
    initCursor(&activeCursor1, &pillQueueIndex1);
    activeCursor1.activePill = YES;
    printCursor(&board1, &activeCursor1, CURRENT);
    initCursor(&nextCursor1, &pillQueueIndex1);
    printNextCursor(&nextCursor1, PLAYER1);
    // Loop forever
    do
    {
        //debug
        sprintf(AUX_TXT, "%05d", capsules1);
        drawText(AUX_TXT, 0, 50, COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
        sprintf(AUX_TXT, "%05d", speedDelta1);
        drawText(AUX_TXT, 0, 60, COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
        sprintf(AUX_TXT, "%05d", currentSpeed1);
        drawText(AUX_TXT, 0, 70, COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
        //debug
        //Abort Game
        if (cpct_isKeyPressed(keys->abort))
        {
            abortGame = showMessage("Abort the game??", YES);
        }
        // Pause Game
        if (cpct_isKeyPressed(keys->pause))
        {
            showMessage("Game Paused", NO);
        }
        // Update active Cursor
        if ((i_time - activeCursor1.lastUpdate) > currentSpeed1)
        {
            if (activeCursor1.activePill == NO)
            {
                //Updates falling speed if necessary
                updateFallingSpeed(&capsules1, &speedDelta1, &currentSpeed1);
                //debug
                sprintf(AUX_TXT, "%05d", capsules1);
                drawText(AUX_TXT, 0, 50, COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
                sprintf(AUX_TXT, "%05d", speedDelta1);
                drawText(AUX_TXT, 0, 60, COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
                sprintf(AUX_TXT, "%05d", currentSpeed1);
                drawText(AUX_TXT, 0, 70, COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
                //wait4OneKey();
                //debug
                // Copy next piece over active
                cpct_memcpy(&activeCursor1, &nextCursor1, sizeof(TCursor));
                animateThrow(&nextCursor1);
                initCursor(&nextCursor1, &pillQueueIndex1);
                printArm01();
                printNextCursor(&nextCursor1, PLAYER1);
                printCursor(&board1, &activeCursor1, CURRENT);
                activeCursor1.activePill = YES;
            }
            else if (checkCollisionDown(&board1, &activeCursor1))
            {
                cursorHitSingle(&board1, &activeCursor1);
            }
            else
            {
                activeCursor1.y++;
                activeCursor1.moved = 1;
            }
        }
        //Update player
        if ((i_time - playerLastUpdate) > PLAYER_SPEED)
        {
            updatePlayer(&activeCursor1, &board1, NULL, keys, SINGLE);
            playerLastUpdate = i_time;
        }
        // Draw active cursor
        if (activeCursor1.activePill && activeCursor1.moved)
        {
            drawActiveCursor(&board1, &activeCursor1);
        }
        if (board1.virList.count == 0)
        {
            sprintf(AUX_TXT, "Good Job!! Level %d Cleared", level);
            showMessage(AUX_TXT, 0);
            if (level < 20)
            {
                level++;
                initSingleLevel();
                activeCursor1.activePill = NO;
                playerLastUpdate = i_time;
                board1.virList.lastUpdate = i_time;
                initCursor(&nextCursor1, &pillQueueIndex1);
            }
            else
            {
                // You have finished all the levels.
                showMessage("Congatulations.You have defeated the virus", 0);
                checkScoreInHallOfFame(board1.score, level, SINGLE, keys, "Winner, enter your name");
                return;
            }
        }

        //Animate Virus
        if ((i_time - board1.virList.lastUpdate) > BACT_ANIM_SPEED)
        {
            //cpct_waitVSYNC();
            animateVirusList(&board1);
            board1.virList.lastUpdate = i_time;
        }

    } while ((activeCursor1.alive == YES) && (abortGame == 0));

    if (abortGame)
        showMessage("Game terminated", 0);
    else
        showMessage("Your are dead!!", 0);

    // Checks if the score is among the top scores
    checkScoreInHallOfFame(board1.score, level, SINGLE, keys, "Top Score.Enter your name");
}

/////////////////////////////////////////////////////////////////
//
// Vs Section
//
/////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//  printScreenVs
//  Draws "DrRoland" on the screen
//  Input:      Level
//
//  Returns:    void.
//
void printScreenVs()
{
    u8 *pvmem;
    u8 i, j;

    clearScreen(BG_COLOR); // Clear de Screen BGCOLOR=Black
    cpct_waitVSYNC();      // Sync with the raster to avoid flickering
    // Draw background
    for (j = 0; j < 13; j++)
    {
        for (i = 0; i < 40; i++)
        {
            if ((i % 2) == (j % 2))
            {
                pvmem = cpct_getScreenPtr(SCR_VMEM, i * 4, j * 16);
                cpct_drawSolidBox(pvmem, cpct_px2byteM0(2, 2), 4, 8);
            }
        }
    }
    // print title
    cpct_waitVSYNC(); // Sync with the raster to avoid flickering
    pvmem = cpct_getScreenPtr(SCR_VMEM, 30, 7);
    cpct_drawSpriteMaskedAlignedTable(sp_title, pvmem, SP_TITLE_W, SP_TITLE_H, g_tablatrans);

    // clear game area

    printScoreBoardVs1(&board1, &board2);
    printScoreBoardVs2(&board1, &board2);
}

//////////////////////////////////////////////////////////////////
//  initVsLevel
//  Initializes the level for vs mode
//
//  Input: void
//
//  Returns: void
//
void initVsLevel()
{
    clearScreen(BG_COLOR);
    // Init board
    initBoard(&board1, 53, 80, 18, 29, 47, 180);
    initBoard(&board2, 3, 80, 18, 19, 29, 180);
    createVirus(&board1, level);
    createVirus(&board2, level);
    initPillQueue();
    pillQueueIndex1 = 0;
    pillQueueIndex2 = 0;
    printScreenVs();
    printBoard(&board1);
    printBoard(&board2);
    capsules1 = 0;
    speedDelta1 = 0;
    capsules2 = 0;
    speedDelta2 = 0;
    currentSpeed1 = cursorSpeedPerLevel[level];
    currentSpeed2 = cursorSpeedPerLevel[level];
    keys1.fireCooling = 0;
    keys2.fireCooling = 0;
}

//////////////////////////////////////////////////////////////////
//  initVsLevel
//  Initializes the level for vs mode
//
//  Input: void
//
//  Returns: void
//
void newVsLevel()
{
    level++;
    initVsLevel();
    activeCursor1.activePill = NO;
    activeCursor2.activePill = NO;
    playerLastUpdate = i_time;
    board1.virList.lastUpdate = i_time;
    board2.virList.lastUpdate = i_time;
    initCursor(&nextCursor1, &pillQueueIndex1);
    initCursor(&nextCursor2, &pillQueueIndex2);
}

//////////////////////////////////////////////////////////////////
//  initVsGame
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//
void initVsGame()
{

    // Initial values
    level = 1;
    initVsLevel();
}

//////////////////////////////////////////////////////////////////
// playVsGame:
// 	Main loop of the game
//
// 	Input: void
//  Returns: void
//
void playVsGame(TKeys *keys1, TKeys *keys2)
{
    u8 abortGame = 0;
    u8 player1Wins = 0;
    u8 player2Wins = 0;

    do
    {
        playerLastUpdate = i_time;

        board1.virList.lastUpdate = i_time;
        initCursor(&activeCursor1, &pillQueueIndex1);
        activeCursor1.activePill = YES;
        printCursor(&board1, &activeCursor1, CURRENT); // 1 = current coordinates
        initCursor(&nextCursor1, &pillQueueIndex1);
        printNextCursor(&nextCursor1, PLAYER1_VS);

        board2.virList.lastUpdate = i_time;
        initCursor(&activeCursor2, &pillQueueIndex2);
        activeCursor2.activePill = YES;
        printCursor(&board2, &activeCursor2, CURRENT); // 1 = current coordinates
        initCursor(&nextCursor2, &pillQueueIndex2);
        printNextCursor(&nextCursor2, PLAYER2_VS);
        // Loop forever

        do
        {

            //Abort Game
            if (cpct_isKeyPressed(keys1->abort))
            {
                abortGame = showMessage("Abort the game??", YES);
            }
            // Pause Game
            if (cpct_isKeyPressed(keys1->pause))
            {
                showMessage("Game Paused", NO);
            }
            // Update active Cursor
            if ((i_time - activeCursor1.lastUpdate) > currentSpeed1)
            {
                // If there is NO active pill
                if (activeCursor1.activePill == NO)
                {
                    //Updates falling speed if necessary
                    updateFallingSpeed(&capsules1, &speedDelta1, &currentSpeed1);
                    cpct_memcpy(&activeCursor1, &nextCursor1, sizeof(TCursor)); // Copy next pill over active cursor
                    initCursor(&nextCursor1, &pillQueueIndex1);
                    printNextCursor(&nextCursor1, PLAYER1_VS);
                    printCursor(&board1, &activeCursor1, CURRENT);
                    activeCursor1.activePill = YES;
                }
                else if (checkCollisionDown(&board1, &activeCursor1))
                {                                                  // If there is an active pill, check if the pill has collided
                    cursorHitVs(&board1, &activeCursor1, &board2); // Manage collision
                                                                   // Check if are there any virus left
                    if (board1.virList.count == 0)
                    {
                        sprintf(AUX_TXT, "Player 1 Wins. Level %d Cleared!!", level);
                        showMessage(AUX_TXT, 0);
                        newVsLevel();
                    }
                }
                else
                {
                    activeCursor1.y++;
                    activeCursor1.moved = 1;
                }
            }
            if ((i_time - activeCursor2.lastUpdate) > currentSpeed2)
            {
                if (activeCursor2.activePill == NO)
                {
                    //Updates falling speed if necessary
                    updateFallingSpeed(&capsules2, &speedDelta2, &currentSpeed2);
                    cpct_memcpy(&activeCursor2, &nextCursor2, sizeof(TCursor)); // Copy next piece over active
                    initCursor(&nextCursor2, &pillQueueIndex2);
                    printNextCursor(&nextCursor2, PLAYER2_VS);
                    printCursor(&board2, &activeCursor2, CURRENT);
                    activeCursor2.activePill = YES;
                }
                else if (checkCollisionDown(&board2, &activeCursor2))
                {                                                  // If there is an active pill, check if the pill has collided
                    cursorHitVs(&board2, &activeCursor2, &board1); // Manage collision
                                                                   // Check if are there any virus left
                    if (board2.virList.count == 0)
                    {
                        sprintf(AUX_TXT, "Player 2 Wins. Level %d Cleared!!", level);
                        showMessage(AUX_TXT, 0);
                        newVsLevel();
                    }
                }
                else
                {
                    activeCursor2.y++;
                    activeCursor2.moved = 1;
                }
            }
            //Update player
            if ((i_time - playerLastUpdate) > PLAYER_SPEED)
            {
                updatePlayer(&activeCursor1, &board1, &board2, keys1, VS);
                updatePlayer(&activeCursor2, &board2, &board1, keys2, VS);
                playerLastUpdate = i_time;
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

            //Animate Virus
            if ((i_time - board1.virList.lastUpdate) > BACT_ANIM_SPEED)
            {
                //cpct_waitVSYNC();
                animateVirusList(&board1);
                animateVirusList(&board2);
                board1.virList.lastUpdate = i_time;
            }

        } while ((activeCursor1.alive == YES) && (activeCursor2.alive == YES) && (abortGame == NO));
        
        sprintf(AUX_TXT, "Good job Player %d!!", activeCursor2.alive + 1);
        showMessage(AUX_TXT, 0);
        
        if (activeCursor1.alive == YES)
            player1Wins++;
        else
            player2Wins++;
        
        newVsLevel();
         
    } while ((player1Wins < 3) && (player2Wins < 3) && (abortGame == NO));

    if (abortGame)
        showMessage("Game terminated", 0);
    else
    {
        sprintf(AUX_TXT, "Player %d Wins the match!!", (player2Wins == 3) + 1);
        showMessage(AUX_TXT, 0);
    }
    checkScoreInHallOfFame(board1.score, level, VS, keys1, "Good job Player1.Enter your name");
    checkScoreInHallOfFame(board2.score, level, VS, keys2, "Well done Player2.Enter your name");
}