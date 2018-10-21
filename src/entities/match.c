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
#include "match.h"
//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//
void initMatch(TMatch *m) __z88dk_fastcall
{
    m->x = 255;
    m->y = 255;
    m->direction = 0;
    m->count = 0;
    m->virus = 0;
}

//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//
void initMatchList(TMatchList *l) __z88dk_fastcall
{
    u8 i;
    for (i = 0; i < MAX_MATCH_LIST; i++)
    {
        initMatch(&l->list[i]);
    }
}
ç //////////////////////////////////////////////////////////////////
    // Name
    //
    //    Descriptio
    //
    //
    // Returns:
    //
    void
    addMatch(TMatchList *l, u8 x, u8 y, u8 p, u8 c)
{
    u8 i = 0;
    // search for a free slot
    while (i < MAX_MATCH_LIST)
    {
        if (l->list[i].count == 0)
        {
            i++;
        }
        else
        {
            break;
        }
    }
    // if a free slot was found we store it
    if (i < MAX_MATCH_LIST)
    {
        l->list[i].x = x;
        l->list[i].y = y;
        l->list[i].direction = p;
        l->list[i].count = c;
    }
}
