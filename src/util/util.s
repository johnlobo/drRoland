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
; RESET
;*************************************

.globl _reset_cpc
_reset_cpc::
	call #0000
	ret


;*************************************
; FAST ABS
;
; Returns the absolute value of a given u1 number
;*************************************

.globl _fast_abs
_fast_abs::
     bit 7,h
     ret z
     xor a 
     sub l  
     ld l,a
     sbc a,a  
     sub h  
     ld h,a
     ret

;******************************
; 	unsigned char fastCollision(unsigned char x1,unsigned char y1,unsigned char w1,unsigned char h1,unsigned char x2,unsigned char y2,unsigned char w2,unsigned char h2){
; 	Descripción:	Devuelve 1 si se ha producido una colisión y 0 en caso contrario
;	Entrada:	- Coordenada x objeto 1
;				- Coordenada y objeto 1
;				- Ancho objeto 1
;				- Alto objeto 1
;				- Coordenada x objeto 1
;				- Coordenada y objeto 1
;				- Ancho objeto 1
;				- Alto objeto 1
;	Salida:		- HL = 1 si se ha producido una colisión, HL = 0 en caso contrario
;	Modificados: 
;
; @ 
;******************************
.globl _fast_collision
_fast_collision::	

	push ix

;	ld ix,#2
	ld ix,#4
	add ix,sp
	
	ld a,0 (ix)				;recupero la coordenada x1
	ld h,a
	ld a,2 (ix)				;recupero el ancho 1
	add a,h
	ld l,a
	ld a,4 (ix)				;recupero la coordenada x2
	ld b,a
	ld a,6 (ix)				;recupero el ancho 2
	add a,b
	ld c,a
	call #solseg
	jr nc, no_choca
	ld a,1 (ix)				;recupero la coordenada y1
	ld h,a
	ld a,3 (ix)				;recupero el alto 1
	add a,h
	ld l,a
	ld a,5 (ix)				;recupero la coordenada y2
	ld b,a
	ld a,7 (ix)				;recupero el alto 2
	add a,b
	ld c,a
	call #solseg
	jr nc, no_choca
	ld h,#0
	ld l,#1

	pop ix

	ret
no_choca:
	ld h,#0
	ld l,#0

	pop ix

	ret

solseg:
	ld a,c					;solapamaiento
	cp h
	jr c, #solseg1			;no hay colisión continua
	ld a,l
	cp b
solseg1:
	ccf						;complemento carry
	ret
