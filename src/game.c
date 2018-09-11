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
#include "sprites/dr.h"
#include "sprites/ams.h"
#include "sprites/trad.h"
#include "sprites/upPills.h"
#include "sprites/downPills.h"
#include "sprites/leftPills.h"
#include "sprites/rightPills.h"
#include "sprites/blocks.h"
#include "sprites/virus.h"
#include "sprites/drRonald.h"
#include "util/util.h"
#include "entities/board.h"
#include "entities/cursor.h"
#include "text/text.h"


TBoard board;
TBoard board2;
TCursor activeCursor;
TCursor activeCursor2;
TCursor nextCursor;
TCursor nextCursor2;

u16 top;
u16 score1, score2;
u8 level;
u8 virus1, virus2;
u32 playerLastUpdate;
u8 activePill;
u8 dead1, dead2;


// Empty Tile : 6x6 pixels, 3x6 bytes.
u8 const emptyCell[3 * 7] = {
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00
};

u8* const sprites[3][9] = {
    {emptyCell, sp_upPills_0, sp_downPills_0, sp_leftPills_0, 
        sp_rightPills_0, sp_blocks_0, sp_virus_0, sp_virus_1, sp_virus_2},
    {emptyCell, sp_upPills_1, sp_downPills_1, sp_leftPills_1, 
        sp_rightPills_1, sp_blocks_1, sp_virus_3, sp_virus_4, sp_virus_5},
    {emptyCell, sp_upPills_2, sp_downPills_2, sp_leftPills_2, 
        sp_rightPills_2, sp_blocks_2, sp_virus_6, sp_virus_7, sp_virus_8}
};
u8 const dimension_W[3][9] = {
    {EMPTYCELL_WIDTH, SP_UPPILLS_0_W, SP_DOWNPILLS_0_W, SP_LEFTPILLS_0_W, 
        SP_RIGHTPILLS_0_W, SP_BLOCKS_0_W, SP_VIRUS_0_W, SP_VIRUS_1_W, SP_VIRUS_2_W},
    {EMPTYCELL_WIDTH, SP_UPPILLS_1_W, SP_DOWNPILLS_1_W, SP_LEFTPILLS_1_W, 
        SP_RIGHTPILLS_1_W, SP_BLOCKS_1_W, SP_VIRUS_3_W, SP_VIRUS_4_W, SP_VIRUS_5_W},
    {EMPTYCELL_WIDTH, SP_UPPILLS_2_W, SP_DOWNPILLS_2_W, SP_LEFTPILLS_2_W, 
        SP_RIGHTPILLS_2_W, SP_BLOCKS_2_W, SP_VIRUS_6_W, SP_VIRUS_7_W, SP_VIRUS_8_W}
};
u8 const dimension_H[3][9] = {
    {EMPTYCELL_HEIGHT, SP_UPPILLS_0_H, SP_DOWNPILLS_0_H, SP_LEFTPILLS_0_H, 
        SP_RIGHTPILLS_0_H, SP_BLOCKS_0_H, SP_VIRUS_0_H, SP_VIRUS_1_H, SP_VIRUS_2_H},
    {EMPTYCELL_HEIGHT, SP_UPPILLS_1_H, SP_DOWNPILLS_1_H, SP_LEFTPILLS_1_H, 
        SP_RIGHTPILLS_1_H, SP_BLOCKS_1_H, SP_VIRUS_3_H, SP_VIRUS_4_H, SP_VIRUS_5_H},
    {EMPTYCELL_HEIGHT, SP_UPPILLS_2_H, SP_DOWNPILLS_2_H, SP_LEFTPILLS_2_H, 
        SP_RIGHTPILLS_2_H, SP_BLOCKS_2_H, SP_VIRUS_6_H, SP_VIRUS_7_H, SP_VIRUS_8_H}
};

u16 const cursorSpeedPerLevel[11] = {100,100,120,60,20,20,20,20,20,20,20};


void addScore(u16 sc, u8 player){
    if (player){
        score2 = score2 + sc;
    } else {
        score1 = score1 + sc;
    }
}


//////////////////////////////////////////////////////////////////
//  printScreenSingle
//  Draws "DrRoland" on the screen
//  Input:      Level
//              
//  Returns:    void.
//
void printScreenSingle(){
    u8 *pvmem;
    u8 i,j;

    clearScreen();   // Clear de Screen BGCOLOR=Black
    cpct_waitVSYNC();  // Sync with the raster to avoid flickering
    // Draw background
    for (j=0;j<13;j++){
        for (i=0;i<40;i++){
            if ((i%2)==(j%2)){
                pvmem = cpct_getScreenPtr(SCR_VMEM,i*4,j*16);
                cpct_drawSolidBox(pvmem, cpct_px2byteM0(2,2),4,8);
            }
        }
    }
    // print title
    cpct_waitVSYNC();  // Sync with the raster to avoid flickering 
    //pvmem = cpct_getScreenPtr(SCR_VMEM,30,5);
    //cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0),22,30);   
    //pvmem = cpct_getScreenPtr(SCR_VMEM,50,5);
    //cpct_drawSolidBox(pvmem, cpct_px2byteM0(0,0),27,30);   
    pvmem = cpct_getScreenPtr(SCR_VMEM, 31, 7);
    //cpct_drawSprite(bk_drRonald_0, pvmem, BK_DRRONALD_0_W, BK_DRRONALD_0_H);
    cpct_drawSpriteMaskedAlignedTable(bk_drRonald_0, pvmem, BK_DRRONALD_0_W, BK_DRRONALD_0_H, g_tablatrans);
    
    pvmem = cpct_getScreenPtr(SCR_VMEM, 53, 7);
    //cpct_drawSprite(bk_drRonald_1, pvmem, BK_DRRONALD_1_W, BK_DRRONALD_1_H);
    cpct_drawSpriteMaskedAlignedTable(bk_drRonald_1, pvmem, BK_DRRONALD_1_W, BK_DRRONALD_1_H, g_tablatrans);

    // clear game area
    //cpct_waitVSYNC();  // Sync with the raster to avoid flickering
    //drawWindow(board.originX-1,board.originY-5,28,119, 15, 0);

    printScoreBoard1();
    printScoreBoard2(&board);

    drawWindow(58,50,18,27,15,BG_COLOR);
	drawText("Next", 62, 55,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
}



//////////////////////////////////////////////////////////////////
//  cursorHit
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
    
    // Clear matches until gravity stops
    //wait4OneKey();
    while (clearMatches(b)){
        applyGravity(b);
    }   
    
    activePill = 0;
    if (cur->y==0){
        dead1 = 1;
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

    if ((cpct_isKeyPressed(k->up) || cpct_isKeyPressed(Joy0_Fire1))){
        delay(4);
        if (cur->position){
            if (cur->x<7){
                cur->position = !cur->position;
                cur->content[0]=3;
                cur->content[1]=4;
                aux = cur->color[0];
                cur->color[0] = cur->color[1];
                cur->color[1] = aux;
                cur->moved = YES;
            }
    
        }else{
            cur->position = !cur->position;
            cur->content[0]=1;
            cur->content[1]=2;
            cur->moved = YES;
        }
    }
}

//////////////////////////////////////////////////////////////////
//  initSingleLevel
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//    
void initSingleLevel(){
    clearScreen();
    // Init board
    initBoard(&board, 30, 76);
    createVirus(&board, level);
    printScreenSingle();
    printBoard(&board);
}

//////////////////////////////////////////////////////////////////
//  initSingleGame
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//    
void initSingleGame(){

// Initial values
score1 = 0;
level = 1;  
    
initSingleLevel();
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
    u32 c = 0;
    u8 pauseGame = 0;
    u8 abortGame = 0;

    c = 0;
    dead1 = 0;
    activePill = 0;
    playerLastUpdate = i_time;
    board.virList.lastUpdate = i_time;
    initCursor(&nextCursor);
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
                cpct_memcpy(&activeCursor, &nextCursor, sizeof(TCursor)); // Copy next piece over active
                initCursor(&nextCursor);
                printNextCursor(&nextCursor);
                printCursor(&board, &activeCursor, CURRENT);
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
            printCursor(&board, &activeCursor, PREVIOUS); // 0 = previous coordinates
            printCursor(&board, &activeCursor, CURRENT); // 1 = current coordinates
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
        
        //Animate Virus
        if ((i_time - board.virList.lastUpdate) > BACT_ANIM_SPEED){
            //cpct_waitVSYNC();
            animateVirusList(&board);
            board.virList.lastUpdate = i_time;
        }

        if (board.virList.count == 0){
            drawWindow(10,60,60,60,15,14); // 15 = white; 0 blue
            sprintf(aux_txt, "Level %d Cleared!!", level);
            drawText(aux_txt, 24, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
            drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
            wait4OneKey();
            level++;
            initSingleLevel();
            activePill = 0;
            playerLastUpdate = i_time;
            board.virList.lastUpdate = i_time;
            initCursor(&nextCursor);
        }

    } while ((dead1 == 0) && (abortGame == 0));

drawWindow(10,60,60,60,15,14); // 15 = white; 0 blue
drawText("You are dead!!", 26, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
wait4OneKey();
}

//////////////////////////////////////////////////////////////////
//  printScreenVs
//  Draws "DrRoland" on the screen
//  Input:      Level
//              
//  Returns:    void.
//
void printScreenVs(){
    u8 *pvmem;
    u8 i,j;

    clearScreen();   // Clear de Screen BGCOLOR=Black
    cpct_waitVSYNC();  // Sync with the raster to avoid flickering
    // Draw background
    for (j=0;j<13;j++){
        for (i=0;i<40;i++){
            if ((i%2)==(j%2)){
                pvmem = cpct_getScreenPtr(SCR_VMEM,i*4,j*16);
                cpct_drawSolidBox(pvmem, cpct_px2byteM0(2,2),4,8);
            }
        }
    }
    // print title
    cpct_waitVSYNC();  // Sync with the raster to avoid flickering 
    pvmem = cpct_getScreenPtr(SCR_VMEM, 31, 7);
    cpct_drawSpriteMaskedAlignedTable(bk_drRonald_0, pvmem, BK_DRRONALD_0_W, BK_DRRONALD_0_H, g_tablatrans);
    
    pvmem = cpct_getScreenPtr(SCR_VMEM, 53, 7);
    cpct_drawSpriteMaskedAlignedTable(bk_drRonald_1, pvmem, BK_DRRONALD_1_W, BK_DRRONALD_1_H, g_tablatrans);

    // clear game area
    //printScoreBoard1();
    //printScoreBoard2(&board);

    drawWindow(58,50,18,27,15,BG_COLOR);
	drawText("Next", 62, 55,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
}

//////////////////////////////////////////////////////////////////
//  initVsLevel
//  Initializes the level for vs mode
//
//  Input: void
//
//  Returns: void
//    
void initVsLevel(){
    clearScreen();
    // Init board
    initBoard(&board, 1, 76);
    initBoard(&board2, 40, 76);
    createVirus(&board, level);
    createVirus(&board2, level);
    printScreenSingle();
    printBoard(&board);
    printBoard(&board2);
}

//////////////////////////////////////////////////////////////////
//  initVsGame
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//    
void initVsGame(){

// Initial values
score1 = 0;
score2 = 0;
level = 1;  
    
initVsLevel();
}

//////////////////////////////////////////////////////////////////
// playVsGame
//  Main loop of the game
//
//  Input: void
//
//  Returns: void
//    
void playVsGame(TKeys *keys)

{
    u32 c = 0;
    u8 pauseGame = 0;
    u8 abortGame = 0;

    c = 0;
    dead1 = 0;
    dead2 = 0;
    activePill = 0;
//playerLastUpdate = i_time;
//board.virlist.lastUpdate = i_time;
//initCursor(&nextCursor);
//// Loop forever
//do  
//{
//    c++; 
//    //Abort Game
//    if (cpct_isKeyPressed(keys->abort)) {
//        abortGame = 1;
//    }
//    // Pause Game
//    if (cpct_isKeyPressed(keys->pause)) {
//        pauseGame = 1;
//        waitKeyUp(keys->pause);
//    }
//    while (pauseGame) {
//        if (cpct_isKeyPressed(keys->pause)) {
//            pauseGame = 0;
//            waitKeyUp(keys->pause);
//        }
//    }
//    //Update player
//    if ((i_time - playerLastUpdate) > PLAYER_SPEED){
//        updatePlayer(&activeCursor, &board, keys);
//        playerLastUpdate = i_time;
//    }
//    
//    // Update active Cursor
//    if ((i_time - activeCursor.lastUpdate) > cursorSpeedPerLevel[level]){
//        if (!activePill){
//            cpct_memcpy(&activeCursor, &nextCursor, sizeof(TCursor)); // Copy next piece over active
//            initCursor(&nextCursor);
//            printNextCursor(&nextCursor);
//            printCursor(&board, &activeCursor, CURRENT);
//            activePill = 1;
//        } else if (checkCollisionDown(&board, &activeCursor)){
//            cursorHit(&board, &activeCursor);    
//            } else {
//                activeCursor.y++;
//                activeCursor.moved = 1;
//            }
//    }
//    
//    // Draw active cursor
//    if (activePill && activeCursor.moved){
//        cpct_waitVSYNC();
//        printCursor(&board, &activeCursor, PREVIOUS); // 0 = previous coordinates
//        printCursor(&board, &activeCursor, CURRENT); // 1 = current coordinates
//        activeCursor.px = activeCursor.x;
//        activeCursor.py = activeCursor.y;
//        activeCursor.ppos = activeCursor.position;
//        activeCursor.pcolor[0] = activeCursor.color[0];
//        activeCursor.pcolor[1] = activeCursor.color[1];
//        activeCursor.pcontent[0] = activeCursor.content[0];
//        activeCursor.pcontent[1] = activeCursor.content[1];
//        activeCursor.lastUpdate = i_time;
//        activeCursor.moved = 0;
//    }
//    
//    //Animate Virus
//    if ((i_time - board.virlist.lastUpdate) > BACT_ANIM_SPEED){
//        //cpct_waitVSYNC();
//        animateVirusList(&board);
//        board.virlist.lastUpdate = i_time;
//    }
//
//    if (board.virlist.count == 0){
//        drawWindow(10,60,60,60,15,14); // 15 = white; 0 blue
//        sprintf(aux_txt, "Level %d Cleared!!", level);
//        drawText(aux_txt, 24, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
//        drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
//        wait4OneKey();
//        level++;
//        initLevel();
//        activePill = 0;
//        playerLastUpdate = i_time;
//        board.virlist.lastUpdate = i_time;
//        initCursor(&nextCursor);
//    }
//
//} while ((dead == 0) && (abortGame == 0));
//
//Window(10,60,60,60,15,14); // 15 = white; 0 blue
//Text("You are dead!!", 26, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
//Text("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
wait4OneKey();
}