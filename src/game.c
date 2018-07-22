//-----------------------------LICENSE NOTICE------------------------------------
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include "defines.h"
#include "game.h"
#include "keyboard/keyboard.h"
#include "sprites/dr.h"
#include "sprites/ams.h"
#include "sprites/trad.h"
#include "sprites/upPills.h"
#include "sprites/downPills.h"
#include "sprites/leftPills.h"
#include "sprites/rightPills.h"
#include "sprites/balls.h"
#include "sprites/bacterias.h"
#include "util/util.h"
#include "entities/board.h"
#include "entities/player.h"
#include "entities/bacteria.h"

u8 *emptyCell;
TBoard board;
TCursor activeCursor;
TBacteriaList bacteriaList;
u8 level;


u8* const sprites[3][9] = {
    {emptyCell, sp_upPills_0, sp_downPills_0, sp_leftPills_0, 
        sp_rightPills_0, sp_balls_0, sp_bacterias_0, sp_bacterias_1, sp_bacterias_2},
    {emptyCell, sp_upPills_1, sp_downPills_1, sp_leftPills_1, 
        sp_rightPills_1, sp_balls_1, sp_bacterias_3, sp_bacterias_4, sp_bacterias_5},
    {emptyCell, sp_upPills_2, sp_downPills_2, sp_leftPills_2, 
        sp_rightPills_2, sp_balls_2, sp_bacterias_6, sp_bacterias_7, sp_bacterias_8}
};
u8 const dimension_W[3][9] = {
    {0, SP_UPPILLS_0_W, SP_DOWNPILLS_0_W, SP_LEFTPILLS_0_W, 
        SP_RIGHTPILLS_0_W, SP_BALLS_0_W, SP_BACTERIAS_0_W, SP_BACTERIAS_1_W, SP_BACTERIAS_2_W},
    {0, SP_UPPILLS_1_W, SP_DOWNPILLS_1_W, SP_LEFTPILLS_1_W, 
        SP_RIGHTPILLS_1_W, SP_BALLS_1_W, SP_BACTERIAS_3_W, SP_BACTERIAS_4_W, SP_BACTERIAS_5_W},
    {0, SP_UPPILLS_2_W, SP_DOWNPILLS_2_W, SP_LEFTPILLS_2_W, 
        SP_RIGHTPILLS_2_W, SP_BALLS_2_W, SP_BACTERIAS_6_W, SP_BACTERIAS_7_W, SP_BACTERIAS_8_W}
};
u8 const dimension_H[3][9] = {
    {0, SP_UPPILLS_0_H, SP_DOWNPILLS_0_H, SP_LEFTPILLS_0_H, 
        SP_RIGHTPILLS_0_H, SP_BALLS_0_H, SP_BACTERIAS_0_H, SP_BACTERIAS_1_H, SP_BACTERIAS_2_H},
    {0, SP_UPPILLS_1_H, SP_DOWNPILLS_1_H, SP_LEFTPILLS_1_H, 
        SP_RIGHTPILLS_1_H, SP_BALLS_1_H, SP_BACTERIAS_3_H, SP_BACTERIAS_4_H, SP_BACTERIAS_5_H},
    {0, SP_UPPILLS_2_H, SP_DOWNPILLS_2_H, SP_LEFTPILLS_2_H, 
        SP_RIGHTPILLS_2_H, SP_BALLS_2_H, SP_BACTERIAS_6_H, SP_BACTERIAS_7_H, SP_BACTERIAS_8_H}
};

u8 const enemiesPerLevel[10] = {4,6,8,10,12,14,16,18,19,20};

//////////////////////////////////////////////////////////////////
// CheckCollisionDown
//
//
//
// Returns: 1 if the cursor hits something, 0 if not.
//

u8 checkCollisionDown(TBoard *aux, TCursor *cursor){
    if (cursor->position == 1){
        // Check the cell two rows down if pill is vertical
        if (aux->content[cursor->y+2][cursor->x]){
            return 1;
        } else return 0;
    } else {
        // Check two cells in the next row if pill is horizaontal
        if (aux->content[cursor->y+1][cursor->x] || aux->content[cursor->y+1][cursor->x+1]){
            return 1;
        } else return 0;
    }
}

//////////////////////////////////////////////////////////////////
//  initBacterias
//  Set the bacterias in the board depending on the level
//  Input:      Level
//              
//  Returns:    void.
//
void initBacterias(u8 lev,TBacteriaList *bactlist, TBoard *b){
    u8 count, x, y, color;

    count = 0;

    do {
        x = (cpct_rand8() % 8);
        y = (cpct_rand8() % 16);

        if (b->content[y][x] == 0){
            color = (cpct_rand8() % 3);  // creates a random color
            b->content[y][x] = 6;  // 6 is Bacteria order in the content array;
            b->color[y][x] = color;  // Assign a random color 
            addBacteria(bactlist, x, y, 6, color); // add bacteria to de list of baterias
            count++;
        }
    } while (count < enemiesPerLevel[lev]);
}

//////////////////////////////////////////////////////////////////
// initGame
//
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//    
void initGame(){
u8 *pvmem;
u8 i,j;

cpct_memset(CPCT_VMEM_START, cpct_px2byteM0(0,0), 0x4000);   // Clear de Screen BGCOLOR=Black

for (j=0;j<13;j++){
    for (i=0;i<40;i++){
        if ((i%2)==(j%2)){
            pvmem = cpct_getScreenPtr(SCR_VMEM,i*4,j*16);
            cpct_drawSolidBox(pvmem, cpct_px2byteM0(2,2),4,8);
        }
    }
}
// Print Title
pvmem = cpct_getScreenPtr(SCR_VMEM, 18, 14);
cpct_drawSprite(bk_dr, pvmem, BK_DR_W, BK_DR_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 28, 10);
cpct_drawSprite(bk_ams, pvmem, BK_AMS_W, BK_AMS_H);
pvmem = cpct_getScreenPtr(SCR_VMEM, 46, 7);
cpct_drawSprite(bk_trad, pvmem, BK_TRAD_W, BK_TRAD_H);

// clear game area
clearGameArea();

level = 0;  // Initial level

initBoard(&board);
fillRandomBoard(&board);
printBoard(&board);
wait4OneKey();

clearGameArea();
initBoard(&board);
initBacteriaList(&bacteriaList);
initBacterias(level, &bacteriaList, &board);
//createBacterias(5, &board);
printBoard(&board);

wait4OneKey();

}

//////////////////////////////////////////////////////////////////
// playGame
//
//  Main loop of the game
//
//  Input: void
//
//  Returns: void
//    
void playGame(TKeys *keys)

{
    u32 c = 0;
    u8 dead = 0;
    u8 winner = 0;
    u8 pauseGame = 0;
    u8 abortGame = 0;
    u8 activePill = 0;

    c = 0;
    // Loop forever
    do  
    {
        c++;

        if ((c%5) == 0){
            if (!activePill){
                createCursor(&activeCursor);
                printCursor(&activeCursor);
                activePill = 1;
            } else if ((activeCursor.y>15) || (checkCollisionDown(&board, &activeCursor))){
                board.content[activeCursor.y][activeCursor.x]=activeCursor.content[0];
                board.color[activeCursor.y][activeCursor.x]=activeCursor.color[0];
                activePill = 0;
                } else {
                    printCursor(&activeCursor);
                    activeCursor.y++;
                    printCursor(&activeCursor);
                    delay(50);
                }    
        }

        if ((c%5) == 0){
            //cpct_waitVSYNC();
            animateBacteriaList(&bacteriaList, &board);
        }

        //Abort Game
        if (cpct_isKeyPressed(keys->abort)) {
            abortGame = 1;
        }
        // Pause Game
        if (cpct_isKeyPressed(keys->pause)) {
            pauseGame = 1;
            waitKeyUp(keys->pause);
        }
        while (pauseGame) {
            if (cpct_isKeyPressed(keys->pause)) {
                pauseGame = 0;
                waitKeyUp(keys->pause);
            }
        }
        // Players block


    } while ((dead == 0) && (winner == 0) && (abortGame == 0));
}
