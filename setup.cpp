#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <pspctrl.h>

#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>
#include <pspnet_resolver.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <curl/curl.h>

#include <sstream>
#include <iostream>
#include <string>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "keyboard.h"
#include "setup.h"
#include "setupwifi.h"

#define printf pspDebugScreenPrintf

#define MODULE_NAME "File downloader"

int url_N_output(SceCtrlData *pad, int *continuer, bool *appuis, char *addurl, char *filename)
{

	int step = 1, ouverture = 0;

	// Make a variable Osk (to use the OSK)
	Osk poison;

	FILE *fichier_url;
	TTF_Font *Font = TTF_OpenFont("./Vera.ttf", 10);

	// Set a color (color of your texte)
	SDL_Color couleurBlanche = {255, 255, 255};

	SDL_Surface *ecran = SDL_SetVideoMode(480, 272, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_Surface *background = IMG_Load("gfx/background.png");
	SDL_Surface *credits = IMG_Load("gfx/txt.png");
	SDL_Surface *texte = NULL, *texte2 = NULL, *askin_for_url_txt = TTF_RenderText_Blended(Font, "Enter an url adress :", couleurBlanche), *askin_for_output_file = TTF_RenderText_Blended(Font, " Where do you want to save the file (ex : ./file.txt) ?", couleurBlanche), *pushsquare_txt = TTF_RenderText_Blended(Font, "Push square to continue", couleurBlanche);
	SDL_Surface *triangle_txt = TTF_RenderText_Blended(Font, "Push triangle to load the url that contain the url.ini file", couleurBlanche);

	// Initialisation pictures coordinates
	SDL_Rect background_position;
	background_position.x = 0;
	background_position.y = 0;

	SDL_Rect askin_for_something_position;
	askin_for_something_position.x = 10;
	askin_for_something_position.y = 10;

	SDL_Rect texte_position;
	texte_position.x = 10;
	texte_position.y = 40;

	SDL_Rect pushsquare_txt_position;
	pushsquare_txt_position.x = 10;
	pushsquare_txt_position.y = 175;

	SDL_Rect triangle_txt_position;
	triangle_txt_position.x = 10;
	triangle_txt_position.y = 85;

	do
	{
		sceCtrlReadBufferPositive(pad, 1);

		// Blit a background
		SDL_BlitSurface(background, NULL, ecran, &background_position);

		if (step == 1)
		{
			SDL_BlitSurface(askin_for_url_txt, NULL, ecran, &askin_for_something_position);
			SDL_BlitSurface(pushsquare_txt, NULL, ecran, &pushsquare_txt_position);
			SDL_BlitSurface(triangle_txt, NULL, ecran, &triangle_txt_position);

			// Call the osk
			poison.Init(pad, ecran, addurl, appuis);

			if ((pad->Buttons & PSP_CTRL_TRIANGLE) && ((*appuis) == false) && (ouverture != 1))
			{
				fichier_url = fopen("./url.ini", "r");
				fgets(addurl, 2000, fichier_url);
				fclose(fichier_url);
				ouverture = 1;
			}

			if ((pad->Buttons & PSP_CTRL_CROSS) && ((*appuis) == false) && (ouverture == 1))
			{
				ouverture = 0;
			}

			// Print the text on screen (FreeSurface and load it , this is very IMPORTANT):
			SDL_FreeSurface(texte);
			texte = TTF_RenderText_Blended(Font, addurl, couleurBlanche);
			SDL_BlitSurface(texte, NULL, ecran, &texte_position);
		}
		else if ((step == 2))
		{
			SDL_BlitSurface(askin_for_output_file, NULL, ecran, &askin_for_something_position);
			SDL_BlitSurface(pushsquare_txt, NULL, ecran, &pushsquare_txt_position);
			// Call the osk
			poison.Init(pad, ecran, filename, appuis);

			// Print the text on screen (FreeSurface and load it , this is very IMPORTANT):
			SDL_FreeSurface(texte2);
			texte2 = TTF_RenderText_Blended(Font, filename, couleurBlanche);
			SDL_BlitSurface(texte2, NULL, ecran, &texte_position);
		}
		else if (step == 3)
		{
			(*continuer) = 1;
			sceKernelDelayThread(50 * 1000 * 1);
			SDL_BlitSurface(background, NULL, ecran, &background_position);
			break;
			step = 1;
		}

		if ((pad->Buttons & PSP_CTRL_SQUARE) && (step == 1) && ((*appuis) == false))
		{
			step = 2;
		}
		else if ((pad->Buttons & PSP_CTRL_SQUARE) && (step == 2) && ((*appuis) == false))
		{
			step = 3;
		}

		if (pad->Buttons)
			((*appuis) = true);
		else if (!pad->Buttons)
			((*appuis) = false);

		if (pad->Buttons & PSP_CTRL_HOME)
			(sceKernelExitGame());
		SDL_Flip(ecran);
	} while ((*continuer) == 0);

	SDL_FreeSurface(ecran);
	SDL_FreeSurface(background);
	SDL_FreeSurface(texte);
	SDL_FreeSurface(texte2);
	SDL_FreeSurface(askin_for_output_file);
	SDL_FreeSurface(askin_for_url_txt);
	return 0;
}

int getting_the_file(SceCtrlData *pad, int *continuer, char *addurl, char *filename)
{
	SDL_Surface *ecran = SDL_SetVideoMode(480, 272, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_Surface *background = IMG_Load("gfx/background.png");
	SDL_Surface *credits = IMG_Load("gfx/txt.png");
	SDL_Rect background_position;
	background_position.x = 0;
	background_position.y = 0;

	int err;

	do
	{
		SDL_BlitSurface(background, NULL, ecran, &background_position);
		SDL_BlitSurface(credits, NULL, ecran, &background_position);
		if ((err = pspSdkInetInit()))
		{
			printf(MODULE_NAME ": Error, could not initialise the network %08X\n", err);
			break;
		}

		if (connect_to_apctl(1))
		{
			// Connecté et lance untest d'IP
			// Get the IP address
			SceNetApctlInfo szMyIPAddr;
			if (sceNetApctlGetInfo(8, &szMyIPAddr) != 0)
				strcpy(szMyIPAddr.name, "unknown IP address");

			run_curl_test(addurl, filename);
			printf("\n\nYou can leave the program.");
			break;
		}
	} while ((*continuer) == 1);

	SDL_FreeSurface(ecran);
	SDL_FreeSurface(background);
	return 0;
}
