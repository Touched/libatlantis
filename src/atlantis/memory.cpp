//extern u8 *bios;
//extern u8 *rom;
//extern u8 *internalRAM;
//extern u8 *workRAM;
//extern u8 *paletteRAM;
//extern u8 *vram;
//extern u8 *pix;
//extern u8 *oam;
//extern u8 *ioMem;

#include "../gba/Globals.h"

extern "C" {
	char *pMemBios = (char*)bios;
	char *pMemRom = (char*)rom;
	char *pMemIRam = (char*)internalRAM;
	char *pMemWRam = (char*)workRAM;
	char *pMemPal = (char*)paletteRAM;
	char *pMemVRam = (char*)vram;
	char *pMemOAM = (char*)oam;
	char *pMemIO = (char*)ioMem;
}
