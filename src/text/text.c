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
#include "../defines.h"
#include "text.h"
#include "../sprites/font_chars.h"

//Font Sprite Size
#define FONT2_W 2
#define FONT2_H 9

u8 const swapColors[6][4] = {
        {0x55, 0xee, 0xdd, 0xff},   // Bright White 
        {0x14, 0x6c, 0x9c, 0x3c},   // Bright Yellow
        {0x50, 0xe4, 0xd8, 0xf0},   // Orange
        {0x11, 0x66, 0x99, 0x33},   // Blue
        {0x10, 0x35, 0x3a, 0x30},   // Bright Red
        {0x45, 0xce, 0xcd, 0xcf}    // Mauve
};


/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char *itoa(int value, char *result, int base)
{

    int tmp_value;
    char *ptr = result, *ptr1 = result, tmp_char;

    // check that the base if valid
    if (base < 2 || base > 36)
    {
        *result = '\0';
        return result;
    }

    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    }
    while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


//////////////////////////////////////////////////////////////////
// strLength
//
//  initializes the whole program
//
// Returns:
//    void
//

u8 strLength(u8 str[]) {
    u8 result;

    result = 0;
    while (str[result] != '\0') {
        result++;
    }
    return result;
}

//////////////////////////////////////////////////////////////////
// strCopy
//
//  initializes the whole program
//
//  Input: str1 string origin, str2 string destiny
//
// Returns:
//    void
//

void strCopy(u8 *str1, u8 *str2){
    u8 i = 0;
    while (str1[i] != '\0'){
        str2[i] = str1[i];
        i++;
    } 
}


//void drawText(u8 text[], u8 xPos, u8 yPos, u8 color, u8 size) {
void drawText(const u8 text[], u8 xPos, u8 yPos, u8 color, u8 size, u8 transparent) {

    u8* pvideo;
    u8* pChar;
    u8 character;
    u8 x = 0; // general purpose.
    u8 i = 0; // chage color bucle.
    u8 color1=0, color2=0, color3=0, color4=0; // Store pair of pixel for print chars in a predefined color.
    u8 colorchar[2 * 9 * 2]; // Store a copy of a char in a specific color. // need double memory for double heigth chars.
    u8 pos; // for precalculated values.

    color1 = swapColors[color][0];
    color2 = swapColors[color][1];
    color3 = swapColors[color][2];
    color4 = swapColors[color][3];

    // String index
    x = 0;
    // Store the caracter.
    character = text[x];

    while (character != '\0') {

        // If a spece or an unsupported char, the left an space.
        if (character != 32) { //32 = SPACE


            // EXCEPTIONS
            switch(character){
                // .
                case 46:
                    character=60;
                    break;

                // ,
                case 44:
                    character=61;
                    break;

                // " --> este caracter no se usa.
                case 34:
                    character=62;
                    break;

                // !
                case 33:
                    character=64;
                    break;

                // (
                case 40:
                    character=91;
                    break;

                // )
                case 41:
                    character=93;
                    break;

                // /
                case 47:
                    character=92;
                    break;
                // &
                case 38:
                    character=94;
                    break;
                // '
                case 39:
                    character=96;
                    break;
            }

            // I apply the offset.
            character-=48;

            // Create a copy of the char in a specific color:
            for(i=0;i<18;i++){
                pChar = (u8*) g_font_chars + (character*18) + i;

                if(size==1) {
                    // NORMAL CHAR
                    if(*pChar == 0x55) colorchar[i]=color1;
                    else if(*pChar == 0xee) colorchar[i]=color2;
                    else if(*pChar == 0xdd) colorchar[i]=color3;
                    else if(*pChar == 0xff) colorchar[i]=color4;
                    else colorchar[i]=*pChar;

                } else {
                    // DOUBLE HEIGHT CHAR

                    pos=(i*size)-(i%FONT2_W);

                    if(*pChar == 0x55) {
                        colorchar[pos]=color1;
                        colorchar[pos+FONT2_W]=color1;
                    }
                    else if(*pChar == 0xee) {
                        colorchar[pos]=color2;
                        colorchar[pos+FONT2_W]=color2;
                    }
                    else if(*pChar == 0xdd) {
                        colorchar[pos]=color3;
                        colorchar[pos+FONT2_W]=color3;
                    }
					else if(*pChar == 0xff) {
                        colorchar[pos]=color4;
                        colorchar[pos+FONT2_W]=color4;
                    }
                    else {
                        colorchar[pos]=*pChar;
                        colorchar[pos+FONT2_W]=*pChar;

                    }

                }

            }

            
            pvideo = cpct_getScreenPtr(CPCT_VMEM_START, xPos, yPos);
            if(transparent) cpct_drawSpriteMaskedAlignedTable(colorchar, pvideo, FONT2_W, FONT2_H*size, g_tablatrans);
            else cpct_drawSprite (colorchar, pvideo, FONT2_W, FONT2_H*size);

            // Correction to support narrow wide, like "i", "l" and "'".
            if(character == 48 || character == 60 || character == 57) xPos--;
            
        }
        character = text[++x];
        xPos+=FONT2_W;
    }
}
