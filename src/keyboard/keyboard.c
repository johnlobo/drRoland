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

#include "../defines.h"
#include "keyboard.h"
//#include "../text/text.h"


const TKeys tempKeys = {    Key_CursorUp, Key_CursorDown, Key_CursorLeft, Key_CursorRight,
                            Key_Space, Key_Return, Key_H, Key_Esc, Key_M
                       };

//////////////////////////////////////////////////////////////////
// initKeys
//    Initializes the keys
// 
//
// Returns:
//    <u32> Number of iterations passed
//
void initKeys(){
    cpct_memcpy(&keys, &tempKeys, sizeof(TKeys));
}

//////////////////////////////////////////////////////////////////
// wait4OneKey
//    Waits till the user presses a key, and waits until no other key is pressed
// 
//
// Returns:
//    void
//
void wait4OneKey() {
    u16 keypressed; //Key that has been pressed

    // Wait until user presses a key
    
    keypressed = waitForAKey();
    waitKeyUp(keypressed);
    
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
u32 wait4UserKeypress() {
    u32 c = 0;     // Count the number of cycles passed till user k

    // Wait 'till the user presses a key, counting loop iterations
    do {
        c++;                       // One more cycle
        cpct_scanKeyboard_f();     // Scan the scan the keyboard
    } while ( ! cpct_isAnyKeyPressed_f() );

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
//Función proporcionada por ronaldo para redefinición de teclas
cpct_keyID waitForAKey() {
    // Recorreremos el vector de teclas desde el final hacia el principio,
    // para poder hacer que el bucle acabe en 0 (así el compilador podrá optimizarlo)
    u8 i = 10, *keys = cpct_keyboardStatusBuffer + 9;
    u16 keypressed;

    // Esperamos hasta que se pulse una tecla
    do { cpct_scanKeyboard(); } while ( ! cpct_isAnyKeyPressed() );

    // Detectamos cuál tecla ha sido pulsada
    do {
        // Si en este grupo de 8 teclas hay una pulsada, alguno de los bits estará a 0
        // En caso contrario, todos estarán a 1, y un XOR con 0xFF dará 0 (false) como resultado
        keypressed = *keys ^ 0xFF;
        if (keypressed)
            return (keypressed << 8) + (i - 1);  // Formato cpct_keyID: 8 primeros bits = máscara de tecla, 8 siguientes fila del teclado (0-9)
        keys--;
    } while (--i);
    return (keypressed << 8) + (i - 1);
}



//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//    

u8 checkKeys(const cpct_keyID *k, u8 numk)
{
    u8 i;
    //   cpct_scanKeyboard_if();
    if (cpct_isAnyKeyPressed())
    {
        for (i = 1; i <= numk; i++, k++)
        {
            if (cpct_isKeyPressed(*k))
                return i;
        }
    }
    return 0;
}
//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//    
void waitKeyUp(cpct_keyID key){

    while (cpct_isKeyPressed(key)) {
        cpct_scanKeyboard_f();
    }
}
//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//    
u32 wait4Key(cpct_keyID key) {

	u32 c = 0;

	while(!cpct_isKeyPressed(key));
    do{
    	c++;
    }
    while(cpct_isKeyPressed(key));

    return c;
}
