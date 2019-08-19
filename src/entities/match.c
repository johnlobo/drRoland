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
#include "..//defines.h"
#include "match.h"

//////////////////////////////////////////////////////////////////
//	initMatch
//
//
//
//
//	Returns:
//
void initMatch(TMatch* m)
{
	setMatch(m, PLAYER1, 255, 255, 0, 0, 0, 0);
}

//////////////////////////////////////////////////////////////////
//	setMatch
//
//
//
//
//	Returns:
//
void setMatch(TMatch* m, u8 p, u8 x, u8 y, u8 dir, u8 c, u8 v, u8 step)
{
	m->player = p;
	m->x = x;
	m->y = y;
	m->direction = dir;
	m->count = c;
	m->virus = v;
	m->animStep = step;
}

//////////////////////////////////////////////////////////////////
//	initMatchList
//
// 
//
//
//	Returns:
//
void initMatchList(TMatchList* l)
{
	u8 i;
	for (i = 0; i < MAX_MATCH_LIST; i++)
	{
		initMatch(&l->list[i]);
	}
}
//////////////////////////////////////////////////////////////////
//	addMatch
//
//	
//
//
// Returns:
//
void addMatch(TMatchList* l, TMatch* m)
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
		//l->list[i].player = m->player;
		//l->list[i].x = m->x;
		//l->list[i].y = m->y;
		//l->list[i].direction = m->direction;
		//l->list[i].count = m->count;
		//l->list[i].virus = m->virus;

		setMatch(&l->list[i], m->player, m->x, m->y, m->direction, m->count, m->virus, m->animStep);
		l->count = l->count + 1;
	}
}
