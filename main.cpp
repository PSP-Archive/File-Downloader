#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsdk.h>
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

#include <setupwifi.h>

#define printf pspDebugScreenPrintf

PSP_MODULE_INFO("File downloader", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

int exit_callback(int arg1, int arg2, void *common);
int CallbackThread(SceSize args, void *argp);
int SetupCallbacks(void);

int main(int argc, char **argv)
{
	SceUID thid;

	SetupCallbacks();

	pspDebugScreenInit();

	//Chargement du Modules inet
	if(pspSdkLoadInetModules() < 0)
	{
		printf("Error, could not load inet modules\n");
		sceKernelSleepThread();
	}

	//Création d'un thread dans lequel on vas "travailler"
	thid = sceKernelCreateThread("net_thread", net_thread, 0x18, 0x10000, PSP_THREAD_ATTR_USER, NULL);
	if(thid < 0)
	{
		printf("Error, could not create thread\n");
		sceKernelSleepThread();
	}
	sceKernelStartThread(thid, 0, NULL);

	sceKernelExitDeleteThread(0);

return 0;
}


































int exit_callback(int arg1, int arg2, void *common)
{
sceKernelExitGame();
return 0;
}

int CallbackThread(SceSize args, void *argp)
{
int cbid;

cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
sceKernelRegisterExitCallback(cbid);
sceKernelSleepThreadCB();

return 0;
}

int SetupCallbacks(void)
{
int thid = 0;

thid = sceKernelCreateThread("update_thread", CallbackThread,
0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);
if(thid >= 0)
{
sceKernelStartThread(thid, 0, 0);
}

return thid;
}
