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
#include <stdio.h> //because sprintf
#include "../defines.h"
#include "board.h"
#include "../game.h"
#include "../util/util.h"
#include "../text/text.h"
#include "../sprites/hit.h"
#include "../sprites/downPills.h"
#include "match.h"

u8 *const hitSprite[3] = {sp_hit_0, sp_hit_1, sp_hit_2};
TMatch match;

u8 const maximumRow[21] = {0, 10, 9, 8, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 4, 4, 3};
u16 const virusPerLevel[21] = {0, 4, 8, 6, 10, 6, 12, 8, 14, 8, 16, 10, 18, 12, 20, 14, 22, 16, 24, 18, 26};
u16 const pointsPerKill[7] = {0, 200, 600, 1400, 3000, 6200, 12600};

u8 pillQueueIndex1;
u8 pillQueueIndex2;
u8 partialCount;
TMatchList animateMatchList;

// Prototype of clearMatches function to be used by addViruses procedure
u8 clearMatches(TBoard *b);

//////////////////////////////////////////////////////////////////////////
// Virus section
//////////////////////////////////////////////////////////////////////////

// ********************************************************************************
/// <summary>
/// initVirus
/// Initialize a Virus
/// Input:      A Virus
/// Returns:    void.
/// </summary>
/// <param name="vir"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void initVirus(TVirus *vir)
{
	vir->x = 255;
	vir->y = 255;
	vir->color = 0;
	vir->type = 0;
}

// ********************************************************************************
/// <summary>
/// initvirusList
/// Initialize a list of Virus
/// Input:      A list of Virus
/// Returns:    void.
/// </summary>
/// <param name="virlist"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void initvirusList(TVirusList *virlist)
{
	//u8 i;
	//
	//for (i = 0; i < 20; i++)
	//{
	//	initVirus(&virlist->virusList[i]);
	//}
	//virlist->count = 0;
	//virlist->step = 0;
	//virlist->lastUpdate = i_time;
	//virlist->colorCount[0] = 0;
	//virlist->colorCount[1] = 0;
	//virlist->colorCount[2] = 0;

	cpct_memset(virlist, 0, sizeof(TVirusList));
	virlist->lastUpdate = i_time;
}

// ********************************************************************************
/// <summary>
/// addVirus
/// adds a Virus to a Virus list
/// Input:      A list of Virus, virria position, color and type
/// Returns:    void.
/// </summary>
/// <param name="virlist"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="type"></param>
/// <param name="color"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void addVirus(TVirusList *virlist, u8 x, u8 y, u8 type, u8 color)
{
	u8 iter = 0;
	if (virlist->count < 20)
	{
		do
		{
			if (virlist->virusList[iter].type != 0)
			{
				iter++;
			}
			else
			{
				break;
			}
		} while (iter < 20);

		virlist->virusList[iter].color = color;
		virlist->virusList[iter].type = type;
		virlist->virusList[iter].x = x;
		virlist->virusList[iter].y = y;
		virlist->count++;
		virlist->colorCount[color]++;
	}
}

// ********************************************************************************
/// <summary>
/// deleteVirus
/// deletes a Virus from a Virus list
/// Input:      A list of Virus and the index of the Virus to remove
/// Returns:    void.
/// </summary>
/// <param name="virlist"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void deleteVirus(TVirusList *virlist, u8 x, u8 y)
{
	u8 i;

	i = 0;
	while (i < MAX_VIR_LIST)
	{
		if ((virlist->virusList[i].x == x) && (virlist->virusList[i].y == y))
		{
			break;
		}
		else
		{
			i++;
		}
	}
	if (i < MAX_VIR_LIST)
	{
		virlist->virusList[i].x = 255;
		virlist->virusList[i].y = 255;
		virlist->virusList[i].type = 0;
		virlist->colorCount[virlist->virusList[i].color]--;
		virlist->virusList[i].color = 255;
		virlist->count--;
	}
}


// ********************************************************************************
/// <summary>
/// drawOneVirus
/// Prints one Virus in the board
/// </summary>
/// <param name="b">Board</param>
/// <param name="i"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawOneVirus(TBoard *b, u8 i)
{
	u8 *pvmem;
	TVirus *vir;
	u8 step;

	vir = &b->virList.virusList[i];
	step = b->virList.step;
	// claculate screen adrees for the Virus
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
							  b->originX + (vir->x * CELL_WIDTH),
							  b->originY + (vir->y * CELL_HEIGHT)
	);
	// Print Virus
	//cpct_drawSpriteBlended(
	//	pvmem, CELL_HEIGHT, CELL_WIDTH,
	//	sprites[vir->color][vir->type + (step % 3)]);
	cpct_drawSprite(
		sprites[vir->color][vir->type + (step % 3)],
		pvmem,
		CELL_WIDTH,
		CELL_HEIGHT);
}

// ********************************************************************************
/// <summary>
/// printvirusList
/// Prints all the Virus in a board
/// Input:      A list of Virus and the board
/// Returns:    void.
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawVirusList(TBoard *b)
{
	u8 i;

	for (i = 0; i < 20; i++)
	{
		if (b->virList.virusList[i].type)
		{
			drawOneVirus(b, i);
		}
	}
}

// ********************************************************************************
/// <summary>
/// animatevirusList
/// Animates all the Virus in a board
/// Input:      A list of Virus and the board
/// Returns:    void.
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void animateVirusList(TBoard *b)
{
	//drawVirusList(b);
	b->virList.step++;
	drawVirusList(b);
}

// ********************************************************************************
/// <summary>
/// createtVirus
/// Set the Virus in the board depending on the level
/// Input:      Level
/// Returns:    void.
/// </summary>
/// <param name="b"></param>
/// <param name="l"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void createVirus(TBoard *b, u8 l)
{
	u8 count = 0;
	u8 x, y, color;

	count = 0;

	do
	{
		x = (cpct_rand8() % 8);
		y = (cpct_rand8() % (16 - maximumRow[l])) + maximumRow[l];
		color = (cpct_rand8() % 3); // creates a random color

		if (b->content[y][x] == 0)
		{
			b->content[y][x] = 6;				   // 6 is Virus order in the content array;
			b->color[y][x] = color;				   // Assign a random color
			addVirus(&b->virList, x, y, 6, color); // add Virus to de list of baterias
			count++;
		}
	} while (count < virusPerLevel[l]); //Enemies are 4 times the level plus 4
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Queue section
/////////////////////////////////////////////////////////////////////////////////////////////////

// ********************************************************************************
/// <summary>
/// initPillQueue
/// Input:      Level
/// Returns:    void.
/// </summary>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void initPillQueue()
{
	u8 i;

	for (i = 0; i < 128; i++)
	{
		pillQueue[i].color[0] = (cpct_rand8() % 3);
		pillQueue[i].color[1] = (cpct_rand8() % 3);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Board section
/////////////////////////////////////////////////////////////////////////////////////////////////

// ********************************************************************************
/// <summary>
/// initBoard
/// initializes the board
/// Input: void
/// Returns: void
/// </summary>
/// <param name="b">Board to be initialized</param>
/// <param name="p">Player that owns the board</param>
/// <param name="x">x pos where the board should be drawed</param>
/// <param name="y">y pos where the board should be drawed</param>
/// <param name="scX">x where the score should be drawed</param>
/// <param name="scY">y where the score should be drawed</param>
/// <param name="viX">x where the virus should be drawed</param>
/// <param name="viY">y where the virus should be drawed</param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void initBoard(TBoard *b, u8 p, u8 x, u8 y, u8 scX, u8 scY, u8 viX, u8 viY)
{
	u8 i, j;

	b->player = p;
	b->originX = x;
	b->originY = y;
	b->scoreX = scX;
	b->scoreY = scY;
	b->virusX = viX;
	b->virusY = viY;
	for (j = 0; j < BOARD_HEIGHT; j++)
	{
		for (i = 0; i < BOARD_WIDTH; i++)
		{
			b->color[j][i] = 255;
			b->content[j][i] = 0;
		}
	}
	b->applyingGravity = NO;
	b->throwing = NO;
	initvirusList(&b->virList);
	initMatchList(&animateMatchList);
}


// ********************************************************************************
/// <summary>
/// drawBoardCells
/// prints the content of the cells of the board on the screen
/// Input: void
/// Returns: void
/// </summary>
/// <param name="b">Board to be printed</param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawBoardCells(TBoard *b){
	u8 i, j;
	u8 *pvmem;
	
	for (j = 0; j < BOARD_HEIGHT; j++)
	{
		for (i = 0; i < BOARD_WIDTH; i++)
		{
			pvmem = cpct_getScreenPtr(CPCT_VMEM_START, b->originX + (i * CELL_WIDTH), b->originY + (j * CELL_HEIGHT));
			if (b->content[j][i] != 0)
			{
				cpct_drawSprite(
					sprites[b->color[j][i]][b->content[j][i]],
					pvmem,
					CELL_WIDTH,
					CELL_HEIGHT);
			} else
				cpct_drawSprite(emptyCell, pvmem, CELL_WIDTH, CELL_HEIGHT);
		}
	}	
}

// ********************************************************************************
/// <summary>
/// drawBoard
/// prints the board on the screen
/// Input: void
/// Returns: void
/// </summary>
/// <param name="b">Board to be printed</param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawBoard(TBoard *b)
{
	// Clear board background
	drawWindow(b->originX - 1, b->originY - 5, 28, 119, 15, BG_COLOR);
	drawBottleNeck(b->originX - 1 + 4, b->originY - 5 - 29, 18, 32, 15, BG_COLOR);
	drawBoardCells(b);
	
}

// ********************************************************************************
/// <summary>
/// clearGameArea
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void clearGameArea(TBoard *b)
{
	u8 *pvmem;
	pvmem = cpct_getScreenPtr(SCR_VMEM, b->originX - SP_DOWNPILLS_0_W, b->originY - SP_DOWNPILLS_0_H);
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(BG_COLOR, BG_COLOR), 10 * SP_DOWNPILLS_0_W, 10 * (SP_DOWNPILLS_0_H + 1));
	pvmem = cpct_getScreenPtr(SCR_VMEM, b->originX - SP_DOWNPILLS_0_W, b->originY + 9 * (SP_DOWNPILLS_0_H + 1));
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(BG_COLOR, BG_COLOR), 10 * SP_DOWNPILLS_0_W, 8 * (SP_DOWNPILLS_0_H + 1));
}

// ********************************************************************************
/// <summary>
/// drawSingleScore
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawSingleScore(TBoard *b)
{
	u8 *pvmem;

	sprintf(auxTxt, "%05d", b->score);
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, b->scoreX, b->scoreY);
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(14, 14), strLength(auxTxt) * 2, 9);
	drawText(auxTxt, b->scoreX, b->scoreY, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
}

// ********************************************************************************
/// <summary>
/// drawScoreBoard1
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawScoreBoard1(TBoard *b)
{
	drawWindow(1, 3, 30, 29, 15, BG_COLOR);
	//Top
	drawText("TOP", 3, 9, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(auxTxt, "%06d", hallOfFameSingle.topScore);
	drawText(auxTxt, 14, 9, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	//Score
	drawText("SCORE", 3, 19, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	drawSingleScore(b);
}

// ********************************************************************************
/// <summary>
/// drawSingleVirusCount
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawSingleVirusCount(TBoard *b)
{
	u8 *pvmem;

	sprintf(auxTxt, "%02d", b->virList.count);
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, b->virusX, b->virusY);
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(BG_COLOR, BG_COLOR), strLength(auxTxt) * 2, 9);
	drawText(auxTxt, b->virusX, b->virusY, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
}

// ********************************************************************************
/// <summary>
/// drawScoreBoard2
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawScoreBoard2(TBoard *b)
{
	drawWindow(61, 162, 20, 31, 15, BG_COLOR);
	drawText("LEVEL", 62, 169, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(auxTxt, "%2d", level);
	drawText(auxTxt, 74, 169, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText("VIRUS", 62, 179, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	drawSingleVirusCount(b);
}

// ********************************************************************************
/// <summary>
/// drawHitSpriteXY
/// Input: board and match to remove form the screen
/// Output: void
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="step"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawHitSpriteXY(u8 x, u8 y, u8 step)
{
	u8 *pvmem;
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
	//cpct_drawSpriteBlended(pvmem, SP_HIT_0_H, SP_HIT_0_W, hitSprite[step]);
	cpct_drawSprite(hitSprite[step], pvmem, SP_HIT_0_W, SP_HIT_0_H );
}

// ********************************************************************************
/// <summary>
/// drawHitSprite
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <param name="m"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawHitSprite(TBoard *b, TMatch *m)
{
	u8 i;
	u8 x, y;

	for (i = 0; i < m->count; i++)
	{
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		drawHitSpriteXY(b->originX + (x * CELL_WIDTH), b->originY + (y * CELL_HEIGHT), m->animStep);
	}
}

// ********************************************************************************
/// <summary>
/// drawCell
/// Input:
/// Output: void
/// </summary>
/// <param name="b"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawCell(TBoard *b, u8 x, u8 y)
{
	u8 *pvmem;

	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, b->originX + (x * CELL_WIDTH), b->originY + (y * CELL_HEIGHT));
	cpct_drawSpriteBlended(
		pvmem,
		CELL_HEIGHT,
		CELL_WIDTH,
		sprites[b->color[y][x]][b->content[y][x]]);
}

// ********************************************************************************
/// <summary>
/// deleteCell
/// Input:
/// Output: void
/// </summary>
/// <param name="b"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void deleteCell(TBoard *b, u8 x, u8 y)
{
	u8 *pvmem;

	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, b->originX + (x * CELL_WIDTH), b->originY + (y * CELL_HEIGHT));
	cpct_drawSprite(
		emptyCell,
		pvmem,
		CELL_WIDTH,
		CELL_HEIGHT);
}

// ********************************************************************************
/// <summary>
/// updateCell
/// Input:
/// Output: void
/// </summary>
/// <param name="b"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void updateCell(TBoard *b, u8 x, u8 y)
{
	deleteCell(b, x, y);
	drawCell(b, x, y);
}

// ********************************************************************************
/// <summary>
/// printMatch
/// Input: board and match to remove from the screen
/// Output: void
/// </summary>
/// <param name="b"></param>
/// <param name="m"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void printMatch(TBoard *b, TMatch *m)
{
	u8 i;
	u8 x, y;

	for (i = 0; i < m->count; i++)
	{
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		if (b->content[y][x] != 0)
		{
			drawCell(b, x, y);
		}
	}
}

// ********************************************************************************
/// <summary>
/// deleteMatch
/// Input: board and match to remove form the screen
/// Output: void
/// </summary>
/// <param name="b"></param>
/// <param name="m"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void deleteMatch(TBoard *b, TMatch *m)
{
	u8 i;
	u8 x, y;

	for (i = 0; i < m->count; i++)
	{
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);

		deleteCell(b, x, y);

	}
}





// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void animateMatch()
{
	u8 i;
	TBoard *b;

	// Iteration over the animaMatchList to print next step on every match 
	for (i = 0; i < MAX_MATCH_LIST; i++) {
		// Check if the element in the list has an active match (count>0)
		if ((animateMatchList.list[i].count) && ((i_time - animateMatchList.list[i].lastUpdate) > ANIM_SPEED)){
			//select the proper board depending on the board of the match
			if (animateMatchList.list[i].player == PLAYER1) {
				b = &board1;
			}
			else {
				b = &board2;
			}
			// first deletes the current match sprites
			deleteMatch(b, &animateMatchList.list[i]);
			// and depending on the step of the animation print a new frame or init the match
			if (animateMatchList.list[i].animStep < 3) {
				drawHitSprite(b, &animateMatchList.list[i]);
				animateMatchList.list[i].animStep++;
			} else {
				//We are finished with the animation, so init match and decrease animateMatchList count
				initMatch(&animateMatchList.list[i]);
				animateMatchList.count--;
			}
			animateMatchList.list[i].lastUpdate = i_time;
		}
	}
}

// ********************************************************************************
/// <summary>
/// startAnimateMatch
/// Input: board and match to remove form the board
/// Output: void
/// </summary>
/// <param name="b"></param>
/// <param name="m"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void startAnimateMatch(TMatch* m)
{
	m->animStep = 0;
	addMatch(&animateMatchList, m);
	animateMatch();
}

// ********************************************************************************
/// <summary>
/// removeMatch
/// Input: board and match to remove form the board
/// Output: void
/// </summary>
/// <param name="b"></param>
/// <param name="m"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void removeMatch(TBoard *b, TMatch *m)
{
	u8 i;
	u8 x0, y0, c0, d0;
	u8 x, y;
	u8 virusCount = 0;

	x0 = m->x;
	y0 = m->y;
	d0 = m->direction;
	c0 = m->count;

	//erase match form logic board
	//check vertical pill doing the match case
	if ((y0 > 0) && (d0 == VERTICAL) && (b->content[y0][x0] == 2))
	{
		b->content[y0 - 1][x0] = 5;
		updateCell(b, x0, y0 - 1);
	}

	// match loop
	for (i = 0; i < c0; i++)
	{
		y = y0 + (d0 * i);
		x = x0 + ((!d0) * i);
		// erase match from board
		// Change the half of the cell erased
		if (d0 == VERTICAL)
		{
			if (b->content[y][x] == 3)
			{
				b->content[y][x + 1] = 5;
				updateCell(b, x + 1, y);
			}
			if (b->content[y][x] == 4)
			{
				b->content[y][x - 1] = 5;
				updateCell(b, x - 1, y);
			}
		}
		else
		{
			if (b->content[y][x] == 1)
			{
				b->content[y + 1][x] = 5;
				updateCell(b, x, y + 1);
			}
			if (b->content[y][x] == 2)
			{
				b->content[y - 1][x] = 5;
				updateCell(b, x, y - 1);
			}
		}
		if (b->content[y][x] == 6)
		{
			virusCount++; // One virus found
			deleteVirus(&b->virList, x, y);
			drawSingleVirusCount(b);
		}
		b->content[y][x] = 0;
		b->color[y][x] = 255;
	}
	// Add score for killing a virus
	if (virusCount)
	{
		b->score += pointsPerKill[virusCount];
		drawSingleScore(b);
	}
	//Marked the found virus in the match for further treatment
	b->virusMatched = virusCount;

	//erase match from screen
	//deleteMatch(b, m);

	//start match animation
	startAnimateMatch(m);

	initMatch(m);
}

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,21/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void startApplyGravity(TBoard* b) {
	b->applyingGravity = YES;
	applyGravity(b);
}

// ********************************************************************************
/// <summary>
/// applyGravity
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,21/08/2019</changed>
// ********************************************************************************
void applyGravity(TBoard *b)
{
	u8 i, j, k;
	u8 *pvmem;

	for (j = (BOARD_HEIGHT - 2); j > 0; j--)
	{
		for (i = 0; i < BOARD_WIDTH; i++)
		{
			if (
				// is not a virus and not empty
				(b->content[j][i] > 0) && (b->content[j][i] < 6) &&
				(b->content[j + 1][i] == 0) && // there is free space underneath
				!(							   //None of these conditions is met
					//is a complete piece laying on something on it's right side
					((i < 7) && (j < 15) && (b->content[j][i] == 3) && (b->content[j][i + 1] == 4) && (b->content[j + 1][i + 1] != 0)) ||
					////is a complete piece laying on something on it's left side
					((i > 0) && (j < 15) && (b->content[j][i - 1] == 3) && (b->content[j][i] == 4) && (b->content[j + 1][i - 1] != 0))))
			{
				k = j + 1;
				
				//while ((k < BOARD_HEIGHT) && (b->content[k][i] == 0))
				//{
					pvmem = cpct_getScreenPtr(CPCT_VMEM_START, b->originX + (i * CELL_WIDTH), b->originY + ((k - 1) * CELL_HEIGHT));
					cpct_drawSprite(
						emptyCell,
						pvmem,
						CELL_WIDTH,
						CELL_HEIGHT);
					b->content[k][i] = b->content[k - 1][i];
					b->color[k][i] = b->color[k - 1][i];
					b->content[k - 1][i] = 0;
					b->color[k - 1][i] = 255;
					pvmem = cpct_getScreenPtr(CPCT_VMEM_START, b->originX + (i * CELL_WIDTH), b->originY + (k * CELL_HEIGHT));
					cpct_drawSprite(
						sprites[b->color[k][i]][b->content[k][i]],
						pvmem,
						CELL_WIDTH,
						CELL_HEIGHT);
					//delay(2);
					//cpct_waitHalts(5);
			
				
				//Return after moving a line down
				return;
			}
		}
		// proceed with active animations
				if (animateMatchList.count) {
					animateMatch();
				}
	}
	//If no gravity is applied deactivate gravity flag
	b->applyingGravity = NO;
	clearMatches(b);
}

// ********************************************************************************
/// <summary>
/// clearMatches
/// Input:
/// Output:
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
u8 clearMatches(TBoard *b)
{
	u8 row, col;
	u8 i, j, k, l;
	u8 result;

	result = NO;

	// Find matches in rows
	for (row = 0; row < BOARD_HEIGHT; row++)
	{
		i = 0;
		while (i < BOARD_WIDTH)
		{
			if (b->color[row][i] != 255)
			{
				j = i + 1;
				partialCount = 1;
				while ((j < BOARD_WIDTH) && (b->color[row][i] == b->color[row][j]))
				{
					partialCount++;
					j++;
				}
				if (partialCount > 3)
				{
					setMatch(&match, b->player, i, row, HORIZONTAL, partialCount, 0, 0);
					removeMatch(b, &match);
					result = YES;
				}
				i = j;
			}
			else
			{
				i++;
			}
		}
	}
	// Clear matches in cols
	for (col = 0; col < BOARD_WIDTH; col++)
	{
		k = 0;
		while (k < BOARD_HEIGHT)
		{
			if (b->color[k][col] != 255)
			{
				l = k + 1;
				partialCount = 1;
				while ((l < BOARD_HEIGHT) && (b->color[k][col] == b->color[l][col]))
				{
					partialCount++;
					l++;
				}
				if (partialCount > 3)
				{
					setMatch(&match, b->player, col, k, VERTICAL, partialCount, 0, 0);
					removeMatch(b, &match);
					result = YES;
				}
				k = l;
			}
			else
			{
				k++;
			}
		}
	}
	return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Vs section
///////////////////////////////////////////////////////////////////////////////////////////////////

// ********************************************************************************
/// <summary>
/// drawScoreBoardVs1
/// Input:
/// Output:
/// </summary>
/// <param name="b1"></param>
/// <param name="b2"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawScoreBoardVs1(TBoard *b1, TBoard *b2)
{
	drawWindow(1, 3, 30, 39, 15, BG_COLOR);
	//Top
	drawText("TOP", 3, 9, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(auxTxt, "%05d", hallOfFameVs.topScore);
	drawText(auxTxt, 18, 9, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	//Score
	drawText("PLAYER1", 3, 19, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	drawSingleScore(b1);
	drawText("PLAYER2", 3, 29, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	drawSingleScore(b2);
}

// ********************************************************************************
/// <summary>
/// drawScoreBoard2
/// Input:
/// Output:
/// </summary>
/// <param name="b1"></param>
/// <param name="b2"></param>
/// <created>johnlobo,20/08/2019</created>
/// <changed>johnlobo,20/08/2019</changed>
// ********************************************************************************
void drawScoreBoardVs2(TBoard *b1, TBoard *b2)
{
	u8 i;
	u8 *pvmem;

	drawWindow(32, 46, 19, 20, 15, BG_COLOR);
	drawText("LEVEL", 34, 52, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(auxTxt, "%2d", level);
	drawText(auxTxt, 44, 52, COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);

	//Wins panel
	pvmem = cpct_getScreenPtr(SCR_VMEM, 31, 80);
	cpct_drawSolidBox(pvmem, 255, 19, 65);

	for (i = 0; i < 3; i++)
	{
		pvmem = cpct_getScreenPtr(SCR_VMEM, 32, 82 + (i * 21));
		cpct_drawSolidBox(pvmem, cpct_px2byteM0(0, 0), 8, 19);
		pvmem += 9;
		cpct_drawSolidBox(pvmem, cpct_px2byteM0(0, 0), 8, 19);
	}

	// Virus Panels
	//drawWindow(26,172,40,18,15,BG_COLOR);
	drawText("VIRUS", 36, 179, COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	drawWindow(26, 174, 10, 18, 15, BG_COLOR);
	drawWindow(46, 174, 10, 18, 15, BG_COLOR);
	drawSingleVirusCount(b1);
	drawSingleVirusCount(b2);
}