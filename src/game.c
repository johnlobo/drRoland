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
#include "sprites/drroland02.h"
#include "sprites/arm01.h"
#include "sprites/arm02.h"
#include "sprites/title.h"
#include "sprites/viruses-big.h"
#include "sprites/drroland01.h"
#include "sprites/letterMarker.h"
#include "sprites/letterMarker2.h"
#include "sprites/okSign.h"
#include "sprites/crown.h"

#define YPOS 44


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
u16 currentDelay1;
u8 capsules2;
u8 speedDelta2;
u16 currentDelay2;
u8 bigVirusOnScreen[3];
u8 player1Wins;
u8 player2Wins;

u8 *const sprites[3][9] = {
    {emptyCell, sp_upPills_0, sp_downPills_0, sp_leftPills_0,
     sp_rightPills_0, sp_blocks_0, sp_virus_0, sp_virus_1, sp_virus_2},
    {emptyCell, sp_upPills_1, sp_downPills_1, sp_leftPills_1,
     sp_rightPills_1, sp_blocks_1, sp_virus_3, sp_virus_4, sp_virus_5},
    {emptyCell, sp_upPills_2, sp_downPills_2, sp_leftPills_2,
     sp_rightPills_2, sp_blocks_2, sp_virus_6, sp_virus_7, sp_virus_8}};
u8 *const spritesBigVirus[9] = {sp_viruses_big_0, sp_viruses_big_1, sp_viruses_big_2};

u16 const cursorSpeedPerLevel[20] = {150, 140, 140, 130, 130, 120, 120, 120, 110, 110, 110, 100, 100, 100, 90, 90, 80, 80, 70, 70};

// Inital coord: 61,81
// Final coord: 40, 51
u8 const throwCoordsX[5] = {57, 53, 49, 45, 40};
u8 const throwCoordsY[5] = {70, 50, 30, 40, 51};


// ********************************************************************************
/// <summary>
/// printBigVirus
/// Input: void
/// Returns: void
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
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
        // Print number
        pvmem = cpct_getScreenPtr(SCR_VMEM, 15 - (14 * (n==1)) + (SP_VIRUSES_BIG_1_W * (n == 1)), 111 + 
                    (SP_VIRUSES_BIG_1_H * n));
        cpct_drawSolidBox(pvmem, 0, 4, 8);
        if (b->virList.colorCount[n]>0){
            sprintf (auxTxt,"%d",b->virList.colorCount[n]);
            drawText(auxTxt, 15 - (14 * (n==1)) + (SP_VIRUSES_BIG_1_W * (n == 1)), 111 + 
                (SP_VIRUSES_BIG_1_H * n), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
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
void printBackground(){
	u8 i, j;
	u8* pvmem;
	
	cpct_waitVSYNC(); // Sync with the raster to avoid flickering
	for (j = 0; j < 12; j++)
    {
        for (i = 0; i < 20; i++)
        {
            if ((i % 2) == (j % 2))
            {
                pvmem = cpct_getScreenPtr(SCR_VMEM, i * 4, j * 16);
                cpct_drawSolidBox(pvmem, cpct_px2byteM0(2, 2), 4, 16);
            }
        }
    }
	// print title
    cpct_waitVSYNC(); // Sync with the raster to avoid flickering
    pvmem = cpct_getScreenPtr(SCR_VMEM, 30, 7);
    cpct_drawSpriteMaskedAlignedTable(sp_title, pvmem, SP_TITLE_W, SP_TITLE_H, g_tablatrans);
}
	

// ********************************************************************************
/// <summary>
/// printScreenSingle
/// Draws "DrRoland" on the screen
/// Input:      Level
/// Returns:    void.
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printScreenSingle()
{
	u8* pvmem;
	
    clearScreen(BG_COLOR); // Clear de Screen BGCOLOR=Black
    cpct_waitVSYNC();      // Sync with the raster to avoid flickering
    // Draw background
    printBackground();
    
    // print scoreboards
    drawScoreBoard1(&board1);
    drawScoreBoard2(&board1);
	
	// print Roland
    pvmem = cpct_getScreenPtr(SCR_VMEM, 64, 86);
    cpct_drawSprite(sp_drroland02, pvmem, SP_DRROLAND02_W, SP_DRROLAND02_H);
    
	// Big Virus Container
    drawWindow(3, 95, 21, 80, 15, 0);
}

// ********************************************************************************
/// <summary>
/// animateThrow
/// Input: void
/// Returns: void
/// </summary>
/// <param name="cur"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void animateThrow(TCursor *cur)
{
    u8 *pvmem;
    u8 n;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm02, pvmem, SP_ARM02_W, SP_ARM02_H);
    for (n = 0; n < 5; n++)
    {
        pvmem = cpct_getScreenPtr(SCR_VMEM, throwCoordsX[n], throwCoordsY[n]);
        //cpc_GetSp((u8 *)screenBuffer, 7, 6, pvmem); // Capture screen background
		cpct_getScreenToSprite(pvmem, (u8*) &screenBuffer, 6, 7); // Capture screen background
        printCursor2(cur, throwCoordsX[n], throwCoordsY[n]);
        //delay(25);
		cpct_waitHalts(25);
        cpct_drawSprite(&screenBuffer, pvmem, 6, 7); // Screen background restore
    }
    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm01, pvmem, SP_ARM01_W, SP_ARM01_H);
}

// ********************************************************************************
/// <summary>
/// printArm01
/// Input: void
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
/// cursorHitSingle
/// Input: void
/// Returns: void
/// </summary>
/// <param name="b"></param>
/// <param name="cur"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void cursorHitSingle(TBoard *b, TCursor *cur)
{
    b->content[cur->y][cur->x] = cur->content[0];
    b->color[cur->y][cur->x] = cur->color[0];
    // Add position and neg position to change direction vertical & horizaontal
    b->content[cur->y + cur->position][cur->x + (!cur->position)] = cur->content[1];
    b->color[cur->y + cur->position][cur->x + (!cur->position)] = cur->color[1];

    // Clear matches until gravity stops
	while (clearMatches(b)) {
		if (b->applyingGravity == NO) {
			startApplyGravity(b);
		}
	}
    

    cur->activePill = NO;
    if (cur->y == 0)
    {
        cur->alive = NO;
    }

}

//Forward declaration of "cursorHitVs" for code clarity
void cursorHitVs(TBoard *b, TCursor *cur, TBoard *foe);

// ********************************************************************************
/// <summary>
/// updatePlayer
/// Updates cursor position based on player's keypresses
/// Input: cursor, board & keys
/// Returns: void && cursor updated
/// </summary>
/// <param name="cur"></param>
/// <param name="b"></param>
/// <param name="foe"></param>
/// <param name="k"></param>
/// <param name="typeOfGame"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void updatePlayer(TCursor *cur, TBoard *b, TBoard *foe, TKeys *k, u8 typeOfGame)
{
    u8 aux;

    // Check downwards movement
    if (cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down))
    {
        if (checkCollisionDown(b, cur) == YES)
        {
            cpct_akp_SFXPlay (1, 15, 60, 0, 0, AY_CHANNEL_C);
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
            if ((cur->position == HORIZONTAL) && (cur->y > 0) && (b->content[cur->y - 1][cur->x] == 0))
            {
                cur->y--;
                cur->content[0] = 1;
                cur->content[1] = 2;
                cur->moved = YES;
                cur->position = !cur->position; // Check if there is enough space to rotate VER->HOR
                cpct_akp_SFXPlay (1, 15, 60, 0, 0, AY_CHANNEL_C);
            }
            else if ((cur->position == VERTICAL) && ((((cur->x < 7) && (b->content[cur->y + 1][cur->x + 1] == 0)) ||
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
               	cpct_akp_SFXPlay (1, 15, 60, 0, 0, AY_CHANNEL_C);

            }
            k->fireCooling = FIRE_COOL_TIME;
        }
    }
}


// ********************************************************************************
/// <summary>
/// printSpecialMarker
/// Input: void
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
/// Input: void
/// Returns: void
/// </summary>
/// <param name="result"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void updateText(u8 *result)
{
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13, (YPOS + 90));
    cpct_drawSolidBox(pvmem, cpct_px2byteM0(0, 0), 40, 18);
    drawText(result, 13, (YPOS + 90), COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);
}

// ********************************************************************************
/// <summary>
/// updateTopScoreMarker
/// Input: void
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
/// Input: void
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


    txt[0] = 'A';
    txt[1] = '\0';
    drawWindow(9, YPOS, 64, 110, 15, 0);
    // Title
    drawText(title, 13, YPOS + 6, COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);
    // DrRonald
    pvmem = cpct_getScreenPtr(SCR_VMEM, 57, YPOS + 25);
    cpct_drawSpriteMaskedAlignedTable(sp_drroland01, pvmem, SP_DRROLAND01_W, SP_DRROLAND01_H, g_tablatrans);
    pvmem = cpct_getScreenPtr(SCR_VMEM, 53, YPOS + 36);
    cpct_drawSpriteMaskedAlignedTable(sp_okSign, pvmem, SP_OKSIGN_W, SP_OKSIGN_H, g_tablatrans);

    for (i = 0; i < 26; i++)
    {
        drawText(txt, 13 + ((i % 13) * 3), (YPOS + 39) + ((i / 13) * 15), COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        txt[0] = 66 + i;
    }
    drawText("SPACE", 13, YPOS + 69, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("DEL", 30, YPOS + 69, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("END", 45, YPOS + 69, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);

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
            else if (y==1)
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
/// Input: void
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
/// Input:
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
/// initSingleLevel
/// Initializes the game
/// Input: void
/// Returns: void
/// </summary>
/// <param name="resetScore"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void initSingleLevel(u8 resetScore)
{
    clearScreen(BG_COLOR);
	// init bigvirusOnScreen flag array
	cpct_memset(&bigVirusOnScreen, 0, 3);
    // Init board
    initBoard(&board1, PLAYER1, 30, 76, 16, 19, 74, 179);
    if (resetScore)
        board1.score = 0;
    createVirus(&board1, level);
    initPillQueue();
    pillQueueIndex1 = 0;
    printScreenSingle();
    printBigVirus(&board1);
    drawBoard(&board1);
    // Clean the matches appeared after creating all the viruses
	clearMatches(&board1);
    capsules1 = 0;
    speedDelta1 = 0;
    currentDelay1 = cursorSpeedPerLevel[level];
    keys1.fireCooling = 0;
    playerLastUpdate = i_time;
    board1.virList.lastUpdate = i_time;
    initCursor(&activeCursor1, &pillQueueIndex1);
    activeCursor1.activePill = YES;
    initCursor(&nextCursor1, &pillQueueIndex1);
    printNextCursor(&nextCursor1, PLAYER1);
}

// ********************************************************************************
/// <summary>
/// initSingleGame
/// Initializes the game
/// Input: void
/// Returns: void
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void initSingleGame()
{

    // Initial values
    level = 1;
    initSingleLevel(YES);
}

// ********************************************************************************
/// <summary>
/// updateFallingSpeed
/// Main loop of the game
/// Input: void
/// Returns: void
/// </summary>
/// <param name="caps"></param>
/// <param name="speedD"></param>
/// <param name="curDelay"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void updateFallingSpeed(u8 *caps, u8 *speedD, u16 *curDelay)
{
    (*caps)++;
    //Update cursor speed
    if ((*curDelay > 0) && (*speedD < 25) && ((*caps % CAPSULES_PER_SPEED) == 0))
    {
        (*speedD)++;
        if (*curDelay > (*speedD * CAPSULE_STEP))
        {
            (*curDelay) -= (*speedD * CAPSULE_STEP);
        }
        else
        {
            *curDelay = 0;
        }
    }
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
void throwNextPill(TCursor* activeCursor, TCursor* nextCursor, u8* pillQueueIndex, TBoard* b, u8 type) {
	cpct_memcpy(activeCursor, nextCursor, sizeof(TCursor));
	animateThrow(nextCursor);
	initCursor(nextCursor, pillQueueIndex);
	if (type == PLAYER1)
		printArm01();
	printNextCursor(nextCursor, type);
	printCursor(b, activeCursor, CURRENT);
	activeCursor->activePill = YES;
}

// ********************************************************************************
/// <summary>
/// playSingleGame
/// Main loop of the game
/// Input: void
/// Returns: void
/// </summary>
/// <param name="keys"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void playSingleGame(TKeys *keys)
{
    u8 abortGame = 0;

	//printCursor(&board1, &activeCursor1, CURRENT);
	printNextCursor(&activeCursor1, PLAYER1);
	throwNextPill(&activeCursor1, &nextCursor1, &pillQueueIndex1, &board1, PLAYER1);

    // Loop forever
    do
    {
		//If there is some match in the list of animation... animate it
		if (animateMatchList.count) {
			animateMatch();
		}
		//If the flag for applying gravity is set, applygravity
		if(board1.applyingGravity)
		{
			applyGravity(&board1);
			printBigVirus(&board1);
		}

		//Abort Game
        if (cpct_isKeyPressed(keys->abort))
        {
            abortGame = showMessage("ABORT THE GAME??", YES);
        }
        // Pause Game
        if (cpct_isKeyPressed(keys->pause))
        {
            showMessage("GAME PAUSED", NO);
        }
        // Update active Cursor
        if ((i_time - activeCursor1.lastUpdate) > currentDelay1)
        {
            if (activeCursor1.activePill == NO)
            {
                //Updates falling speed if necessary
                updateFallingSpeed(&capsules1, &speedDelta1, &currentDelay1);
               
				// Throw next Pill
				throwNextPill(&activeCursor1, &nextCursor1, &pillQueueIndex1, &board1, PLAYER1);
            }
            else if (checkCollisionDown(&board1, &activeCursor1))
            {
				cpct_akp_SFXPlay (1, 15, 60, 0, 0, AY_CHANNEL_C);
                cursorHitSingle(&board1, &activeCursor1);
            }
            else
            {
                activeCursor1.y++;
                activeCursor1.moved = 1;
            }
        }
        //Update player
        if (((i_time - playerLastUpdate) > PLAYER_SPEED) && (activeCursor1.activePill))
        {
            updatePlayer(&activeCursor1, &board1, NULL, keys, SINGLE);
            playerLastUpdate = i_time;
        }
        // Draw active cursor
        if (activeCursor1.activePill && activeCursor1.moved)
        {
            drawActiveCursor(&board1, &activeCursor1);
        }
		// If no virus left, level is done
        if (board1.virList.count == 0)
        {
            sprintf(auxTxt, "GOOD JOB!! LEVEL %d CLEARED", level);
            showMessage(auxTxt, 0);
            if (level < 20)
            {
                level++;
                initSingleLevel(NO);
                activeCursor1.activePill = NO;
                playerLastUpdate = i_time;
                board1.virList.lastUpdate = i_time;
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
        if ((i_time - board1.virList.lastUpdate) > BACT_ANIM_SPEED)
        {
            //cpct_waitVSYNC();
            animateVirusList(&board1);
            board1.virList.lastUpdate = i_time;
        }

    } while ((activeCursor1.alive == YES) && (abortGame == 0));

    if (abortGame)
        showMessage("GAME TERMINATED", 0);
    else
        showMessage("YOU ARE DEAD!!", 0);

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
/// Input: void
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
/// animateAttack
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void animateAttack(TBoard *b, u8 x, u8 y)
{
    u8 i;

    for (i = 0; i < 3; i++)
    {
        drawHitSpriteXY(x, y, i);
        //delay(60);
		cpct_waitHalts(60);
        deleteCell(b, x, y);
    }
}

// ********************************************************************************
/// <summary>
/// attackFoe
/// Input: void
/// Returns: void
/// </summary>
/// <param name="b"></param>
/// <param name="v"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
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
        drawVirusList(b);
        drawSingleVirusCount(b);
        v--;
    } while (v > 0);
}

// ********************************************************************************
/// <summary>
/// cursorHitVs
/// Input: void
/// Returns: void
/// </summary>
/// <param name="b"></param>
/// <param name="cur"></param>
/// <param name="foe"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
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

// ********************************************************************************
/// <summary>
/// printScreenVs
/// Draws the game area
/// Input:      Level
/// Returns:    void.
/// </summary>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void printScreenVs()
{
    clearScreen(BG_COLOR); // Clear de Screen BGCOLOR=Black
    // Draw background
	printBackground();

    // print scoreboards
    drawScoreBoardVs1(&board1, &board2);
    drawScoreBoardVs2(&board1, &board2);

    printCrowns();
}

// ********************************************************************************
/// <summary>
/// initVsLevel
/// Initializes the level for vs mode
/// Input: void
/// Returns: void
/// </summary>
/// <param name="resetScore"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void initVsLevel(u8 resetScore)
{
    clearScreen(BG_COLOR);
    // Init board
    initBoard(&board1, PLAYER1, 53, 80, 18, 19, 47, 180);
    initBoard(&board2, PLAYER2, 3, 80, 18, 29, 29, 180);
    if (resetScore)
    {
        board1.score = 0;
        board2.score = 0;
    }
    createVirus(&board1, level);
    createVirus(&board2, level);
    initPillQueue();
    pillQueueIndex1 = 0;
    pillQueueIndex2 = 0;
    printScreenVs();
    drawBoard(&board1);
    drawBoard(&board2);
    // Clean the matches appeared after creating all the viruses
	clearMatches(&board1);
	clearMatches(&board2);

    capsules1 = 0;
    speedDelta1 = 0;
    capsules2 = 0;
    speedDelta2 = 0;
    currentDelay1 = cursorSpeedPerLevel[level];
    currentDelay2 = cursorSpeedPerLevel[level];
    keys1.fireCooling = 0;
    keys2.fireCooling = 0;

    activeCursor1.activePill = NO;
    activeCursor2.activePill = NO;
    playerLastUpdate = i_time;
    board1.virList.lastUpdate = i_time;
    board2.virList.lastUpdate = i_time;
    initCursor(&nextCursor1, &pillQueueIndex1);
    initCursor(&nextCursor2, &pillQueueIndex2);
}

// ********************************************************************************
/// <summary>
/// initVsGame
/// Initializes the game in vs mode
/// Input: void
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
    initVsLevel(YES);
}

// ********************************************************************************
/// <summary>
/// playVsGame:
/// Main loop of the game
/// Input: void
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

    do
    {
        // Loop forever

        do
        {
			//If there is some match in the list of animation... animate it
			if (animateMatchList.count) {
				animateMatch();
			}
			//If the flag for applying gravity is set, applygravity
			if (board1.applyingGravity)
			{
				applyGravity(&board1);
				printBigVirus(&board1);
			}

            //Abort Game
            if (cpct_isKeyPressed(keys1->abort))
            {
                abortGame = showMessage("ABORT THE GAME??", YES);
            }
            // Pause Game
            if (cpct_isKeyPressed(keys1->pause))
            {
                showMessage("GAME PAUSED", NO);
            }
            // Update active Cursor
            if ((i_time - activeCursor1.lastUpdate) > currentDelay1)
            {
                // If there is NO active pill
                if (activeCursor1.activePill == NO)
                {
                    //Updates falling speed if necessary
                    updateFallingSpeed(&capsules1, &speedDelta1, &currentDelay1);

					// Throw next Pill
					throwNextPill(&activeCursor1, &nextCursor1, &pillQueueIndex1, &board1, PLAYER1_VS);
                }
                else if (checkCollisionDown(&board1, &activeCursor1))
                {                                                  
					cpct_akp_SFXPlay (2, 15, 60, 1, 0, AY_CHANNEL_C);
                    cursorHitVs(&board1, &activeCursor1, &board2);                                                                    
                }
                else
                {
                    activeCursor1.y++;
                    activeCursor1.moved = 1;
                }
            }
            if ((i_time - activeCursor2.lastUpdate) > currentDelay2)
            {
                if (activeCursor2.activePill == NO)
                {
                    //Updates falling speed if necessary
                    updateFallingSpeed(&capsules2, &speedDelta2, &currentDelay2);

					// Throw next Pill
					throwNextPill(&activeCursor1, &nextCursor1, &pillQueueIndex1, &board1, PLAYER2_VS);
                }
                else if (checkCollisionDown(&board2, &activeCursor2))
                {                               
					cpct_akp_SFXPlay (2, 15, 60, 1, 0, AY_CHANNEL_C);
                    cursorHitVs(&board2, &activeCursor2, &board1); 
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
            if (board1.virList.count == 0)
            {
                sprintf(auxTxt, "PLAYER 1 WINS LEVEL %d", level);
                showMessage(auxTxt, MESSAGE);
                player1Wins++;
                if (player1Wins<3){
                    level++;
                    initVsLevel(NO);    
                }
                
            }
            else if (board2.virList.count == 0)
            {
                sprintf(auxTxt, "PLAYER 2 WINS LEVEL %d", level);
                showMessage(auxTxt, MESSAGE);
                player2Wins++;
                if (player2Wins<3){
                    level++;
                    initVsLevel(NO);    
                }
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

        if (abortGame == NO)
        {
            sprintf(auxTxt, "PLAYER %d LOSES LEVEL %d", 1 +  activeCursor2.alive, level);
            showMessage(auxTxt, 0);

            if (activeCursor1.alive == YES)
                player1Wins++;
            else
                player2Wins++;

            if ((player1Wins < 3) && (player2Wins < 3))
            {
                level++;
                initVsLevel(NO);
            }
            else
                printCrowns();
        }

    } while ((player1Wins < 3) && (player2Wins < 3) && (abortGame == NO));

    if (abortGame)
        showMessage("GAME TERMINATED", 0);
    else
    {
        sprintf(auxTxt, "PLAYER %d WINS THE MATCH!!", (player2Wins == 3) + 1);
        showMessage(auxTxt, 0);
    }
    checkScoreInHallOfFame(board1.score, level, VS, keys1, "PLAYER1 ENTER YOUR NAME");
    checkScoreInHallOfFame(board2.score, level, VS, keys2, "PLAYER2 ENTER YOUR NAME");
}