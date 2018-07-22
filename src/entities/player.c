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
#include "board.h"
#include "player.h"
#include "../keyboard/keyboard.h"
#include "../game.h"



//////////////////////////////////////////////////////////////////
// movePlayer
//
//  Input:      player: Player to be moved
//              direction: Direction to move Player (0 = left; 1 = down; 2 = right)
//  Returns:    void.
//
void movePlayer(TPlayer *player, u8 direction){
    player->cursor.px = player->cursor.x;
    player->cursor.py = player->cursor.y;
    player->moved = 1;
    if (direction == 0)
        player->cursor.x--;
    else if (direction == 1)
        player->cursor.y++;
    else if (direction == 2)
        player->cursor.x++;
}

//////////////////////////////////////////////////////////////////
// updatePlayer
//
// 
// 
//
// Returns: void.
//
//

void updatePlayer(TBoard *board, TPlayer *player, TKeys *keys){
    // Check downwards movement
    if (cpct_isKeyPressed(keys->down) || cpct_isKeyPressed(Joy0_Down)){
        if (!checkCollisionDown(board, &player->cursor)){
            movePlayer(player, 1); // Move Player down (direction = 1)
        }
    }

    if (cpct_isKeyPressed(keys->left) || cpct_isKeyPressed(Joy0_Left)){

    } else if (cpct_isKeyPressed(keys->right) || cpct_isKeyPressed(Joy0_Right)){
    }
    
}