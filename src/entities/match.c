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
#include "match.h"

void initMatch(TMatch *m){
    m->x = 255;
    m->y = 255;
    m->direction = 0;
    m->count = 0;
}

void initMatchList(TMatchList *l){
    u8 i;
    for (i=0;i < MAX_MATCH_LIST; i++){
        initMatch(&l->list[i]);
    }
}
void addMatch(TMatchList *l, u8 x, u8 y, u8 p, u8 c){
    u8 i = 0;
    // search for a free slot
    while (i<MAX_MATCH_LIST){
        if (l->list[i].count == 0){
            i++;
        } else{
            break;
        }
    }
    // if a free slot was found we store it
    if (i<MAX_MATCH_LIST){
        l->list[i].x = x;
        l->list[i].y = y;
        l->list[i].direction = p;
        l->list[i].count = c;
    }
}
