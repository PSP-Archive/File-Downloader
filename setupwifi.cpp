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
#include <png.h>

#include <sstream>
#include <iostream>
#include <string>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "keyboard.h"
#include "setup.h"

#define printf pspDebugScreenPrintf

#define MODULE_NAME "File downloader"

/* callback pour que curl retourne les données, en gros c'est une fonction qui permet d'ecrire un fichier du net sur la ms */
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int a;

    for (a = 0; a < (size * nmemb); a++)
    {
    }
    return nmemb;
}

/* Utilisation de curl pour obtenir une page */
void run_curl_test(char *addurl, char* filename)
{
	CURL *curl;
	CURLcode res;
	FILE *fichier_downloaded;

	sceKernelDelayThread(1000*1000*1);

	fichier_downloaded = fopen(filename, "w+");
	
	curl = curl_easy_init();
	printf("Downloading in progress...\n");
	if(curl)
	{
		//Mise en place de l'url
		curl_easy_setopt(curl, CURLOPT_URL, addurl);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fichier_downloaded);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_data);

		//Dit a curl d'actualiser la page etc...
		res = curl_easy_perform(curl);

		// Toujours nettoyer
		curl_easy_cleanup(curl);
	}
	fclose(fichier_downloaded);
	sceKernelDelayThread(1000*1000*1);
	printf("Download finished.\n");
}


/* Connection a un point d'acces */
int connect_to_apctl(int config)
{
	int err;
	int stateLast = -1;

	/* Connection utilisant le premier profile */
	err = sceNetApctlConnect(config);
	if (err != 0)
	{
		printf(MODULE_NAME ": sceNetApctlConnect returns %08X\n", err);
		return 0;
	}

	printf(MODULE_NAME ": Connecting to internet...\n\n");
	while (1)
	{
		int state;
		err = sceNetApctlGetState(&state);
		if (err != 0)
		{
			printf(MODULE_NAME ": sceNetApctlGetState returns $%x\n", err);
			break;
		}
		if (state > stateLast)
		{
			printf("  Connexion : %d of 4.\n\n", state);
			stateLast = state;
		}
		if (state == 4)
			break;  // connection avec Ip static

		// Attente
		sceKernelDelayThread(50*1000); // 50ms
	}
	printf(MODULE_NAME ": Connected to internet.\n\n");

	if(err != 0)
	{
		return 0;
	}

	return 1;
}

int net_thread(SceSize args, void *argp)
{

	//Initialisation de la SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init(); 

	char addurl[2000] = "", filename[2000] = "";
	int continuer = 0;
	bool appuis = false;

	SceCtrlData pad;

	url_N_output(&pad, &continuer, &appuis, addurl, filename);

	getting_the_file(&pad, &continuer, addurl, filename);

SDL_Quit();
TTF_Quit();
return 0;
}
