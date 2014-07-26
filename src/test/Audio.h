#ifndef AUDIOS_H_
#define AUDIOS_H_

#include <stdint.h>
#include <cstdio>
#include "../atlantis/audio.h"

namespace test {

class Audio: public atlantis::Audio {
public:
	Audio();
	~Audio();
	bool init(long sampleRate);
	void pause();
	void reset();
	void resume();
	void write(uint16_t * finalWave, int length);
	void setThrottle(unsigned short throttle);
private:
	FILE *out;
	long int sampleRate;
	int seekHere;
	long int fileSize;
};

} /* namespace test */

#endif /* AUDIOS_H_ */
