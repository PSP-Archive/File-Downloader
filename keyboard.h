/*
Osk made by Poison from Xtreamlua.com

This is an open software.

I allow people to change/modify my own 
code and to publishe it everywhere.

*/

#ifndef DEF_KEYBOARD
#define DEF_KEYBOARD

#include <sstream>
#include <string>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <psppower.h>
#include <pspaudio.h>
#include <pspaudiolib.h>

class Osk
{
	public:

	Osk();
	void Init(SceCtrlData *pad, SDL_Surface *ecran, char *phrase, bool *appuis);

	private:

	SDL_Surface *m_osk_min;
	SDL_Surface *m_osk_maj;
	SDL_Surface *m_osk_img;
	SDL_Surface *m_osk_selector;

	SDL_Rect m_osk_position;
	SDL_Rect m_selector_position;
	
	std::string m_sentence;
	std::string m_alphabet;
	std::string m_alphabet_min;
	std::string m_alphabet_maj;
	char m_selector;
	char m_choix_letter;
	char m_appuisCROSS;
	char m_appuisRIGHT;
	char m_appuisLEFT;
	char m_appuisDOWN;
	char m_appuisUP;
	char m_minuscule;

};

#endif
