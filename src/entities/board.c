//-----------------------------LICENSE NOTICE------------------------------------
//
//	|  _  \     / _ \              | |               | |
//	| | | |_ __/ /_\ \_ __ ___  ___| |_ _ __ __ _  __| |
//	| | | | '__|  _  | '_ ` _ \/ __| __| '__/ _` |/ _` |
//	| |/ /| |_ | | | | | | | | \__ \ |_| | | (_| | (_| |
//	|___/ |_(_)\_| |_/_| |_| |_|___/\__|_|  \__,_|\__,_|
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
#include <stdio.h>  //because sprintf
#include "defines.h"
#include "board.h"
#include "../game.h"
#include "../util/util.h"
#include "../text/text.h"
#include "../sprites/hit.h"
u8* const hitSprite[3] = {sp_hit_0, sp_hit_1, sp_hit_2};
TMatch m;
u8 aux_txt[20];
//////////////////////////////////////////////////////////////////
// initBoard
//
//  initializes the board
//
//  Input: void
//
//  Returns: void
//    
void initBoard(TBoard *board){
	u8 i,j;
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			board->color[j][i] = 0;
			board->content[j][i] = 0;
		}
	}
}
//////////////////////////////////////////////////////////////////
// initMatch
//
//  initializes the match
//
//  Input: void
//
//  Returns: void
//    
void initMatch(TMatch *match){
	match->x = 255;
	match->y = 255;
	match->direction = 255;
	match->count = 0;
}
//////////////////////////////////////////////////////////////////
// fillRandomBoard
//
//  Fills the board with random tiles (debug)
//
//  Input: void
//
//  Returns: void
//    
void fillRandomBoard(TBoard *board){
	u8 i,j;
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			board->color[j][i] = (cpct_rand8() % 3)+1;
			board->content[j][i] = (cpct_rand8() % 6)+1;
		}
	}
}
//////////////////////////////////////////////////////////////////
// printBoard
//
//  prints the board on the screen
//
//  Input: void
//
//  Returns: void
//    
void printBoard(TBoard *board){
	u8 i,j;
	u8* pvmem;
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			if (board->content[j][i] != 0){
				pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (i*3), BOARD_ORIGIN_Y + (j*7));
				cpct_drawSprite(
					sprites[board->color[j][i]][board->content[j][i]],
					pvmem, 
					dimension_W[board->color[j][i]][board->content[j][i]],
					dimension_H[board->color[j][i]][board->content[j][i]]
				);
			}
		}
	}
}
void clearGameArea(){
	u8 *pvmem;
	pvmem = cpct_getScreenPtr(SCR_VMEM, BOARD_ORIGIN_X - SP_DOWNPILLS_0_W, BOARD_ORIGIN_Y - SP_DOWNPILLS_0_H);
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0), 10*SP_DOWNPILLS_0_W, 10*(SP_DOWNPILLS_0_H+1));
	pvmem = cpct_getScreenPtr(SCR_VMEM, BOARD_ORIGIN_X - SP_DOWNPILLS_0_W, BOARD_ORIGIN_Y+9*(SP_DOWNPILLS_0_H+1));
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0), 10*SP_DOWNPILLS_0_W, 8*(SP_DOWNPILLS_0_H+1));
}
void printScoreBoard1(){
	//u8 aux_txt[20];
	drawWindow(1,3,26,29,15,14);
	//Top
	drawText("Top", 3, 9,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
	sprintf(aux_txt, "%5d", top);
	drawText(aux_txt, 14, 9,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);   
	//Score
	drawText("Score", 3, 19,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
	sprintf(aux_txt, "%5d", score);
	drawText(aux_txt, 14, 19,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);   
}
void printScoreBoard2(){
	//u8 aux_txt[20];
	drawWindow(63,165,18,29,15,14);
	drawText("Level", 65, 171,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
	sprintf(aux_txt, "%2d", level);
	drawText(aux_txt, 74, 171,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);   
	drawText("Virus", 65, 181,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
	sprintf(aux_txt, "%2d", virus);
	drawText(aux_txt, 74, 181,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);
}
//////////////////////////////////////////////////////////////////
// checkMatchInRow
//
//  Input: board, row to analyze and match to store the result
//  Output: 1 if a match is found, 0 otherwise.
//
//
u8 findMatchInRows(TBoard *b, u8 row, TMatch *match){
	u8 x;
	u8 i;
	u8 currentColor;
	u8 count;
	// Search for the first not null element in the row
	count = 0;
	i = 0;
	x = 0;
	while ((b->content[row][i] == 0) && (i<BOARD_WIDTH)){
		i++;
	}
	// If a not null element found begin the count
	if (i<BOARD_WIDTH){
		count = 1;
		currentColor = b->color[row][i];
		i++;
		while (i<BOARD_WIDTH){
			if ((b->content[row][i] != 0) && (b->color[row][i] == currentColor)){
				count++;
				i++;
			} else { 
				if (count>1){
					break;
				}else{
					// Search for the next not null element in the row
					while ((b->content[row][i] == 0) && (i<BOARD_WIDTH)){
						i++;
					}
					// If a not null element found begin the count
					if (i<BOARD_WIDTH){
						currentColor = b->color[row][i];
						x = i;
						i++;
					}
				}
			  }
		}
		//Debug
		sprintf(aux_txt, "row:%d",row);
		drawText(aux_txt, 0, 100,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);
		sprintf(aux_txt, "x:%d",x);
		drawText(aux_txt, 0, 110,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);
		sprintf(aux_txt, "count:%d",count);
		drawText(aux_txt, 0, 120,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);
		wait4OneKey();
		
		if (count>3){
			match->x = x;
			match->y = row;
			match->direction = HORIZONTAL;
			match->count = count;
			return YES;        
		}
	}
	return NO;
}
//////////////////////////////////////////////////////////////////
// printMatch
//
//  Input: board and match to remove form the screen
//  Output: void
//
//
void printMatch(TBoard *board, TMatch *m){
	u8 i;
	u8 x,y;
	u8 *pvmem;
	for (i=0;i<m->count; i++){
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		if (board->content[y][x] != 0){
			pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (x*3), BOARD_ORIGIN_Y + (y*7));
			cpct_drawSpriteBlended(
				pvmem, 
				dimension_H[board->color[y][x]][board->content[y][x]],
				dimension_W[board->color[y][x]][board->content[y][x]],
				sprites[board->color[y][x]][board->content[y][x]]
			);
		}
	}
}
//////////////////////////////////////////////////////////////////
// printHitSprite
//
//  Input: board and match to remove form the screen
//  Output: void
//
//
void printHitSprite(TMatch *m, u8 step){
	u8 i;
	u8 x,y;
	u8 *pvmem;
	for (i=0;i<m->count; i++){
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (x*3), BOARD_ORIGIN_Y + (y*7));
		cpct_drawSpriteBlended(
			pvmem, 
			SP_HIT_0_H,
			SP_HIT_0_W,
			hitSprite[step]
		);    
	}
}
//////////////////////////////////////////////////////////////////
// deleteMatch
//
//  Input: board and match to remove form the screen
//  Output: void
//
//
void deleteMatch(TMatch *m){
	u8 i;
	u8 x,y;
	u8 *pvmem;
	for (i=0;i<m->count; i++){
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (x*3), BOARD_ORIGIN_Y + (y*7));
		cpct_drawSprite(
			emptyCell,
			pvmem, 
			SP_HIT_0_W,
			SP_HIT_0_H
		);    
	}
}
//////////////////////////////////////////////////////////////////
// animateMatch
//
//  Input: board and match to remove form the board
//  Output: void
//
//
void animateMatch(TMatch *m){
	printHitSprite(m, 0);
	delay(60);
	printHitSprite(m, 0);
	printHitSprite(m, 1);
	delay(60);
	printHitSprite(m, 1);
	printHitSprite(m, 2);
	delay(60);
	printHitSprite(m, 2); 
	delay(60);
}
//////////////////////////////////////////////////////////////////
// removeMatch
//
//  Input: board and match to remove form the board
//  Output: void
//
//
void removeMatch(TBoard *b, TMatch *m){
	u8 i;
	//erase match from screen
		wait4OneKey();
	//printMatch(b,m);
	deleteMatch(m);
	//erase match form logic board
	for (i=0; i<m->count; i++){
		// erase match from board
		b->content[m->y + (m->direction*i)][m->x+((!m->direction)*i)] = 0;
		b->color[m->y+(m->direction*i)][m->x+((!m->direction)*i)] = 0;
	}
	//animate match
		wait4OneKey();
	animateMatch(m);
	//apply gravity
	//applyGravity(b);
}
//////////////////////////////////////////////////////////////////
// findMatches
//
//  Input: board and match to remove form the board
//  Output: void
//
//
void findMatches(TBoard *b){
	u8 j;
	// Search in Rows
	j = 0;
	do{
		if (findMatchInRows(b,j,&m)){
			removeMatch(b,&m);
			initMatch(&m);
			j++;
		} else{
			j++;
		}
	} while (j<BOARD_HEIGHT);
}
