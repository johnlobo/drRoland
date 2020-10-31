//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of Throne Legacy
//  Copyright (C) 2020 Arnaud Bouche (@Arnaud6128)
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
//-------------------------------------------------------------------------------

/*************** System includes ***************/
#include <cpctelera.h>

/*************** Sound includes ****************/
#include "sound.h"

/********** Current song & Fx played ***********/
volatile void* _selMusic;
volatile void* _currentMusic;
volatile u8 _currentFx;

/*************** Song & Fx *********************/
extern void* FEVERREMIX_START;
extern void* FX_SOUNDEFFECTS;

/*****************************************************/
/*													 */
/*	Init SFX							 			 */
/*												     */
/*****************************************************/
void InitSFX(void* sfx_SoundEffects)
{

   PLY_AKM_INITSOUNDEFFECTS(sfx_SoundEffects);
   _currentFx = NO_FX;
}

/*****************************************************/
/*													 */
/*	Play SFX							 			 */
/*												     */
/*****************************************************/
void PlaySFX(u8 fx)
{
   _currentFx = fx;
}

/*****************************************************/
/*													 */
/*	Init SFX							 			 */
/*												     */
/*****************************************************/
void ActivateSFX()
{
   if (_currentFx != NO_FX)
   {
      PLY_AKM_PLAYSOUNDEFFECT(_currentFx, CHANNEL_C, 0);
      _currentFx = NO_FX;
   }
}

/*****************************************************/
/*													 */
/*	Select new music					 			 */
/*												     */
/*****************************************************/
void InitMusic(void* music)
{
   _selMusic = music;
}

/*****************************************************/
/*													 */
/*	Activate music					 				 */
/*												     */
/*****************************************************/
void ActivateMusic()
{
   if (_currentMusic != _selMusic)
   {
      _currentMusic = _selMusic;
      PLY_AKM_INIT(_currentMusic, 0);
   }
}

/*****************************************************/
/*													 */
/*	Play sound						 				 */
/*												     */
/*****************************************************/
void PlaySound()
{
   ActivateMusic();
   ActivateSFX();
__asm
     ;; Save registers before calling PLY_AKM_PLAY     
      exx
      ex af',af
      push af
      push bc
      push de
      push hl

      call _PLY_AKM_PLAY

    ;; Revert back registers after calling
      pop hl
      pop de
      pop bc
      pop af
      ex af',af
      exx
__endasm;
   //PLY_AKM_PLAY();
}

/*****************************************************/
/*													 */
/*	Init sound						 				 */
/*												     */
/*****************************************************/
void InitSound()
{
   InitSFX(&FX_SOUNDEFFECTS);
   InitMusic(&FEVERREMIX_START);
}