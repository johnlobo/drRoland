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
#include "../sprites/downPills.h"
#include "match.h"

u8* const hitSprite[3] = {sp_hit_0, sp_hit_1, sp_hit_2};
u8 aux_txt[20];
TMatch match;

u8 const enemiesPerLevel[10] = {4,6,8,10,12,14,16,18,19,20};

//////////////////////////////////////////////////////////////////
// initBoard
//
//  initializes the board
//
//  Input: void
//
//  Returns: void
//    
void initBoard(TBoard *b){
	u8 i,j;

	b->originX = 0;
	b->originY = 0;
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			b->color[j][i] = 255;
			b->content[j][i] = 0;
		}
	}
	initBacteriaList(&b->bactList);
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
void fillRandomBoard(TBoard *b){
	u8 i,j;
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			b->color[j][i] = (cpct_rand8() % 3)+1;
			b->content[j][i] = (cpct_rand8() % 6)+1;
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
void printBoard(TBoard *b){
	u8 i,j;
	u8* pvmem;
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			if (b->content[j][i] != 0){
				pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (i*3), BOARD_ORIGIN_Y + (j*7));
				cpct_drawSprite(
					sprites[b->color[j][i]][b->content[j][i]],
					pvmem, 
					dimension_W[b->color[j][i]][b->content[j][i]],
					dimension_H[b->color[j][i]][b->content[j][i]]
				);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////
// clearGameArea
//
//  Input: 
//  Output:
//
//
void clearGameArea(){
	u8 *pvmem;
	pvmem = cpct_getScreenPtr(SCR_VMEM, BOARD_ORIGIN_X - SP_DOWNPILLS_0_W, BOARD_ORIGIN_Y - SP_DOWNPILLS_0_H);
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0), 10*SP_DOWNPILLS_0_W, 10*(SP_DOWNPILLS_0_H+1));
	pvmem = cpct_getScreenPtr(SCR_VMEM, BOARD_ORIGIN_X - SP_DOWNPILLS_0_W, BOARD_ORIGIN_Y+9*(SP_DOWNPILLS_0_H+1));
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0), 10*SP_DOWNPILLS_0_W, 8*(SP_DOWNPILLS_0_H+1));
}

//////////////////////////////////////////////////////////////////
// printScoreBoard1
//
//  Input: 
//  Output:
//
//
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

void printVirusCount(TBoard *b){
	sprintf(aux_txt, "%2d", b->bactList.count);
	drawText(aux_txt, 74, 181,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);
}

//////////////////////////////////////////////////////////////////
// printScoreBoard2
//
//  Input: 
//  Output:
//
//
void printScoreBoard2(TBoard *b){
	//u8 aux_txt[20];
	drawWindow(63,165,18,29,15,14);
	drawText("Level", 65, 171,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
	sprintf(aux_txt, "%2d", level);
	drawText(aux_txt, 74, 171,  COLORTXT_WHITE, NORMALHEIGHT, OPAQUE);   
	drawText("Virus", 65, 181,  COLORTXT_RED, NORMALHEIGHT, OPAQUE);
	printVirusCount(b);
}

//////////////////////////////////////////////////////////////////
// printCell
//
//  Input: 
//  Output: void
//
//
void printCell(TBoard *b, u8 x, u8 y){
	u8 *pvmem;

	pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (x*3), BOARD_ORIGIN_Y + (y*7));
			cpct_drawSpriteBlended(
				pvmem, 
				dimension_H[b->color[y][x]][b->content[y][x]],
				dimension_W[b->color[y][x]][b->content[y][x]],
				sprites[b->color[y][x]][b->content[y][x]]
			);
}

//////////////////////////////////////////////////////////////////
// printMatch
//
//  Input: board and match to remove form the screen
//  Output: void
//
//
void printMatch(TBoard *b, TMatch *m){
	u8 i;
	u8 x,y;
	
	for (i=0;i<m->count; i++){
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		if (b->content[y][x] != 0){
			printCell(b,x,y);
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
// deleteCell
//
//  Input: 
//  Output: void
//
//
void deleteCell(u8 x, u8 y){
	u8 *pvmem;

	pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (x*3), BOARD_ORIGIN_Y + (y*7));
		cpct_drawSprite(
			emptyCell,
			pvmem, 
			SP_HIT_0_W,
			SP_HIT_0_H
		);
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

	for (i=0;i<m->count; i++){
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		deleteCell(x,y);    
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
	deleteMatch(m);
	printHitSprite(m, 1);
	delay(60);
	deleteMatch(m);
	printHitSprite(m, 2);
	delay(60);
	deleteMatch(m);
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
	u8 x,y;
	//erase match from screen
	deleteMatch(m);
	//erase match form logic board
	for (i=0; i<m->count; i++){
		y = m->y + (m->direction*i);
		x = m->x + ((!m->direction)*i);
		// erase match from board
		// Change the half of the cell erased
		if (m->direction == VERTICAL){
			if (b->content[y][x] == 3){
				b->content[y][x+1] = 5;
			}
			if (b->content[y][x] == 4){
				b->content[y][x-1] = 5;
			} 
		}else{ 
			if (b->content[y][x] == 1){
				b->content[y+1][x] = 5;
			}
			if (b->content[y][x] == 4){
				b->content[y-1][x] = 5;
			}
		}
		if (b->content[y][x] == 6){
			deleteBacteria(&b->bactList,x,y);
			printVirusCount(b);
		}
		b->content[y][x] = 0;
		b->color[y][x] = 255;
	}
	//animate match
	animateMatch(m);
}

//////////////////////////////////////////////////////////////////
// applyGravity
//
//  Input: 
//  Output: 
//
//

void applyGravity(TBoard *b){
	u8 i,j,k;
	u8 *pvmem;

	for (j=(BOARD_HEIGHT-2); j>0; j--){
		for (i=0; i<BOARD_WIDTH; i++){
			if ((b->content[j][i]==5) && (b->content[j+1][i] == 0)){
				k = j+1;
				while (b->content[k][i] == 0){
					pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (i*3), BOARD_ORIGIN_Y + ((k-1)*7));
					cpct_drawSprite(
						emptyCell,
						pvmem, 
						SP_HIT_0_W,
						SP_HIT_0_H
					);
					b->content[k][i] = b->content[k-1][i];
					b->color[k][i] = b->color[k-1][i];
					b->content[k-1][i] = 0;
					b->color[k-1][i] = 255;
					pvmem = cpct_getScreenPtr(CPCT_VMEM_START,BOARD_ORIGIN_X + (i*3), BOARD_ORIGIN_Y + (k*7));
					cpct_drawSprite(
						sprites[b->color[k][i]][b->content[k][i]],
						pvmem, 
						dimension_W[b->color[k][i]][b->content[k][i]],
						dimension_H[b->color[k][i]][b->content[k][i]]
					);
					delay(5);
					k++;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////
// clearMatches
//
//  Input: 
//  Output: 
//
//
u8 clearMatches(TBoard *b){
	u8 row, col;
	u8 i, j;
	u8 partialCount;
	u8 result;

	result = NO;

	// Find matches in rows
	for (row=0;row<BOARD_HEIGHT;row++){
		i = 0;
		while (i<BOARD_WIDTH){
			if (b->color[row][i]!=255){
				j  = i + 1;
				partialCount = 1;
				while (j<BOARD_WIDTH){
					if (b->color[row][i] == b->color[row][j]){
						partialCount++;
						j++;
					} else {
						if (partialCount>3){
							match.x = i;
							match.y = row;
							match.direction = HORIZONTAL;
							match.count = partialCount;
							removeMatch(b,&match);
							result = YES;
						}
						j++;
						partialCount = 1;
					}
				}
				if (partialCount>3){
					match.x = i;
					match.y = row;
					match.direction = HORIZONTAL;
					match.count = partialCount;
					removeMatch(b,&match);
					result = YES;
				}
				i++;
			} else {
				i++;
			}
		}
	}
	// Clear matches in cols
	for (col=0;col<BOARD_WIDTH;col++){
		i = 0;
		while (i<BOARD_HEIGHT){
			if (b->color[i][col]!=255){
				j  = i + 1;
				partialCount = 1;
				while (j<BOARD_HEIGHT){
					if (b->color[i][col] == b->color[j][col]){
						partialCount++;
						j++;
					} else {
						if (partialCount>3){
							match.x = col;
							match.y = i;
							match.direction = VERTICAL;
							match.count = partialCount;
							removeMatch(b,&match);
							result = YES;
						}
						j++;
						partialCount = 1;
					}
				}
				if (partialCount>3){
					match.x = col;
					match.y = i;
					match.direction = VERTICAL;
					match.count = partialCount;
					removeMatch(b,&match);
					result = YES;
				}
				i++;
			} else {
				i++;
			}
		}
	}
	return result;
}

//////////////////////////////////////////////////////////////////
//  createtBacterias
//  Set the bacterias in the board depending on the level
//  Input:      Level
//              
//  Returns:    void.
//
void createBacterias(TBoard *b, u8 l){
    u8 count, x, y, color;

    count = 0;

    do {
        x = (cpct_rand8() % 8);
        y = (cpct_rand8() % 6)+10;

        if (b->content[y][x] == 0){
            color = (cpct_rand8() % 3);  // creates a random color
            b->content[y][x] = 6;  // 6 is Bacteria order in the content array;
            b->color[y][x] = color;  // Assign a random color 
            addBacteria(&b->bactList, x, y, 6, color); // add bacteria to de list of baterias
            count++;
        }
    } while (count < enemiesPerLevel[l]);
}