TARGET = File_Downloader
OBJS = main.o setupwifi.o keyboard.o setup.o

INCDIR = 
CFLAGS = -G4 -Wall -O3 -I/usr/local/pspdev/psp/include/SDL
CXXFLAGS = $(CFLAGS)  -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)


PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin

LIBDIR =
LDFLAGS =
STDLIBS= -lSDLmain -lSDL_image -lSDL_ttf -lSDL -lpng -ljpeg -lm -lz -lfreetype -lstdc++ -lcurl -lpsp_req\
		-lpspsdk -lpspctrl  -lpsprtc -lpsppower -lpspgu -lpspaudiolib -lpspaudio -lpsphprm 
LIBS=$(STDLIBS)$(YOURLIBS)


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = File_Downloader
PSP_EBOOT_ICON = ICON0.png
PSP_EBOOT_PIC1 = PIC1.png

PSPSDK=$(shell psp-config --pspsdk-path)
DEFAULT_CFLAGS = $(shell $(SDL_CONFIG) --cflags)
include $(PSPSDK)/lib/build.mak
