#ifndef ATLANTIS_SOUND_DRIVER_H__
#define ATLANTIS_SOUND_DRIVER_H__

#include <stdint.h>
#include "../common/SoundDriver.h"

namespace atlantis {
/**
 * Sound driver abstract interface for the core to use to output sound.
 * Subclass this to implement a new sound driver.
 */
class Audio: public SoundDriver
{
public:

	/**
	 * Destructor. Free the resources allocated by the sound driver.
	 */
	~Audio() {}

	/**
	 * Initialize the sound driver.
	 * @param sampleRate In Hertz
	 */
	bool init(long sampleRate) { return 0; }

	/**
	 * Tell the driver that the sound stream has paused
	 */
	void pause() {}

	/**
	 * Reset the sound driver
	 */
	void reset() {}

	/**
	 * Tell the driver that the sound stream has resumed
	 */
	void resume() {}

	/**
	 * Write length bytes of data from the finalWave buffer to the driver output buffer.
	 */
	void write(uint16_t * finalWave, int length) {}

	void setThrottle(unsigned short throttle) {}
};

} /* namespace atlantis */

#endif // __ATLANTIS_SOUND_DRIVER_H__
