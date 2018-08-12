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
TMatch match;

u8 const enemiesPerLevel[11] = {0,4,6,8,10,12,14,16,18,19,20};

u8 partialCount;


//////////////////////////////////////////////////////////////////////////
// Bacteria section
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//  initBacteria
//  Initialize a bacteria
//  Input:      A bacteria    
//              
//  Returns:    void.
//
void initBacteria(TBacteria *bact){
    bact->x = 255;
    bact->y = 255;
    bact->color = 0;
    bact->type = 0;
}

//////////////////////////////////////////////////////////////////
//  initBacteriaList
//  Initialize a list of bacteria
//  Input:      A list of bacteria    
//              
//  Returns:    void.
//
void initBacteriaList(TBacteriaList *bactlist){
    u8 i;

    for (i=0; i<20; i++){
        initBacteria(&bactlist->bacteriaList[i]);
    }
    bactlist->count = 0;
    bactlist->step = 0;
    bactlist->lastUpdate = i_time;
}

//////////////////////////////////////////////////////////////////
//  addBacteria
//  adds a bacteria to a bacteria list
//  Input:      A list of bacteria, bactria position, color and type    
//              
//  Returns:    void.
//
void addBacteria(TBacteriaList *bactlist, u8 x, u8 y, u8 type, u8 color){
    u8 iter = 0;
    if (bactlist->count<20){
        do{
            if (bactlist->bacteriaList[iter].type != 0){
                iter++;
            } else {
                break;
            }
        } while (iter<20);
        bactlist->bacteriaList[iter].color = color;
        bactlist->bacteriaList[iter].type = type;
        bactlist->bacteriaList[iter].x = x;
        bactlist->bacteriaList[iter].y = y;
        bactlist->count++;
    }
}

//////////////////////////////////////////////////////////////////
//  deleteBacteria
//  deletes a bacteria from a bacteria list
//  Input:      A list of bacteria and the index of the bacteria to remove
//              
//  Returns:    void.
//
void deleteBacteria(TBacteriaList *bactlist, u8 x, u8 y){
    u8 i;

    i = 0;
    while (i < MAX_BACT_LIST){
        if ((bactlist->bacteriaList[i].x == x) && (bactlist->bacteriaList[i].y == y)){
            break;
        } else{
            i++;
        }
    }
        if (i < MAX_BACT_LIST){
            bactlist->bacteriaList[i].x = 255;
            bactlist->bacteriaList[i].y = 255;
            bactlist->bacteriaList[i].type = 0;
            bactlist->bacteriaList[i].color = 255;
            bactlist->count--;
        }
}

//////////////////////////////////////////////////////////////////
//  printOneBacteria
//  Prints one bacteria in the board
//  Input:      The bacteria and the board
//              
//  Returns:    void.
//
void printOneBacteria(TBoard *b, u8 i){
    u8 *pvmem;
    TBacteria *bact;
    u8 step;

    bact = &b->bactList.bacteriaList[i];
    step = b->bactList.step;
    // claculate screen adrees for the bacteria
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
        //b->originX + (bact->x*3), 
        b->originX + (bact->x* CELL_WIDTH), 
        b->originY + (bact->y*CELL_HEIGHT) 
        //b->originY + (bact->y*7)
    );  
    // Print bacteria
    cpct_drawSpriteBlended(        
        pvmem, dimension_H[bact->color][bact->type], dimension_W[bact->color][bact->type],
        sprites[bact->color][bact->type+(step%3)]
    );
}

//////////////////////////////////////////////////////////////////
//  printBacteriaList
//  Prints all the bacteria in a board
//  Input:      A list of bacteria and the board
//              
//  Returns:    void.
//
void printBacteriaList(TBoard *b){
    u8 i;

    for (i=0;i<20;i++){
        if (b->bactList.bacteriaList[i].type){
            printOneBacteria(b, i);
        }
    }
}

//////////////////////////////////////////////////////////////////
//  animateBacteriaList
//  Animates all the bacteria in a board
//  Input:      A list of bacteria and the board
//              
//  Returns:    void.
//
void animateBacteriaList(TBoard *b){
    printBacteriaList(b);
    b->bactList.step++;
    printBacteriaList(b);
}



//////////////////////////////////////////////////////////////////////////
// Board section
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////
// initBoard
//
//  initializes the board
//
//  Input: void
//
//  Returns: void
//    
void initBoard(TBoard *b, u8 x, u8 y){
	u8 i,j;

	b->originX = x;
	b->originY = y;
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			b->color[j][i] = 255;
			b->content[j][i] = 0;
		}
	}
	initBacteriaList(&b->bactList);
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

	// Clear board background
	drawWindow(b->originX-1,b->originY-5,28,119, 15, BG_COLOR);
	
	//Print cells
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			if (b->content[j][i] != 0){
				pvmem = cpct_getScreenPtr(CPCT_VMEM_START,b->originX + (i*CELL_WIDTH), b->originY + (j*CELL_HEIGHT));
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
void clearGameArea(TBoard *b){
	u8 *pvmem;
	pvmem = cpct_getScreenPtr(SCR_VMEM, b->originX - SP_DOWNPILLS_0_W, b->originY - SP_DOWNPILLS_0_H);
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(BG_COLOR,BG_COLOR), 10*SP_DOWNPILLS_0_W, 10*(SP_DOWNPILLS_0_H+1));
	pvmem = cpct_getScreenPtr(SCR_VMEM, b->originX - SP_DOWNPILLS_0_W, b->originY+9*(SP_DOWNPILLS_0_H+1));
	cpct_drawSolidBox(pvmem, cpct_px2byteM0(BG_COLOR,BG_COLOR), 10*SP_DOWNPILLS_0_W, 8*(SP_DOWNPILLS_0_H+1));
}

//////////////////////////////////////////////////////////////////
// printScore
//
//  Input: 
//  Output:
//
void printScore(){
	sprintf(aux_txt, "%5d", score);
	drawText(aux_txt, 14, 19,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
}

//////////////////////////////////////////////////////////////////
// printScoreBoard1
//
//  Input: 
//  Output:
//
void printScoreBoard1(){
	//u8 aux_txt[20];
	drawWindow(1,3,26,29,15,14);
	//Top
	drawText("Top", 3, 9,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(aux_txt, "%5d", top);
	drawText(aux_txt, 14, 9,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);   
	//Score
	drawText("Score", 3, 19,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	printScore();   
}

void printVirusCount(TBoard *b){
	sprintf(aux_txt, "%2d", b->bactList.count);
	drawText(aux_txt, 74, 181,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
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
	drawText("Level", 65, 171,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(aux_txt, "%2d", level);
	drawText(aux_txt, 74, 171,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);   
	drawText("Virus", 65, 181,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
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

	pvmem = cpct_getScreenPtr(CPCT_VMEM_START,b->originX + (x*CELL_WIDTH), b->originY + (y*CELL_HEIGHT));
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
void printHitSprite(TBoard *b, TMatch *m, u8 step){
	u8 i;
	u8 x,y;
	u8 *pvmem;
	for (i=0;i<m->count; i++){
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		pvmem = cpct_getScreenPtr(CPCT_VMEM_START,b->originX + (x*CELL_WIDTH), b->originY + (y*CELL_HEIGHT));
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
void deleteCell(TBoard *b, u8 x, u8 y){
	u8 *pvmem;

	pvmem = cpct_getScreenPtr(CPCT_VMEM_START,b->originX + (x*CELL_WIDTH), b->originY + (y*CELL_HEIGHT));
		cpct_drawSprite(
			emptyCell,
			pvmem, 
			EMPTYCELL_WIDTH,
			EMPTYCELL_HEIGHT
		);
}

//////////////////////////////////////////////////////////////////
// deleteMatch
//
//  Input: board and match to remove form the screen
//  Output: void
//
//
void deleteMatch(TBoard *b, TMatch *m){
	u8 i;
	u8 x,y;

	for (i=0;i<m->count; i++){
		x = m->x + (i * (!m->direction));
		y = m->y + (i * m->direction);
		deleteCell(b,x,y);    
	}
}
//////////////////////////////////////////////////////////////////
// animateMatch
//
//  Input: board and match to remove form the board
//  Output: void
//
//
void animateMatch(TBoard *b, TMatch *m){
	printHitSprite(b,m, 0);
	delay(60);
	deleteMatch(b,m);
	printHitSprite(b,m, 1);
	delay(60);
	deleteMatch(b,m);
	printHitSprite(b,m, 2);
	delay(60);
	deleteMatch(b,m);
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
	u8 x0, y0, c0, d0;
	u8 x,y;

	wait4OneKey();
	x0 = m->x;
	y0 = m->y;
	d0 = m->direction;
	c0 = m->count;
	// add 100 points
	addScore(c0*25);
	printScore();
	//erase match from screen
	deleteMatch(b,m);
	//erase match form logic board
	for (i=0; i<c0; i++){
		y = y0 + (d0*i);
		x = x0 + ((!d0)*i);
		// erase match from board
		// Change the half of the cell erased
		if (d0 == VERTICAL){
			if (b->content[y][x] == 3){
				b->content[y][x+1] = 5;
				deleteCell(b, x+1, y);
				printCell(b, x+1, y);
			}
			if (b->content[y][x] == 4){
				b->content[y][x-1] = 5;
				deleteCell(b, x-1, y);
				printCell(b, x-1, y);
			} 
		}else{ 
			if (b->content[y][x] == 1){
				b->content[y+1][x] = 5;
				deleteCell(b, x, y+1);
				printCell(b, x, y+1);
			}
			if (b->content[y][x] == 2){
				b->content[y-1][x] = 5;
				deleteCell(b, x, y-1);
				printCell(b, x, y-1);
			}
		}
		if (b->content[y][x] == 6){
			deleteBacteria(&b->bactList,x,y);
			printVirusCount(b);
			// Add score for killing a virus
			addScore(1000);
			printScore();
		}
		b->content[y][x] = 0;
		b->color[y][x] = 255;
	}
	//animate match
	animateMatch(b,m);
	initMatch(m);
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
				while ((k<BOARD_HEIGHT) && (b->content[k][i] == 0)){
					pvmem = cpct_getScreenPtr(CPCT_VMEM_START,b->originX + (i*CELL_WIDTH), b->originY + ((k-1)*CELL_HEIGHT));
					cpct_drawSprite(
						emptyCell,
						pvmem, 
						EMPTYCELL_WIDTH,
						EMPTYCELL_HEIGHT
					);
					b->content[k][i] = b->content[k-1][i];
					b->color[k][i] = b->color[k-1][i];
					b->content[k-1][i] = 0;
					b->color[k-1][i] = 255;
					pvmem = cpct_getScreenPtr(CPCT_VMEM_START,b->originX + (i*CELL_WIDTH), b->originY + (k*CELL_HEIGHT));
					cpct_drawSprite(
						sprites[b->color[k][i]][b->content[k][i]],
						pvmem, 
						dimension_W[b->color[k][i]][b->content[k][i]],
						dimension_H[b->color[k][i]][b->content[k][i]]
					);
					delay(11);
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