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
#include "text.h"
#include "../sprites/fonts-small.h"
#include "../sprites/font_chars.h"
#include "../sprites/numbers-small.h"

u8* const font[29] = { g_fonts_small_00, g_fonts_small_01, g_fonts_small_02, g_fonts_small_03, g_fonts_small_04,
                       g_fonts_small_05, g_fonts_small_06, g_fonts_small_07, g_fonts_small_08, g_fonts_small_09,
                       g_fonts_small_10, g_fonts_small_11, g_fonts_small_12, g_fonts_small_13, g_fonts_small_14,
                       g_fonts_small_15, g_fonts_small_16, g_fonts_small_17, g_fonts_small_18, g_fonts_small_19,
                       g_fonts_small_20, g_fonts_small_21, g_fonts_small_22, g_fonts_small_23, g_fonts_small_24,
                       g_fonts_small_25, g_fonts_small_26, g_fonts_small_27, g_fonts_small_28
                     };
u8* const numbers[15] = { g_numbers_small_00, g_numbers_small_01, g_numbers_small_02, g_numbers_small_03, g_numbers_small_04,
                          g_numbers_small_05, g_numbers_small_06, g_numbers_small_07, g_numbers_small_08, g_numbers_small_09,
                          g_numbers_small_10, g_numbers_small_11, g_numbers_small_12, g_numbers_small_13, g_numbers_small_14
                        };

//Font Sprite Size
#define FONT2_W 2
#define FONT2_H 9

u8 const swapColors[6][4] = {
        {0x7f, 0xff, 0xaa, 0x55},   // Bright White
        {0x3e, 0x3c, 0x28, 0x14},   // Bright Yellow
        {0x7a, 0xf0, 0xa0, 0x50},   // Orange
        {0x3b, 0x33, 0x22, 0x11},   // Sky Blue
        {0x3a, 0x30, 0x20, 0x10},   // Bright Red
        {0x7b, 0xF3, 0xA2, 0x51}    // Mauve
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

//////////////////////////////////////////////////////////////////
// drawNumber
//
//  initializes the whole program
//
// Returns:
//    void
//

void drawNumber(i32 aNumber, u8 length, u8 xPos, u8 yPos, u8 delay) {

    u8 str[6];
    u8* pvideo;
    u8 zeros;
    u8 x = 0;
    u8 number;
    
//    cpct_setPalette(sp_palette1, 16); // Palette with transparent sprite active
    
    itoa(aNumber, str, 10);

    zeros = length - strLength(str);

    number = str[x];

    while (number != '\0') {

        pvideo = cpct_getScreenPtr(CPCT_VMEM_START, (zeros + x) * FONT_W + xPos, yPos);
        cpct_drawSpriteMaskedAlignedTable(numbers[number - 44], pvideo, FONT_W, FONT_H, g_tablatrans);
        number = str[++x];
        
        // delay
        if (delay){
            cpct_waitVSYNC ();
            cpct_waitVSYNC ();
        }
    }

//    cpct_setPalette(sp_palette0, 16); // Regular Palette restored
}

//////////////////////////////////////////////////////////////////
// drawText
//
//  initializes the whole program
//
// Returns:
//    void
//

void drawText(u8 text[], u8 xPos, u8 yPos, u8 centered, u8 delay) {

    u8* pvideo;
    u8 character;
    u8 x = 0;

    if (centered) {
        x = strLength(text);
        xPos = 39 - (x / 2) * FONT_W;
    }

//    cpct_setPalette(sp_palette1, 16); // Palette with transparent sprite active
    
    x = 0;
    character = text[x];

    while (character != '\0') {

        pvideo = cpct_getScreenPtr(CPCT_VMEM_START, (x * FONT_W) + xPos, yPos);

        //NUMEROS
        if (character >= 44 && character <= 58) {

            cpct_drawSpriteMaskedAlignedTable(numbers[character - 44], pvideo, FONT_W, FONT_H, g_tablatrans);
        }

        else if (character != 32) { //32 = SPACE

            cpct_drawSpriteMaskedAlignedTable(font[character - 63], pvideo, FONT_W, FONT_H, g_tablatrans);
        }

        character = text[++x];
        
        // delay
        if (delay){
            cpct_waitVSYNC ();
            cpct_waitVSYNC ();
        }
        
    }
    
//    cpct_setPalette(sp_palette0, 16); // Regular Palette restored
}

//void drawText(u8 text[], u8 xPos, u8 yPos, u8 color, u8 size) {
void drawText2(const u8 text[], u8 xPos, u8 yPos, u8 color, u8 size, u8 transparent) {

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
                pChar = g_font_chars + (character*18) + i;

                if(size==1) {
                    // NORMAL CHAR
                    if(*pChar == 0x7f) colorchar[i]=color1;
                    else if(*pChar == 0xff) colorchar[i]=color2;
                    else if(*pChar == 0xaa) colorchar[i]=color3;
                    else if(*pChar == 0x55) colorchar[i]=color4;
                    else colorchar[i]=*pChar;

                } else {
                    // DOUBLE HEIGHT CHAR

                    pos=(i*size)-(i%FONT2_W);

                    if(*pChar == 0x7f) {
                        colorchar[pos]=color1;
                        colorchar[pos+FONT2_W]=color1;
                    }
                    else if(*pChar == 0xff) {
                        colorchar[pos]=color2;
                        colorchar[pos+FONT2_W]=color2;
                    }
                    else if(*pChar == 0xaa) {
                        colorchar[pos]=color3;
                        colorchar[pos+FONT2_W]=color3;
                    }
					else if(*pChar == 0x55) {
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
