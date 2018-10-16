;//-----------------------------LICENSE NOTICE------------------------------------
;//
;//  /$$$$$$$                /$$$$$$$            /$$                           /$$
;// | $$__  $$              | $$__  $$          | $$                          | $$
;// | $$  \ $$  /$$$$$$     | $$  \ $$  /$$$$$$ | $$  /$$$$$$  /$$$$$$$   /$$$$$$$
;// | $$  | $$ /$$__  $$    | $$$$$$$/ /$$__  $$| $$ |____  $$| $$__  $$ /$$__  $$
;// | $$  | $$| $$  \__/    | $$__  $$| $$  \ $$| $$  /$$$$$$$| $$  \ $$| $$  | $$
;// | $$  | $$| $$          | $$  \ $$| $$  | $$| $$ /$$__  $$| $$  | $$| $$  | $$
;// | $$$$$$$/| $$       /$$| $$  | $$|  $$$$$$/| $$|  $$$$$$$| $$  | $$|  $$$$$$$
;// |_______/ |__/      |__/|__/  |__/ \______/ |__/ \_______/|__/  |__/ \_______/
;//
;//  This program is free software: you can redistribute it and/or modify
;//  it under the terms of the GNU Lesser General Public License as published by
;//  the Free Software Foundation, either version 3 of the License, or
;//  (at your option) any later version.
;//
;//  This program is distributed in the hope that it will be useful,
;//  but WITHOUT ANY WARRANTY; without even the implied warranty of
;//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;//  GNU Lesser General Public License for more details.
;//
;//  You should have received a copy of the GNU Lesser General Public License
;//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
;//------------------------------------------------------------------------------


;*************************************
;;cpc_GetSP
;; 
;;void cpc_GetSp(int *buffer, char height, char width, int *origin)
;; 
;;Captures a screen area starting from origin and sized by width and height and copy it to buffer.
;; 
;;Parameters:
;;buffer: captured data destination.
;;height: capture height.
;;width:  capture width.
;;origin: capture starting address.
;*************************************

.globl _cpc_GetSp
_cpc_GetSp::

	pop af
	
	pop de
	pop bc
	pop hl
	
	push af
	
	ld a,b

	LD (#loop_alto_2x_GetSp0+1),A

	SUB #1
	CPL
	LD (#salto_lineax_GetSp0+1),A    ;comparten los 2 los mismos valores.

	push iy
	call _cpc_GetSp0
	pop iy
	ret

_cpc_GetSp0::
	.DB #0XFD
	LD H,c		;ALTO, SE PUEDE TRABAJAR CON HX DIRECTAMENTE
	LD B,#7
loop_alto_2x_GetSp0:
	LD C,#0
loop_ancho_2x_GetSp0:
	LD A,(HL)
	LD (DE),A
	INC DE
	INC HL
	DEC C
	JP NZ,loop_ancho_2x_GetSp0
	.DB #0XFD
	DEC H
	RET Z
salto_lineax_GetSp0:
	LD C,#0XFF					;salto linea menos ancho
	ADD HL,BC
	JP NC,loop_alto_2x_GetSp0 			;si no desborda va a la siguiente linea
	LD BC,#0XC050
	ADD HL,BC
	LD B,#7						;sólo se daría una de cada 8 veces en un sprite
	JP loop_alto_2x_GetSp0