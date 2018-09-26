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
#include <stdio.h>  //because sprintf
#include "../defines.h"
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
// Virus section
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//  initVirus
//  Initialize a Virus
//  Input:      A Virus    
//              
//  Returns:    void.
//
void initVirus(TVirus *vir){
    vir->x = 255;
    vir->y = 255;
    vir->color = 0;
    vir->type = 0;
}

//////////////////////////////////////////////////////////////////
//  initvirusList
//  Initialize a list of Virus
//  Input:      A list of Virus    
//              
//  Returns:    void.
//
void initvirusList(TVirusList *virlist){
    u8 i;

    for (i=0; i<20; i++){
        initVirus(&virlist->virusList[i]);
    }
    virlist->count = 0;
    virlist->step = 0;
    virlist->lastUpdate = i_time;
}

//////////////////////////////////////////////////////////////////
//  addVirus
//  adds a Virus to a Virus list
//  Input:      A list of Virus, virria position, color and type    
//              
//  Returns:    void.
//
void addVirus(TVirusList *virlist, u8 x, u8 y, u8 type, u8 color){
    u8 iter = 0;
    if (virlist->count<20){
        do{
            if (virlist->virusList[iter].type != 0){
                iter++;
            } else {
                break;
            }
        } while (iter<20);

        virlist->virusList[iter].color = color;
        virlist->virusList[iter].type = type;
        virlist->virusList[iter].x = x;
        virlist->virusList[iter].y = y;
        virlist->count++;
    }
}

//////////////////////////////////////////////////////////////////
//  deleteVirus
//  deletes a Virus from a Virus list
//  Input:      A list of Virus and the index of the Virus to remove
//              
//  Returns:    void.
//
void deleteVirus(TVirusList *virlist, u8 x, u8 y){
    u8 i;

    i = 0;
    while (i < MAX_VIR_LIST){
        if ((virlist->virusList[i].x == x) && (virlist->virusList[i].y == y)){
            break;
        } else{
            i++;
        }
    }
        if (i < MAX_VIR_LIST){
            virlist->virusList[i].x = 255;
            virlist->virusList[i].y = 255;
            virlist->virusList[i].type = 0;
            virlist->virusList[i].color = 255;
            virlist->count--;
        }
}

//////////////////////////////////////////////////////////////////
//  printOneVirus
//  Prints one Virus in the board
//  Input:      The Virus and the board
//              
//  Returns:    void.
//
void printOneVirus(TBoard *b, u8 i){
    u8 *pvmem;
    TVirus *vir;
    u8 step;

    vir = &b->virList.virusList[i];
    step = b->virList.step;
    // claculate screen adrees for the Virus
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
        //b->originX + (vir->x*3), 
        b->originX + (vir->x* CELL_WIDTH), 
        b->originY + (vir->y*CELL_HEIGHT) 
        //b->originY + (vir->y*7)
    );  
    // Print Virus
    cpct_drawSpriteBlended(        
        pvmem, dimension_H[vir->color][vir->type], dimension_W[vir->color][vir->type],
        sprites[vir->color][vir->type+(step%3)]
    );
}

//////////////////////////////////////////////////////////////////
//  printvirusList
//  Prints all the Virus in a board
//  Input:      A list of Virus and the board
//              
//  Returns:    void.
//
void printVirusList(TBoard *b){
    u8 i;

    for (i=0;i<20;i++){
        if (b->virList.virusList[i].type){
            printOneVirus(b, i);
        }
    }
}

//////////////////////////////////////////////////////////////////
//  animatevirusList
//  Animates all the Virus in a board
//  Input:      A list of Virus and the board
//              
//  Returns:    void.
//
void animateVirusList(TBoard *b){
    printVirusList(b);
    b->virList.step++;
    printVirusList(b);
}

//////////////////////////////////////////////////////////////////
//  createtVirus
//  Set the Virus in the board depending on the level
//  Input:      Level
//              
//  Returns:    void.
//
void createVirus(TBoard *b, u8 l){
    u8 count, x, y, color;

    count = 0;

    do {
        x = (cpct_rand8() % 8);
        y = (cpct_rand8() % 6)+10;

        if (b->content[y][x] == 0){
            color = (cpct_rand8() % 3);  // creates a random color
            b->content[y][x] = 6;  // 6 is Virus order in the content array;
            b->color[y][x] = color;  // Assign a random color 
            addVirus(&b->virList, x, y, 6, color); // add Virus to de list of baterias
            count++;
        }
    } while (count < enemiesPerLevel[l]);
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
void initBoard(TBoard *b, u8 x, u8 y, u8 scX, u8 scY, u8 viX, u8 viY){
	u8 i,j;

	b->originX = x;
	b->originY = y;
	b->scoreX = scX;
	b->scoreY = scY;
	b->virusX = viX;
	b->virusY = viY;
	for (j=0;j<BOARD_HEIGHT;j++){
		for (i=0;i<BOARD_WIDTH;i++){
			b->color[j][i] = 255;
			b->content[j][i] = 0;
		}
	}
	initvirusList(&b->virList);
	b->score = 0;
	b->virusMatched = NO;
	initVirus(&b->virusFound);
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
// printSingleScore
//
//  Input: 
//  Output:
//
void printSingleScore(TBoard *b){
	sprintf(aux_txt, "%05d", b->score);
	//drawText(aux_txt, 14, 19,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText(aux_txt, b->scoreX, b->scoreY,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);

}

//////////////////////////////////////////////////////////////////
// printScoreBoard1
//
//  Input: 
//  Output:
//
void printScoreBoard1(TBoard *b){
	//u8 aux_txt[20];
	drawWindow(1,3,26,29,15,14);
	//Top
	drawText("Top", 3, 9,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(aux_txt, "%5d", top);
	drawText(aux_txt, 14, 9,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);   
	//Score
	drawText("Score", 3, 19,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	printSingleScore(b);   
}

//////////////////////////////////////////////////////////////////
// printSingleVirusCount
//
//  Input: 
//  Output:
//
void printSingleVirusCount(TBoard *b){
	sprintf(aux_txt, "%02d", b->virList.count);
	//drawText(aux_txt, 74, 181,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	drawText(aux_txt, b->virusX, b->virusY,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);

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
	drawWindow(61,162,20,31,15,BG_COLOR);
	drawText("Level", 63, 169,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(aux_txt, "%2d", level);
	drawText(aux_txt, 74, 169,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);   
	drawText("Virus", 63, 179,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	printSingleVirusCount(b);
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

	x0 = m->x;
	y0 = m->y;
	d0 = m->direction;
	c0 = m->count;
	// Reset VirusFound marker in the board
	b->virusMatched = NO;
	initVirus(&b->virusFound);
	// add 100 points
	b->score = b->score + c0*25;
	printSingleScore(b);
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
			deleteVirus(&b->virList,x,y);
			
			//Marked the found virus in the match for further treatment
			b->virusMatched = YES;
			b->virusFound.x = x;
			b->virusFound.y = y;
			b->virusFound.type = 6;
			b->virusFound.color = b->color[y][x];
			
			printSingleVirusCount(b);

			// Add score for killing a virus
			b->score = b->score + 1000;
			
			printSingleScore(b);
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
	u8 compareColor;

	result = NO;
	compareColor = 255;

	// Find matches in rows
	for (row=0;row<BOARD_HEIGHT;row++){
		i = 0;
		while (i<BOARD_WIDTH){
			if (b->color[row][i]!=255){
				compareColor = b->color[row][i];
				j  = i + 1;
				partialCount = 1;
				while (j<BOARD_WIDTH){
					if (b->color[row][j] == compareColor){
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
				compareColor = b->color[i][col];
				j  = i + 1;
				partialCount = 1;
				while (j<BOARD_HEIGHT){
					if (b->color[j][col] == compareColor){
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



//////////////////////////////////////////////////////////////////////////
// Vs section
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
// printScore
//
//  Input: 
//  Output:
//
void printScoreVs(TBoard *b1, TBoard *b2){
	sprintf(aux_txt, "%5d", b1->score);
	drawText(aux_txt, 14, 19,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
	sprintf(aux_txt, "%5d", b2->score);
	drawText(aux_txt, 14, 19,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
}

//////////////////////////////////////////////////////////////////
// printScoreBoardVs1
//
//  Input: 
//  Output:
//
void printScoreBoardVs1(TBoard *b1, TBoard *b2){
	drawWindow(1,3,30,39,15,14);
	//Top
	drawText("Top", 3, 9,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(aux_txt, "%05d", top);
	drawText(aux_txt, 16, 9,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);   
	//Score
	drawText("Player 1", 3, 19,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	printSingleScore(b1);   
	drawText("Player 2", 3, 29,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	printSingleScore(b2);   
}


//////////////////////////////////////////////////////////////////
// printScoreBoard2
//
//  Input: 
//  Output:
//
//
void printScoreBoardVs2(TBoard *b1, TBoard *b2){
	//u8 aux_txt[20];
	drawWindow(32,46,19,20,15,BG_COLOR);
	drawText("Level", 35, 52,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
	sprintf(aux_txt, "%2d", level);
	drawText(aux_txt, 44, 52,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);   

	// Virus Panels
	//drawWindow(26,172,40,18,15,BG_COLOR);
	drawText("Virus", 36, 177,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);   
	drawWindow(26,172,10,18,15,BG_COLOR);
	drawWindow(46,172,10,18,15,BG_COLOR);
	printSingleVirusCount(b1);
	printSingleVirusCount(b2);
}