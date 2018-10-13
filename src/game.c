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
#include "sprites/letterMarker.h"


TBoard board1;
TBoard board2;
TCursor activeCursor1;
TCursor activeCursor2;
TCursor nextCursor1;
TCursor nextCursor2;

u16 top;
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
u8* const spritesBigVirus[9] = { sp_viruses_big_0, sp_viruses_big_1, sp_viruses_big_2 };
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

u16 const cursorSpeedPerLevel[20] = {150,140,140,130,130,120,120,120,110,110,110,100,100,100,90,90,80,80,70,70};

// Inital coord: 61,81
// Final coord: 40, 51
u8 const throwCoordsX[5] = {57,53,49,45,40};
u8 const throwCoordsY[5] = {70,50,30,40,51};
u8 screen_buffer[50] = {
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00
};

void updateTopScoreMarker(u8 *x, u8 *y, u8 dir){
    u8 *pvmem;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(*x*3), 28+(*y*12) );
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);
    
    switch (dir)
    {
        case UP:
            *y=*y-1;
            break;
        case DOWN:
            *y=*y+1;
            break;
        case LEFT:
            *x=*x-1;
            break;
        default:
            *x=*x+1;            
            break;
    }

    pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(*x*3), 28+(*y*12) );
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);    
}

//////////////////////////////////////////////////////////////////
//  getTopScoreName
//  
//  Input: void
//
//  Returns: void
// 

void getTopScoreName(TKeys *k){
    u8 i;
    u8 aux_txt[2];
    u8 *pvmem;
    u8 x,y;
    u8 end;
    u8 result[20];

    aux_txt[0] = 'A';
    aux_txt[1] = '\0';
    drawWindow(10,10,60,120, 15, BG_COLOR);
    for (i=0; i<26; i++){
        drawText(aux_txt, 14+((i%13)*3), 30+((i/13)*12),  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        aux_txt[0] = 66+i;
    }
    aux_txt[0] = 'a';
    for (i=0; i<26; i++){
        drawText(aux_txt, 14+((i%13)*3), 54+((i/13)*12),  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
        aux_txt[0] = 98+i;
    }
    drawText("space", 14, 78,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("delete", 29, 78,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);
    drawText("end", 46, 78,  COLORTXT_WHITE, NORMALHEIGHT, TRANSPARENT);   

    x = 0;
    y = 0;
    end = 0;
    result[0] = '\0';
    k->fireCooling = 0;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 13+(x*3), 28+(y*12) );
    cpct_drawSpriteBlended(pvmem, SP_LETTERMARKER_H, SP_LETTERMARKER_W, sp_letterMarker);

    while (!end){
        delay(20);
            // Check downwards movement
        if ((y<3) && (cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down))){
            updateTopScoreMarker(&x,&y,DOWN);
        } else if ((y>0) && (cpct_isKeyPressed(k->up) || cpct_isKeyPressed(k->j_up))){
            updateTopScoreMarker(&x,&y,UP);
        }
        // Check left movement
        if ((x>0) && (cpct_isKeyPressed(k->left) || cpct_isKeyPressed(k->j_left))){
            updateTopScoreMarker(&x,&y,LEFT);            
        // Check right movement    
        } else if ((x<12) && (cpct_isKeyPressed(k->right) || cpct_isKeyPressed(k->j_right))){
            updateTopScoreMarker(&x,&y,RIGHT);            
        }

	    if (k->fireCooling > 0){
	    	k->fireCooling--;
	    } else {
        	if ((cpct_isKeyPressed(k->up) || cpct_isKeyPressed(k->j_fire1))){ 
                result[strLength(result)-1] = 65 + x + (12*y);
                result[strLength(result)] = '\0';
                drawText(result, 20, 100,  COLORTXT_YELLOW, DOUBLEHEIGHT, TRANSPARENT);                   
        	}
	    }
    }

    wait4OneKey();
}

//////////////////////////////////////////////////////////////////
//  initBigVirusOnScreen
//  
//  Input: void
//
//  Returns: void
// 
void initBigVirusOnScreen(){
    u8 n;

    for (n=0; n<3; n++){
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
void printBigVirus(TBoard *b){
    u8 n;
    u8 *pvmem;

    for (n=0; n<3; n++){
        if ((b->virList.colorCount[n]>0) != bigVirusOnScreen[n]){
            pvmem = cpct_getScreenPtr(SCR_VMEM, 5+(SP_VIRUSES_BIG_1_W * (n==1)), 100+(SP_VIRUSES_BIG_1_H*n) );
            cpct_drawSpriteBlended(pvmem, SP_VIRUSES_BIG_1_H, SP_VIRUSES_BIG_1_W, (u8*) spritesBigVirus[n]);
            bigVirusOnScreen[n] = (b->virList.colorCount[n]>0);
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
void printScreenSingle(){
    u8 *pvmem;
    u8 i,j;

    clearScreen(BG_COLOR);   // Clear de Screen BGCOLOR=Black
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
    pvmem = cpct_getScreenPtr(SCR_VMEM, 30, 7);
    //cpct_drawSprite(bk_drRonald_0, pvmem, BK_DRRONALD_0_W, BK_DRRONALD_0_H);
  //  cpct_drawSpriteMaskedAlignedTable(bk_drRonald_0, pvmem, BK_DRRONALD_0_W, BK_DRRONALD_0_H, g_tablatrans);
    cpct_drawSpriteMaskedAlignedTable(sp_title, pvmem, SP_TITLE_W, SP_TITLE_H, g_tablatrans);
    
//    pvmem = cpct_getScreenPtr(SCR_VMEM, 53, 7);
    //cpct_drawSprite(bk_drRonald_1, pvmem, BK_DRRONALD_1_W, BK_DRRONALD_1_H);
//    cpct_drawSpriteMaskedAlignedTable(bk_drRonald_1, pvmem, BK_DRRONALD_1_W, BK_DRRONALD_1_H, g_tablatrans);

    // clear game area
    //cpct_waitVSYNC();  // Sync with the raster to avoid flickering
    //drawWindow(board.originX-1,board.originY-5,28,119, 15, 0);

    printScoreBoard1(&board1);
    printScoreBoard2(&board1);

    //drawWindow(57,45,18,27,15,BG_COLOR);
	//drawText("Next", 61, 50,  COLORTXT_RED, NORMALHEIGHT, TRANSPARENT);
    
    pvmem = cpct_getScreenPtr(SCR_VMEM, 64, 86);
    cpct_drawSprite(sp_drroland02, pvmem, SP_DRROLAND02_W, SP_DRROLAND02_H);
    // Big Virus Container
    drawWindow(3,95,21,80, 15, 0);

}




//////////////////////////////////////////////////////////////////
//  animateThrow
//  
//  Input: void
//
//  Returns: void
// 
void animateThrow(TCursor *cur){
    u8 *pvmem;
    u8 n;

    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm02, pvmem, SP_ARM02_W, SP_ARM02_H);
    for (n=0;n<5;n++){
        pvmem = cpct_getScreenPtr(SCR_VMEM, throwCoordsX[n], throwCoordsY[n]);
        cpc_GetSp((u8*) screen_buffer, 7, 6, (int) pvmem);  // Capture screen background
        printCursor2(cur, throwCoordsX[n], throwCoordsY[n]);
        delay(25);
        cpct_drawSprite((u8*) screen_buffer, pvmem, 6, 7); // Screen background restore
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
void printArm01(){
    u8 *pvmem;
    pvmem = cpct_getScreenPtr(SCR_VMEM, 61, 81);
    cpct_drawSprite(sp_arm01, pvmem, SP_ARM01_W, SP_ARM01_H);
}



//////////////////////////////////////////////////////////////////
//  cursorHit
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
    while (clearMatches(b)){
        applyGravity(b);
        printBigVirus(b);
    }   
    
    cur->activePill = NO;
    if (cur->y==0){
        cur->alive = NO;
    } 
}


//////////////////////////////////////////////////////////////////
//  attackFoe
//  
//  Input: void
//
//  Returns: void
// 
void attackFoe(TBoard *b, u8 v){
	u8 x, y;
	u8 color;
	
	do {
		do {
    	    x = (cpct_rand8() % 8);
    	    y = (cpct_rand8() % 6)+10;
		
    	} while (b->content[y][x] != 0);
		color = (cpct_rand8() % 3);
    	b->content[y][x] = 6;  // 6 is Virus order in the content array;
    	b->color[y][x] = color;  // Assign a random color 
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
void cursorHitVs(TBoard *b, TCursor *cur, TBoard *foe){
    b->content[cur->y][cur->x]=cur->content[0];
    b->color[cur->y][cur->x]=cur->color[0];
    // Add position and neg position to change direction vertical & horizaontal
    b->content[cur->y+cur->position][cur->x+(!cur->position)]=cur->content[1];
    b->color[cur->y+cur->position][cur->x+(!cur->position)]=cur->color[1];
    
    // Clear matches until gravity stops
	
    while (clearMatches(b)>0){
		if (b->virusMatched > 1){
			attackFoe(foe, b->virusMatched);
		}
        applyGravity(b);
    }   
    
    cur->activePill = 0;
    if (cur->y==0){
        cur->alive = NO;
    } 
}

//////////////////////////////////////////////////////////////////
//  updatePlayerSingle
//  Updates cursor position based on player's keypresses
//
//  Input: cursor, board & keys
//
//  Returns: void && cursor updated
//    
void updatePlayerSingle(TCursor *cur, TBoard *b, TKeys *k){
    u8 aux;
	
    // Check downwards movement
    if (cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down)){
        if (checkCollisionDown(b, cur) == YES){
				cursorHit(b, cur);
        } else {
            cur->y++;
            cur->moved = YES;
        }
    }
    // Check left movement
    if ((cpct_isKeyPressed(k->left) || cpct_isKeyPressed(k->j_left)) &&  
        (checkCollisionLeft(b, cur) == NO)){
            cur->x--;
            cur->moved = YES;
    // Check right movement    
    } else if ((cpct_isKeyPressed(k->right) || cpct_isKeyPressed(k->j_right)) &&
        (checkCollisionRight(b, cur) == NO)){
            cur->x++;
            cur->moved = YES;
    }

	if (k->fireCooling > 0){
		k->fireCooling--;
	} else {
    	if ((cpct_isKeyPressed(k->up) || cpct_isKeyPressed(k->j_fire1))){ 
    	    //delay(10);
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
			k->fireCooling = FIRE_COOL_TIME;
    	}
	}
//	if (cur->moved){
//		delay(3);
//	}
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
    clearScreen(BG_COLOR);
    initBigVirusOnScreen();
    // Init board
    initBoard(&board1, 30, 76, 14, 19, 74, 179);
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
void initSingleGame(){

// Initial values
level = 1;  
board1.score = 0;
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
            updatePlayerSingle(&activeCursor1, &board1, keys);
            playerLastUpdate = i_time;
        }
		
        // Update active Cursor
		
        if ((i_time - activeCursor1.lastUpdate) > currentSpeed1){
            if (activeCursor1.activePill == NO){
				capsules1++;
                //Update cursor speed
		        if ((currentSpeed1>0) && (speedDelta1 < 25) && ((capsules1 % 5) == 0)){
			        speedDelta1++;
			        if (currentSpeed1 > (speedDelta1 * CAPSULE_STEP)){
                        currentSpeed1 -= (speedDelta1 * CAPSULE_STEP);
                    } else {
                        currentSpeed1 = 0; 
		            }
                }
                cpct_memcpy(&activeCursor1, &nextCursor1, sizeof(TCursor)); // Copy next piece over active
                animateThrow(&nextCursor1);
                initCursor(&nextCursor1, &pillQueueIndex1);
                printArm01();
                printNextCursor(&nextCursor1, PLAYER1);
                printCursor(&board1, &activeCursor1, CURRENT);
                activeCursor1.activePill = YES;
            } else if (checkCollisionDown(&board1, &activeCursor1)){
                cursorHit(&board1, &activeCursor1);    
                } else {
                    activeCursor1.y++;
                    activeCursor1.moved = 1;
                }
        }
        
        // Draw active cursor
        if (activeCursor1.activePill && activeCursor1.moved){
            //cpct_waitVSYNC();
            printCursor(&board1, &activeCursor1, PREVIOUS); // 0 = previous coordinates
            printCursor(&board1, &activeCursor1, CURRENT); // 1 = current coordinates
            activeCursor1.px = activeCursor1.x;
            activeCursor1.py = activeCursor1.y;
            activeCursor1.ppos = activeCursor1.position;
            activeCursor1.pcolor[0] = activeCursor1.color[0];
            activeCursor1.pcolor[1] = activeCursor1.color[1];
            activeCursor1.pcontent[0] = activeCursor1.content[0];
            activeCursor1.pcontent[1] = activeCursor1.content[1];
            activeCursor1.lastUpdate = i_time;
            activeCursor1.moved = 0;
        }
        
        //Animate Virus
        if ((i_time - board1.virList.lastUpdate) > BACT_ANIM_SPEED){
            //cpct_waitVSYNC();
            animateVirusList(&board1);
            board1.virList.lastUpdate = i_time;
        }

        if (board1.virList.count == 0){
	        drawWindow(10,60,60,60,15,8); // 15 = white; 12 green
            sprintf(aux_txt, "Level %d Cleared!!", level);
            drawText(aux_txt, 24, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
            drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
            wait4OneKey();
            level++;
            initSingleLevel();
            activeCursor1.activePill = NO;
            playerLastUpdate = i_time;
            board1.virList.lastUpdate = i_time;
            initCursor(&nextCursor1, &pillQueueIndex1);
        }

    } while (( activeCursor1.alive == YES) && (abortGame == 0));

drawWindow(10,60,60,60,15,14); // 15 = white; 0 blue
drawText("You are dead!!", 26, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
wait4OneKey();
getTopScoreName(keys);
}

/////////////////////////////////////////////////////////////////
//
// Vs Section
//
/////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////
//  updatePlayerVs
//  Updates cursor position based on player's keypresses
//
//  Input: cursor, board & keys
//
//  Returns: void && cursor updated
//    
void updatePlayerVs(TCursor *cur, TBoard *b, TBoard *foe, TKeys *k){
    u8 aux;
	
    // Check downwards movement
    if (cpct_isKeyPressed(k->down) || cpct_isKeyPressed(k->j_down)){
        if (checkCollisionDown(b, cur) == YES){
				cursorHitVs(b, cur, foe);
        } else {
            cur->y++;
            cur->moved = YES;
        }
    }
    // Check left movement
    if ((cpct_isKeyPressed(k->left) || cpct_isKeyPressed(k->j_left)) &&  
        (checkCollisionLeft(b, cur) == NO)){
            cur->x--;
            cur->moved = YES;
    // Check right movement    
    } else if ((cpct_isKeyPressed(k->right) || cpct_isKeyPressed(k->j_right)) &&
        (checkCollisionRight(b, cur) == NO)){
            cur->x++;
            cur->moved = YES;
    }

	if (k->fireCooling > 0){
		k->fireCooling--;
	} else {
    	if ((cpct_isKeyPressed(k->up) || cpct_isKeyPressed(k->j_fire1))){ 
    	    //delay(10);
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
			k->fireCooling = FIRE_COOL_TIME;
    	}
	}
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

    clearScreen(BG_COLOR);   // Clear de Screen BGCOLOR=Black
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
void initVsLevel(){
    clearScreen(BG_COLOR);
    // Init board
    initBoard(&board1, 53, 80, 16, 29, 47, 180);
    initBoard(&board2, 3, 80, 16, 19, 29, 180);
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
//  initVsGame
//  Initializes the game
//
//  Input: void
//
//  Returns: void
//    
void initVsGame(){

// Initial values
level = 1;  
initVsLevel();
}

//////////////////////////////////////////////////////////////////
// playVsGame:		
// 	Main loop of the game
//  Input: void
//
//  Returns: void
//    
void playVsGame(TKeys *keys1, TKeys *keys2)

{
    u32 c = 0;
    u8 pauseGame = 0;
    u8 abortGame = 0;

    c = 0;
    playerLastUpdate = i_time;
	board1.virList.lastUpdate = i_time;
	board2.virList.lastUpdate = i_time;
	initCursor(&activeCursor1, &pillQueueIndex1);
	activeCursor1.activePill = YES;
	printCursor(&board1, &activeCursor1, CURRENT); // 1 = current coordinates
	initCursor(&activeCursor2, &pillQueueIndex2);
	activeCursor2.activePill = YES;
	printCursor(&board2, &activeCursor2, CURRENT); // 1 = current coordinates
	initCursor(&nextCursor1, &pillQueueIndex1);	
    printNextCursor(&nextCursor1, PLAYER1_VS);
	initCursor(&nextCursor2, &pillQueueIndex2);
    printNextCursor(&nextCursor2, PLAYER2_VS);	
	//// Loop forever
	do {
		
	    c++; 
		
	    //Abort Game
	    if (cpct_isKeyPressed(keys1->abort)) {
	        abortGame = 1;
	    }
	    // Pause Game
	    if (cpct_isKeyPressed(keys1->pause)) {
	        pauseGame = 1;
	        waitKeyUp(keys1->pause);
	    }
	    while (pauseGame) {
	        if (cpct_isKeyPressed(keys1->pause)) {
	            pauseGame = 0;
	            waitKeyUp(keys1->pause);
	        }
	    }
	    //Update player
	    if ((i_time - playerLastUpdate) > PLAYER_SPEED){
	        updatePlayerVs(&activeCursor1, &board1, &board2, keys1);
	        updatePlayerVs(&activeCursor2, &board2, &board1, keys2);
	        playerLastUpdate = i_time;
	    }
		
		// Update active Cursor
	    if ((i_time - activeCursor1.lastUpdate) > currentSpeed1){
	        if (activeCursor1.activePill == NO){
				capsules1++;
				//Update cursor1 speed
				if ((currentSpeed1>0) && (speedDelta1 < 25) && ((capsules1 % 5) == 0)){
					speedDelta1++;
					 if (currentSpeed1 > (speedDelta1 * CAPSULE_STEP)){
                        currentSpeed1 -= (speedDelta1 * CAPSULE_STEP);
                    } else {
                        currentSpeed1 = 0; 
		            }
				}
	            cpct_memcpy(&activeCursor1, &nextCursor1, sizeof(TCursor)); // Copy next piece over active
	            initCursor(&nextCursor1, &pillQueueIndex1);
	            printNextCursor(&nextCursor1, PLAYER1_VS);
	            printCursor(&board1, &activeCursor1, CURRENT);
	            activeCursor1.activePill = YES;
	        } else if (checkCollisionDown(&board1, &activeCursor1)){
	            cursorHit(&board1, &activeCursor1);    
	            } else {
	                activeCursor1.y++;
	                activeCursor1.moved = 1;
	            }
		}
		if ((i_time - activeCursor2.lastUpdate) > currentSpeed2){
			if (activeCursor2.activePill == NO){
				capsules2++;
				//Update cursor2 speed
				if ((currentSpeed2>0) && (speedDelta2 < 25) && ((capsules2 % 5) == 0)){
					speedDelta2++;
					 if (currentSpeed2 > (speedDelta2 * CAPSULE_STEP)){
                        currentSpeed2 -= (speedDelta2 * CAPSULE_STEP);
                    } else {
                        currentSpeed2 = 0; 
		            }
				}
	            cpct_memcpy(&activeCursor2, &nextCursor2, sizeof(TCursor)); // Copy next piece over active
	            initCursor(&nextCursor2, &pillQueueIndex2);
	            printNextCursor(&nextCursor2, PLAYER2_VS);
	            printCursor(&board2, &activeCursor2, CURRENT);
	            activeCursor2.activePill = YES;
	        } else if (checkCollisionDown(&board2, &activeCursor2)){
	            cursorHit(&board2, &activeCursor2);    
	            } else {
	                activeCursor2.y++;
	                activeCursor2.moved = 1;
	            }
	    }
	    
	    // Draw active cursor
	    if (activeCursor1.activePill && activeCursor1.moved){
	        printCursor(&board1, &activeCursor1, PREVIOUS); // 0 = previous coordinates
	        printCursor(&board1, &activeCursor1, CURRENT); // 1 = current coordinates
	        activeCursor1.px = activeCursor1.x;
	        activeCursor1.py = activeCursor1.y;
	        activeCursor1.ppos = activeCursor1.position;
	        activeCursor1.pcolor[0] = activeCursor1.color[0];
	        activeCursor1.pcolor[1] = activeCursor1.color[1];
	        activeCursor1.pcontent[0] = activeCursor1.content[0];
	        activeCursor1.pcontent[1] = activeCursor1.content[1];
	        activeCursor1.lastUpdate = i_time;
	        activeCursor1.moved = 0;
	    }
		if (activeCursor2.activePill && activeCursor2.moved){
	        printCursor(&board2, &activeCursor2, PREVIOUS); // 0 = previous coordinates
	        printCursor(&board2, &activeCursor2, CURRENT); // 1 = current coordinates
	        activeCursor2.px = activeCursor2.x;
	        activeCursor2.py = activeCursor2.y;
	        activeCursor2.ppos = activeCursor2.position;
	        activeCursor2.pcolor[0] = activeCursor2.color[0];
	        activeCursor2.pcolor[1] = activeCursor2.color[1];
	        activeCursor2.pcontent[0] = activeCursor2.content[0];
	        activeCursor2.pcontent[1] = activeCursor2.content[1];
	        activeCursor2.lastUpdate = i_time;
	        activeCursor2.moved = 0;
	    }
	    
	    //Animate Virus
	    if ((i_time - board1.virList.lastUpdate) > BACT_ANIM_SPEED){
	        //cpct_waitVSYNC();
	        animateVirusList(&board1);
			animateVirusList(&board2);
	        board1.virList.lastUpdate = i_time;
	    }
	
	    if (board1.virList.count == 0){
	        drawWindow(10,60,60,60,15,8); // 15 = white; 12 green
	        sprintf(aux_txt, "Level %d Cleared!!", level);
	        drawText(aux_txt, 24, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
	        drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
	        wait4OneKey();
	        level++;
	        initVsLevel();
	        activeCursor1.activePill = NO;
	        playerLastUpdate = i_time;
	        board1.virList.lastUpdate = i_time;
	        initCursor(&nextCursor1, &pillQueueIndex1);
	        initCursor(&nextCursor2, &pillQueueIndex2);
	    }
	
	} while ((activeCursor1.alive == YES) && (activeCursor2.alive == YES) && (abortGame == NO));
	
	drawWindow(10,60,60,60,15,14); // 15 = white; 0 blue
	drawText("You are dead!!", 26, 77,  COLORTXT_WHITE, DOUBLEHEIGHT, TRANSPARENT);
	drawText("Press any key to continue", 15, 102,  COLORTXT_YELLOW, NORMALHEIGHT, TRANSPARENT);
	wait4OneKey();
}