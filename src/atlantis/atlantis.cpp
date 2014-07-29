#include "version.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cmath>

#include <time.h>

#include "../AutoBuild.h"

#include "emulator.h"
#include "logger.h"
#include "audio.h"
#include "signals.h"

#include "../common/Patch.h"
#include "../gba/GBA.h"
#include "../gba/agbprint.h"
#include "../gba/Flash.h"
#include "../gba/Cheats.h"
#include "../gba/RTC.h"
#include "../gba/Sound.h"
#include "../gb/gb.h"
#include "../gb/gbGlobals.h"
#include "../gb/gbCheats.h"
#include "../gb/gbSound.h"
#include "../Util.h"

extern void remoteInit();
extern void remoteCleanUp();
extern void remoteStubMain();
extern void remoteStubSignal(int, int);
extern void remoteOutput(const char *, uint32_t);
extern void remoteSetProtocol(int);
extern void remoteSetPort(int);

// Atlantis global
atlantis::Emulator* atlantis_emulator = NULL;

int autoFireMaxCount = 1;

struct EmulatedSystem emulator = { NULL };

int systemSpeed = 0;
int systemRedShift = 0;
int systemBlueShift = 0;
int systemGreenShift = 0;
int systemColorDepth = 0;
int systemDebug = 0;
int systemVerbose = 0;
int systemFrameSkip = 0;
int systemSaveUpdateCounter = SYSTEM_SAVE_NOT_UPDATED;

int srcPitch = 0;
int srcWidth = 0;
int srcHeight = 0;
int desktopWidth = 0;
int desktopHeight = 0;

uint8_t *delta = NULL;
static const int delta_size = 322 * 242 * 4;

int filter_enlarge = 1;

int PrintUsage = 0;

int cartridgeType = 3;
int captureFormat = 0;

int openGL = 0;
int textureSize = 256;
uint8_t *filterPix = 0;

int pauseWhenInactive = 0;
int active = 1;
int emulating = 0;
int RGB_LOW_BITS_MASK = 0x821;
uint32_t systemColorMap32[0x10000];
uint16_t systemColorMap16[0x10000];
uint16_t systemGbPalette[24];
char filename[2048];
char biosFileName[2048];
char gbBiosFileName[2048];
char captureDir[2048];
char saveDir[2048];
char batteryDir[2048];
char* homeDir = NULL;

// Directory within homedir to use for default save location.
#define DOT_DIR ".vbam"

extern int autoFireMaxCount;

#define REWIND_NUM 8
#define REWIND_SIZE 400000
#define SYSMSG_BUFFER_SIZE 1024

#define _stricmp strcasecmp

bool wasPaused = false;
int autoFrameSkip = 0;
int frameskipadjust = 0;
int showRenderedFrames = 0;
int renderedFrames = 0;

uint32_t throttleLastTime = 0;
uint32_t autoFrameSkipLastTime = 0;

int showSpeed = 1;
int showSpeedTransparent = 1;
bool disableStatusMessages = false;
bool paused = false;
bool pauseNextFrame = false;
bool debugger = false;
bool debuggerStub = false;
int fullscreen = 0;
int FlashSize = 0;
int AutoPatch = 1;
int RtcEnable = 0;
int AgbPrint = 0;
int MirroringEnable = 0;

/* forward */
void systemConsoleMessage(const char*);

void debuggerMain() {
}
void debuggerSignal(int sig, int number) {
}
void debuggerOutput(const char *s, uint32_t addr) {
}
void debuggerBreakOnWrite(uint32_t address, uint32_t oldvalue, uint32_t value,
		int size, int t) {
}

void (*dbgMain)() = debuggerMain;
void (*dbgSignal)(int, int) = debuggerSignal;
void (*dbgOutput)(const char *, uint32_t) = debuggerOutput;

int mouseCounter = 0;

bool screenMessage = false;
char screenMessageBuffer[21];
uint32_t screenMessageTime = 0;

char *arg0;

int PreparedCheats = 0;
#define MAX_CHEATS 100
const char * PreparedCheatCodes[MAX_CHEATS];

#define _SOUND_MAX_VOLUME 2.0
#define _SOUND_ECHO       0.2
#define _SOUND_STEREO     0.15

bool writeSaveState(char *szFilename) {
	if (emulator.emuWriteState)
		return emulator.emuWriteState(szFilename);
	return false;
}

bool readSaveState(char *szFilename) {
	if (emulator.emuReadState)
		return emulator.emuReadState(szFilename);
	return false;
}

bool writeBattery(char *szFilename) {
	return emulator.emuWriteBattery(szFilename);
}

bool readBattery(char *szFilename) {
	return emulator.emuReadBattery(szFilename);
}

bool screenshotBitmap(char *szFilename) {
	return emulator.emuWriteBMP(szFilename);
}

bool screenshotPNG(char *szFilename) {
	return emulator.emuWritePNG(szFilename);
}

void initVideo() {
	// Set the size of the output buffer
	//atlantis_emulator->video_driver()->resize(srcWidth, srcHeight);

	int flags;
	int screenWidth;
	int screenHeight;

	filter_enlarge = 1;

	srcWidth = filter_enlarge * srcWidth;
	srcHeight = filter_enlarge * srcHeight;

	screenWidth = srcWidth;
	screenHeight = srcHeight;

	// 5 is the bit depth of the GBA, 32 is the bit depth of RGBA
	systemRedShift = 27; //32 - 5
	systemGreenShift = 19; // 24 - 5
	systemBlueShift = 11; // 16 - 5

	systemColorDepth = 32;
	srcPitch = srcWidth * 4 + 4;
}

void event_loop() {
}

// Set the global variable
void init(atlantis::Emulator *emu) {
	atlantis_emulator = emu;
}

void init() {
	systemSaveUpdateCounter = SYSTEM_SAVE_NOT_UPDATED;

	//arg0 = argv[0];

	captureDir[0] = 0;
	saveDir[0] = 0;
	batteryDir[0] = 0;

	int op = -1;

	frameSkip = 2;
	gbBorderOn = 0;

	parseDebug = true;

	gb_effects_config.stereo = 0.0;
	gb_effects_config.echo = 0.0;
	gb_effects_config.surround = false;
	gb_effects_config.enabled = false;

	char buf[1024];
	struct stat s;

	//ReadPreferences();

	if (FlashSize == 0)
		flashSetSize(0x10000);
	else
		flashSetSize(0x20000);

	rtcEnable(RtcEnable ? true : false);
	agbPrintEnable(AgbPrint ? true : false);

//	if (!debuggerStub) {
//		if (optind >= argc) {
//			systemMessage(0, "Missing image name");
//			exit(-1);
//		}
//	}

	for (int i = 0; i < 24;) {
		systemGbPalette[i++] = (0x1f) | (0x1f << 5) | (0x1f << 10);
		systemGbPalette[i++] = (0x15) | (0x15 << 5) | (0x15 << 10);
		systemGbPalette[i++] = (0x0c) | (0x0c << 5) | (0x0c << 10);
		systemGbPalette[i++] = 0;
	}
	soundInit();
}

void load(const char *szRomPath) {
	bool failed = false;

	IMAGE_TYPE type = utilFindType(szRomPath);

	if (type == IMAGE_UNKNOWN) {
		systemMessage(0, "Unknown file type %s", szRomPath);
		exit(-1);
	}
	cartridgeType = (int) type;

	if (type == IMAGE_GB) {
		failed = !gbLoadRom(szRomPath);
		if (!failed) {
			gbGetHardwareType();
			atlantis_signal_gb_load();

			// used for the handling of the gb Boot Rom
			if (gbHardware & 5)
				gbCPUInit(gbBiosFileName, useBios);

			cartridgeType = IMAGE_GB;
			emulator = GBSystem;
			gbReset();
		}
	} else if (type == IMAGE_GBA) {
		int size = CPULoadRom(szRomPath);
		failed = (size == 0);
		if (!failed) {
			atlantis_signal_gba_load();

			doMirroring(mirroringEnable);

			cartridgeType = 0;
			emulator = GBASystem;

			CPUInit(biosFileName, useBios);
			CPUReset();
		}
	}

	if (failed) {
		systemMessage(0, "Failed to load file %s", szRomPath);
		exit(-1);
	}

	atlantis_signal_startup();

	if (debuggerStub)
		remoteInit();

	if (cartridgeType == 0) {
		srcWidth = 240;
		srcHeight = 160;
		systemFrameSkip = frameSkip;
	} else if (cartridgeType == 1) {
		if (gbBorderOn) {
			srcWidth = 256;
			srcHeight = 224;
			gbBorderLineSkip = 256;
			gbBorderColumnSkip = 48;
			gbBorderRowSkip = 40;
		} else {
			srcWidth = 160;
			srcHeight = 144;
			gbBorderLineSkip = 160;
			gbBorderColumnSkip = 0;
			gbBorderRowSkip = 0;
		}
		systemFrameSkip = gbFrameSkip;
	} else {
		srcWidth = 320;
		srcHeight = 240;
	}
	initVideo();

	if (systemColorDepth == 15)
		systemColorDepth = 16;

	if (systemColorDepth != 16 && systemColorDepth != 24
			&& systemColorDepth != 32) {
		fprintf(stderr,
				"Unsupported color depth '%d'.\nOnly 16, 24 and 32 bit color depths are supported\n",
				systemColorDepth);
		exit(-1);
	}

	utilUpdateSystemColorMaps();

	if (delta == NULL) {
		delta = (uint8_t*) malloc(delta_size);
		memset(delta, 255, delta_size);
	}

	emulating = 1;
	renderedFrames = 0;

	autoFrameSkipLastTime = throttleLastTime = systemGetClock();

	// now we can enable cheats?
	{
		int i;
		for (i = 0; i < PreparedCheats; i++) {
			const char * p;
			int l;
			p = PreparedCheatCodes[i];
			l = strlen(p);
			if (l == 17 && p[8] == ':') {
				fprintf(stdout, "Adding cheat code %s\n", p);
				cheatsAddCheatCode(p, p);
			} else if (l == 13 && p[8] == ' ') {
				fprintf(stdout, "Adding CBA cheat code %s\n", p);
				cheatsAddCBACode(p, p);
			} else if (l == 8) {
				fprintf(stdout, "Adding GB(GS) cheat code %s\n", p);
				gbAddGsCheat(p, p);
			} else {
				fprintf(stderr, "Unknown format for cheat code %s\n", p);
			}
		}
	}
}

int iteration() {
	if (emulating) {

		if (!paused && active) {
			if (debugger && emulator.emuHasDebugger)
				dbgMain();
			else {
				emulator.emuMain(emulator.emuCount);
			}
		} else {
			sleep(1);
		}
		event_loop();
		return 0;
	}
	return 1;
}

void finalize() {
	emulating = 0;
	remoteCleanUp();
	soundShutdown();

	if (gbRom != NULL || rom != NULL) {
		atlantis_signal_shutdown();
		emulator.emuCleanUp();
	}

	if (delta) {
		free(delta);
		delta = NULL;
	}

	if (filterPix) {
		free(filterPix);
		filterPix = NULL;
	}
}

extern "C" {
void atlantis_load(const char *szRomPath) {
	load(szRomPath);
}

void atlantis_finalize() {
	finalize();
}

int atlantis_iteration() {
	return iteration();
}

void atlantis_init() {
	init();
}
}

void systemMessage(int num, const char *msg, ...) {

	va_list valist;
	va_start(valist, msg);
	vprintf(msg, valist);
	atlantis_logger_system(num, msg, valist);
	va_end(valist);
}

void drawSpeed(uint8_t *screen, int pitch, int x, int y) {
	atlantis_logger_speed(systemSpeed, systemFrameSkip, renderedFrames);
}

void systemDrawScreen() {
	unsigned int destPitch = srcWidth * (systemColorDepth >> 3);
	uint8_t *screen;

	renderedFrames++;

	// Skip the first blank line by adjusting the screen pointer
	uint32_t *pixels = (uint32_t*) (pix + 4 * (srcWidth + 1));

	uint32_t *output = (uint32_t*) malloc(
			srcWidth * srcHeight * sizeof(uint32_t));
	uint32_t *ptr = output;
	for (int y = 0; y < srcHeight; y++) {
		for (int x = 0; x < srcWidth; x++) {
			uint32_t pixel = *pixels++;

			/*
			 * Shift left 3, as each value occupies 5 bits on GBA 16 bit, but 8
			 * in 24 bit/32 bit truecolor.
			 */

			// 11 = 16 - 5, 19 = 24, 5, 27 = 32 - 5
			uint8_t r = ((pixel >> 11) & 0x1f) << 3; // R
			uint8_t g = ((pixel >> 19) & 0x1f) << 3; // G
			uint8_t b = ((pixel >> 27) & 0x1f) << 3; // B

			*output++ = (r << 24) | (g << 16) | (b << 8);
		}
		// Fix skew (there is a blank pixel at the end of each row)
		pixels++;
	}

	atlantis_video_frame(ptr, srcWidth, srcHeight);
}

void systemSetTitle(const char *title) {
	atlantis_logger_window_title(title);
}

void systemScreenCapture(int i) {

}

void systemShowSpeed(int speed) {
	systemSpeed = speed;

	showRenderedFrames = renderedFrames;
	renderedFrames = 0;
}

void systemFrame() {
}

void system10Frames(int rate) {
	// Auto adjust frame skip

	uint32_t time = systemGetClock();
	if (!wasPaused && autoFrameSkip) {
		uint32_t diff = time - autoFrameSkipLastTime;
		int speed = 100;

		if (diff)
			speed = (1000000 / rate) / diff;

		if (speed >= 98) {
			frameskipadjust++;

			if (frameskipadjust >= 3) {
				frameskipadjust = 0;
				if (systemFrameSkip > 0)
					systemFrameSkip--;
			}
		} else {
			if (speed < 80)
				frameskipadjust -= (90 - speed) / 5;
			else if (systemFrameSkip < 9)
				frameskipadjust--;

			if (frameskipadjust <= -2) {
				frameskipadjust += 2;
				if (systemFrameSkip < 9)
					systemFrameSkip++;
			}
		}
	}

	atlantis_signal_autosave();

	wasPaused = false;
	autoFrameSkipLastTime = time;
}

uint32_t systemGetClock() {
	// TODO: Return a value in milliseconds
	// This is for timing functions
	return time(NULL) * 1000;
}

void systemGbPrint(uint8_t *data, int len, int pages, int feed, int palette,
		int contrast) {
}

void systemConsoleMessage(const char *msg) {
	printf("%s\n", msg);
	atlantis_logger_console(msg);
}

void systemScreenMessage(const char *msg) {
	printf("%s\n", msg);
	atlantis_logger_screen(msg);
}

bool systemCanChangeSoundQuality() {
	return false;
}

bool systemPauseOnFrame() {
	if (pauseNextFrame) {
		paused = true;
		pauseNextFrame = false;
		return true;
	}
	return false;
}

void systemGbBorderOn() {
	srcWidth = 256;
	srcHeight = 224;
	gbBorderLineSkip = 256;
	gbBorderColumnSkip = 48;
	gbBorderRowSkip = 40;

	initVideo();
}

bool systemReadJoypads() {
	//return atlantis_emulator->input_driver()->canRead();
	return true;
}

uint32_t systemReadJoypad(int which) {
	if (which == -1) {
		//return atlantis_emulator->input_driver()->getDefault()->getState();
		return 0;
	} else {
		//return atlantis_emulator->input_driver()->getPad(which)->getState();
		return 0;
	}
}

void systemUpdateMotionSensor() {
	// Executed every frame. Used emulate an accelerometer with arrow keys
}

int systemGetSensorX() {
	/* Original values
	 * 2197 - max
	 * 2047 - mid
	 * 1897 - min
	 */

	return 2047;
}

int systemGetSensorY() {
	/* Original values
	 * 2197 - max
	 * 2047 - mid
	 * 1897 - min
	 */

	return 2047;
}

#include "../common/SoundSDL.h"

SoundDriver * systemSoundInit() {
	soundShutdown();
	//return (SoundDriver*) (atlantis_emulator->sound_driver());
	//return NULL;
	//return new atlantis::Audio();
	return new SoundSDL();
}

void systemOnSoundShutdown() {
}

void systemOnWriteDataToSoundBuffer(const uint16_t * finalWave, int length) {
}

void log(const char *defaultMsg, ...) {
	printf("%s\n", defaultMsg);
	va_list valist;
	va_start(valist, defaultMsg);
	atlantis_logger_format(defaultMsg, valist);
	va_end(valist);
}
