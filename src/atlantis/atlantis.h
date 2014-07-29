#ifndef ATLANTIS_H_
#define ATLANTIS_H_

//#include "emulator.h"
#include "callback.h"

//void init(atlantis::Emulator *emu);

int load(const char *szRomPath);

#ifdef __cplusplus
extern "C" {
#endif

void atlantis_load(const char *szRomPath);

void atlantis_finalize();

int atlantis_iteration();

void atlantis_init();

#ifdef __cplusplus
}
#endif

#endif /* ATLANTIS_H_ */
