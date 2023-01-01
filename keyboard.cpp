/*
Osk made by Poison from Xtreamlua.com

This is an open software.

I allow people to change/modify my own
code and to publishe it everywhere.

*/

#include <sstream>
#include <iostream>
#include <string>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <psppower.h>
#include <pspaudio.h>
#include <pspaudiolib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "keyboard.h"

using namespace std;

Osk::Osk()
{
	m_osk_min = IMG_Load("gfx/keyboard/keyboard_min.png");
	m_osk_maj = IMG_Load("gfx/keyboard/keyboard_maj.png");
	m_osk_img = IMG_Load("gfx/keyboard/keyboard_min.png");
	m_osk_selector = IMG_Load("gfx/keyboard/selector_keyboard.png");

	m_osk_position.x = 10;
	m_osk_position.y = 102;
	m_selector_position.x = m_osk_position.x + 2;
	m_selector_position.y = m_osk_position.y + 2;

	m_sentence = "";
	m_alphabet = "012345678abcdefgh9ijklmnop.qrstuvwx_yz -:-+/%";
	m_alphabet_min = "012345678abcdefgh9ijklmnop.qrstuvwx_yz -:-+/%";
	m_alphabet_maj = "012345678ABCDEFGH9IJKLMNOP.QRSTUVWX_YZ -:-+/%";
	m_selector = 0;
	m_choix_letter = 0;
	m_minuscule = 1;
}

void Osk::Init(SceCtrlData *pad, SDL_Surface *ecran, char *phrase, bool *appuis)
{

	// Keep the selector inside the keyboard
	if (m_selector_position.x > m_osk_position.x + 146)
		(m_selector_position.x = m_osk_position.x + 2);
	if (m_selector_position.x < m_osk_position.x + 2)
		(m_selector_position.x = m_osk_position.x + 146);
	if (m_selector_position.y > m_osk_position.y + 54)
		(m_selector_position.y = m_osk_position.y + 2);
	if (m_selector_position.y < m_osk_position.y + 2)
		(m_selector_position.y = m_osk_position.y + 54);

	if (m_selector <= 0)
		(m_selector = 0);

	// Move selector
	if ((pad->Buttons & PSP_CTRL_RIGHT) && ((*appuis) == false))
	{
		(m_selector_position.x += 16);
	}

	if ((pad->Buttons & PSP_CTRL_LEFT) && ((*appuis) == false))
	{
		(m_selector_position.x -= 16);
	}

	if ((pad->Buttons & PSP_CTRL_UP) && ((*appuis) == false))
	{
		(m_selector_position.y -= 13);
	}

	if ((pad->Buttons & PSP_CTRL_DOWN) && ((*appuis) == false))
	{
		m_selector_position.y += 13;
	}

	// Validate the current letter
	if ((pad->Buttons & PSP_CTRL_CROSS) && ((*appuis) == false))
	{
		if (m_choix_letter >= 0)
		{
			m_sentence[m_selector] = m_alphabet[m_choix_letter];
			m_selector++;
			m_sentence[m_selector + 1] = '\0';
		}
		else if (m_choix_letter == -1)
		{
			if (m_minuscule == 1)
			{
				m_osk_img = m_osk_maj;
				m_alphabet = m_alphabet_maj;
				m_minuscule = 0;
			}
			else if (m_minuscule == 0)
			{
				m_osk_img = m_osk_min;
				m_alphabet = m_alphabet_min;
				m_minuscule = 1;
			}
		}
		else if (m_choix_letter == -2)
		{
			m_sentence[m_selector - 1] = '\0';
			m_selector--;
		}
		// Past the m_sentence into phrase
		sprintf(phrase, "%s", m_sentence.c_str());
	}

	if ((pad->Buttons & PSP_CTRL_SQUARE) && ((*appuis) == false))
	{
		m_sentence = "";
	}
	if ((pad->Buttons & PSP_CTRL_TRIANGLE) && ((*appuis) == false))
	{
		m_sentence = "";
	}

	// Each coordinates is linked to a letter :
	if ((m_selector_position.x == m_osk_position.x + 2) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 0);
	else if ((m_selector_position.x == m_osk_position.x + 18) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 1);
	else if ((m_selector_position.x == m_osk_position.x + 34) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 2);
	else if ((m_selector_position.x == m_osk_position.x + 50) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 3);
	else if ((m_selector_position.x == m_osk_position.x + 66) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 4);
	else if ((m_selector_position.x == m_osk_position.x + 82) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 5);
	else if ((m_selector_position.x == m_osk_position.x + 98) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 6);
	else if ((m_selector_position.x == m_osk_position.x + 114) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 7);
	else if ((m_selector_position.x == m_osk_position.x + 130) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 8);
	else if ((m_selector_position.x == m_osk_position.x + 146) && (m_selector_position.y == m_osk_position.y + 2))
		(m_choix_letter = 40);
	else if ((m_selector_position.x == m_osk_position.x + 2) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 9);
	else if ((m_selector_position.x == m_osk_position.x + 18) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 10);
	else if ((m_selector_position.x == m_osk_position.x + 34) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 11);
	else if ((m_selector_position.x == m_osk_position.x + 50) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 12);
	else if ((m_selector_position.x == m_osk_position.x + 66) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 13);
	else if ((m_selector_position.x == m_osk_position.x + 82) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 14);
	else if ((m_selector_position.x == m_osk_position.x + 98) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 15);
	else if ((m_selector_position.x == m_osk_position.x + 114) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 16);
	else if ((m_selector_position.x == m_osk_position.x + 130) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 17);
	else if ((m_selector_position.x == m_osk_position.x + 146) && (m_selector_position.y == m_osk_position.y + 15))
		(m_choix_letter = 41);
	else if ((m_selector_position.x == m_osk_position.x + 2) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 18);
	else if ((m_selector_position.x == m_osk_position.x + 18) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 19);
	else if ((m_selector_position.x == m_osk_position.x + 34) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 20);
	else if ((m_selector_position.x == m_osk_position.x + 50) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 21);
	else if ((m_selector_position.x == m_osk_position.x + 66) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 22);
	else if ((m_selector_position.x == m_osk_position.x + 82) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 23);
	else if ((m_selector_position.x == m_osk_position.x + 98) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 24);
	else if ((m_selector_position.x == m_osk_position.x + 114) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 25);
	else if ((m_selector_position.x == m_osk_position.x + 130) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 26);
	else if ((m_selector_position.x == m_osk_position.x + 146) && (m_selector_position.y == m_osk_position.y + 28))
		(m_choix_letter = 42);
	else if ((m_selector_position.x == m_osk_position.x + 2) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 27);
	else if ((m_selector_position.x == m_osk_position.x + 18) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 28);
	else if ((m_selector_position.x == m_osk_position.x + 34) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 29);
	else if ((m_selector_position.x == m_osk_position.x + 50) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 30);
	else if ((m_selector_position.x == m_osk_position.x + 66) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 31);
	else if ((m_selector_position.x == m_osk_position.x + 82) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 32);
	else if ((m_selector_position.x == m_osk_position.x + 98) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 33);
	else if ((m_selector_position.x == m_osk_position.x + 114) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 34);
	else if ((m_selector_position.x == m_osk_position.x + 130) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 35);
	else if ((m_selector_position.x == m_osk_position.x + 146) && (m_selector_position.y == m_osk_position.y + 41))
		(m_choix_letter = 43);
	else if ((m_selector_position.x == m_osk_position.x + 2) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = 36);
	else if ((m_selector_position.x == m_osk_position.x + 18) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = 37);
	else if ((m_selector_position.x == m_osk_position.x + 34) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = -1);
	else if ((m_selector_position.x == m_osk_position.x + 50) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = 38);
	else if ((m_selector_position.x == m_osk_position.x + 66) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = 38);
	else if ((m_selector_position.x == m_osk_position.x + 82) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = 38);
	else if ((m_selector_position.x == m_osk_position.x + 98) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = -2);
	else if ((m_selector_position.x == m_osk_position.x + 114) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = -2);
	else if ((m_selector_position.x == m_osk_position.x + 130) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = 39);
	else if ((m_selector_position.x == m_osk_position.x + 146) && (m_selector_position.y == m_osk_position.y + 54))
		(m_choix_letter = 44);

	// Allow the user to move the keyboard
	if (pad->Lx > 215)
	{
		m_osk_position.x += 2;
		m_selector_position.x += 2;
	}
	else if (pad->Lx < 100)
	{
		m_osk_position.x -= 2;
		m_selector_position.x -= 2;
	}
	if (pad->Ly > 215)
	{
		m_osk_position.y += 2;
		m_selector_position.y += 2;
	}
	else if (pad->Ly < 100)
	{
		m_osk_position.y -= 2;
		m_selector_position.y -= 2;
	}

	// Print the keyboard and the red square selector on screen
	SDL_BlitSurface(m_osk_img, NULL, ecran, &m_osk_position);
	SDL_BlitSurface(m_osk_selector, NULL, ecran, &m_selector_position);
}
