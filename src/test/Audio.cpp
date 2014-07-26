#include "Audio.h"

namespace test {

Audio::Audio() {
	// TODO Auto-generated constructor stub
	out = fopen("output.pcm", "wb");
	seekHere = 0;
	sampleRate = 0;
	fileSize = 0;
}

Audio::~Audio() {
	fclose(out);
}

bool Audio::init(long sampleRate) {
	this->sampleRate = sampleRate;
	return true;
}

void Audio::pause() {
}

void Audio::reset() {
}

void Audio::resume() {
}

void Audio::write(uint16_t* finalWave, int length) {
	// finalWave is signed 16 bit, don't know why it's passed as unsigned

	fileSize += length;
	// Outputs as signed 16 bit interlaced stereo PCM data
	//fwrite(finalWave, sizeof(uint16_t), length / 2, out);

	// Output as 32bit float
	uint16_t *ptr = finalWave;
	for (int i = 0; i < length / 2; ++i) {
		// You MUST cast to a unsigned value first!
		float f = ((float) ((int16_t)*ptr++)) / (float) 0x8000;
		//fwrite(&f, sizeof(float), 1, out);
	}

}

void Audio::setThrottle(unsigned short throttle) {
}

} /* namespace test */
