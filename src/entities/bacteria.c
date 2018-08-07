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
#include "../defines.h"
#include "bacteria.h"
#include "board.h"
#include "../game.h"
#include "../keyboard/keyboard.h"

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
    wait4OneKey();
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
void printOneBacteria(TBacteria *bact, u8 step){
    u8 *pvmem;

    // claculate screen adrees for the bacteria
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START,
        BOARD_ORIGIN_X + (bact->x*3), 
        BOARD_ORIGIN_Y + (bact->y*7)
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
void printBacteriaList(TBacteriaList *bactlist){
    u8 i;

    for (i=0;i<20;i++){
        if (bactlist->bacteriaList[i].type){
            printOneBacteria(&bactlist->bacteriaList[i],bactlist->step);    
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
void animateBacteriaList(TBacteriaList *bactlist){
    printBacteriaList(bactlist);
    bactlist->step++;
    printBacteriaList(bactlist);
}