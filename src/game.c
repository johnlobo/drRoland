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
#include "text/text.h"


u8 *emptyCell;
TBoard board;
TCursor activeCursor;
TBacteriaList bacteriaList;
TPlayer player;
u16 top;
u16 score;
u8 level;
u8 virus;
u32 playerLastUpdate;
u8 activePill;
u8 dead;




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
u16 const cursorSpeedPerLevel[10] = {100,120,60,20,20,20,20,20,20,20};


//////////////////////////////////////////////////////////////////
//  createtBacterias
//  Set the bacterias in the board depending on the level
//  Input:      Level
//              
//  Returns:    void.
//
void printTitle(){
    u8 *pvmem;
    
    pvmem = cpct_getScreenPtr(SCR_VMEM, 31, 14);
    cpct_drawSprite(bk_dr, pvmem, BK_DR_W, BK_DR_H);
    pvmem = cpct_getScreenPtr(SCR_VMEM, 41, 10);
    cpct_drawSprite(bk_ams, pvmem, BK_AMS_W, BK_AMS_H);
    pvmem = cpct_getScreenPtr(SCR_VMEM, 59, 7);
    cpct_drawSprite(bk_trad, pvmem, BK_TRAD_W, BK_TRAD_H);
}

//////////////////////////////////////////////////////////////////
//  createtBacterias
//  Set the bacterias in the board depending on the level
//  Input:      Level
//              
//  Returns:    void.
//
void createBacterias(u8 lev,TBacteriaList *bactlist, TBoard *b){
    u8 count, x, y, color;

    count = 0;

    do {
        x = (cpct_rand8() % 8);
        y = (cpct_rand8() % 8)+8;

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
//  cursorDead
//  
//
//  Input: void
//
//  Returns: void
// 
void cursorHit(TBoard *b, TCursor *cur){
    b->content[cur->y][cur->x]=cur->content[0];
    b->color[cur->y][cur->x]=cur->color[0];
    // Add position and neg position to change direction vertical & horizaontal
    b->content[cur->y+cur->position][cur->x+(!cur->position)]=cur->content[1];
    b->color[cur->y+cur->position][cur->x+(!cur->position)]=cur->color[1];
    
    //findMatches(b){    
    
    activePill = 0;
    if (cur->y==0){
        dead = 1;
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
void updatePlayer(TCursor *cur, TBoard *b, TKeys *k){
    u8 aux;
    // Check downwards movement
    if (cpct_isKeyPressed(k->down) || cpct_isKeyPressed(Joy0_Down)){
        if (checkCollisionDown(b, cur) == YES){
                cursorHit(b, cur);
        } else {
            cur->y++;
            cur->moved = YES;
        }
    }
    // Check left movement
    if ((cpct_isKeyPressed(k->left) || cpct_isKeyPressed(Joy0_Left)) &&  
        (checkCollisionLeft(b, cur) == NO)){
            cur->x--;
            cur->moved = YES;
    // Check right movement    
    } else if ((cpct_isKeyPressed(k->right) || cpct_isKeyPressed(Joy0_Right)) &&
        (checkCollisionRight(b, cur) == NO)){
            cur->x++;
            cur->moved = YES;
    }
    if ((cpct_isKeyPressed(k->fire1) || cpct_isKeyPressed(Joy0_Fire1)) &&
        (b->content[cur->y+cur->position][cur->x+(!cur->position)] == 0)){  // check if there is space before ratation
        cur->position = !cur->position;
        // If gone back to horizontal then switch halves
        if (!cur->position){
            aux = cur->color[0];
            cur->color[0] = cur->color[1];
            cur->color[1] = aux;
        }
        cur->moved = YES;
    }
}

//////////////////////////////////////////////////////////////////
//  initGame
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//    
void initGame(){
u8 *pvmem;
u8 i,j;

clearScreen();   // Clear de Screen BGCOLOR=Black
// Draw background
for (j=0;j<13;j++){
    for (i=0;i<40;i++){
        if ((i%2)==(j%2)){
            pvmem = cpct_getScreenPtr(SCR_VMEM,i*4,j*16);
            cpct_drawSolidBox(pvmem, cpct_px2byteM0(2,2),4,8);
        }
    }
}
cpct_waitVSYNC();  // Sync with the raster to avoid flickering
// Print Title
printTitle();
// clear game area
drawWindow(BOARD_ORIGIN_X-1,BOARD_ORIGIN_Y-5,28,119, 15, 0);
// Initial values
top = 10000;
score = 0;
level = 0;  
virus = enemiesPerLevel[level];
    
// Init board
cpct_waitVSYNC();  // Sync with the raster to avoid flickering
printScoreBoard1();
printScoreBoard2();
initBoard(&board);
initBacteriaList(&bacteriaList);
//createBacterias(level, &bacteriaList, &board);
printBoard(&board);

}

//////////////////////////////////////////////////////////////////
// playGame
//  Main loop of the game
//
//  Input: void
//
//  Returns: void
//    
void playGame(TKeys *keys)

{
    u32 c = 0;
    u8 winner = 0;
    u8 pauseGame = 0;
    u8 abortGame = 0;

    c = 0;
    dead = 0;
    activePill = 0;
    playerLastUpdate = i_time;
    // Loop forever
    do  
    {
        c++; 
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
        //Update player
        if ((i_time - playerLastUpdate) > PLAYER_SPEED){
            updatePlayer(&activeCursor, &board, keys);
            playerLastUpdate = i_time;
        }
        
        // Update active Cursor
        if ((i_time - activeCursor.lastUpdate) > cursorSpeedPerLevel[level]){
            if (!activePill){
                initCursor(&activeCursor);
                printCursor(&activeCursor, CURRENT);
                activePill = 1;
            } else if (checkCollisionDown(&board, &activeCursor)){
                cursorHit(&board, &activeCursor);    
                } else {
                    activeCursor.y++;
                    activeCursor.moved = 1;
                }
        }
        
        // Draw active cursor
        if (activePill && activeCursor.moved){
            cpct_waitVSYNC();
            printCursor(&activeCursor, PREVIOUS); // 0 = previous coordinates
            printCursor(&activeCursor, CURRENT); // 1 = current coordinates
            activeCursor.px = activeCursor.x;
            activeCursor.py = activeCursor.y;
            activeCursor.ppos = activeCursor.position;
            activeCursor.pcolor[0] = activeCursor.color[0];
            activeCursor.pcolor[1] = activeCursor.color[1];
            activeCursor.pcontent[0] = activeCursor.content[0];
            activeCursor.pcontent[1] = activeCursor.content[1];
            activeCursor.lastUpdate = i_time;
            activeCursor.moved = 0;
        }
        
        //Animate Bacteria
        if ((i_time - bacteriaList.lastUpdate) > BACT_ANIM_SPEED){
            //cpct_waitVSYNC();
            animateBacteriaList(&bacteriaList);
            bacteriaList.lastUpdate = i_time;
        }

    } while ((dead == 0) && (abortGame == 0));

wait4OneKey();
drawWindow(10,60,60,60,15,14); // 15 = white; 0 blue
drawText("You are dead!!", 26, 76,  COLORTXT_WHITE, DOUBLEHEIGHT, OPAQUE);
drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, OPAQUE);
wait4OneKey();
}
