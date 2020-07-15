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

#include "../defines.h"
#include "keyboard.h"
//#include "../text/text.h"

const TKeys keysSINGLE = {Key_Q, Key_A, Key_O, Key_P, Key_Space, Key_Enter,
                         Joy0_Up, Joy0_Down, Joy0_Left, Joy0_Right, Joy0_Fire1, Joy0_Fire2,
                         Key_H, Key_Esc, Key_M, 0};
const TKeys keys1VS = {Key_I, Key_K, Key_J, Key_L, Key_U, Key_O,
                         Joy0_Up, Joy0_Down, Joy0_Left, Joy0_Right, Joy0_Fire1, Joy0_Fire2,
                         Key_H, Key_Esc, Key_M, 0};
const TKeys keys2VS = {Key_W, Key_S, Key_A, Key_D, Key_Q, Key_E,
                         Joy1_Up, Joy1_Down, Joy1_Left, Joy1_Right, Joy1_Fire1, Joy1_Fire2,
                         Key_H, Key_Esc, Key_M, 0};

//////////////////////////////////////////////////////////////////
// initKeys
//    Initializes the keys
//
//
// Returns:
//    <u32> Number of iterations passed
//
void initKeys(u8 type)
{   
    if (type == SINGLE){
        cpct_memcpy(&keys1, &keysSINGLE, sizeof(TKeys));
    } else {
        cpct_memcpy(&keys1, &keys1VS, sizeof(TKeys));
        cpct_memcpy(&keys2, &keys2VS, sizeof(TKeys));
    }
}


//////////////////////////////////////////////////////////////////
// wait4OneKey
//    Waits till the user presses a key, and waits until no other key is pressed
//
//
// Returns:
//    void
//
void wait4OneKey()
{
	// wait for any previous key presses to clear first
	while (cpct_isAnyKeyPressed());

	//then wait for any key press
	while (!cpct_isAnyKeyPressed());

    return;
}

//////////////////////////////////////////////////////////////////
// wait4UserKeypress
//    Waits till the user presses a key, counting the number of
// loop iterations passed.
//
// Returns:
//    <u32> Number of iterations passed
//
u32 wait4UserKeypress()
{
    u32 c = 0; // Count the number of cycles passed till user k

    // Wait 'till the user presses a key, counting loop iterations
    do
    {
        c++;                   // One more cycle
        cpct_scanKeyboard_f(); // Scan the scan the keyboard
    } while (!cpct_isAnyKeyPressed_f());

    return c;
}

//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//
void waitKeyUp(cpct_keyID key) 
{

    while (cpct_isKeyPressed(key))
    {
        cpct_scanKeyboard_f();
    }
}
