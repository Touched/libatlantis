#ifndef ATLANTIS_SOUND_DRIVER_H__
#define ATLANTIS_SOUND_DRIVER_H__

#include <stdint.h>

namespace atlantis {
/**
 * Sound driver abstract interface for the core to use to output sound.
 * Subclass this to implement a new sound driver.
 */
class Audio
{
public:

	/**
	 * Destructor. Free the resources allocated by the sound driver.
	 */
	virtual ~Audio() {}

	/**
	 * Initialize the sound driver.
	 * @param sampleRate In Hertz
	 */
	virtual bool init(long sampleRate) = 0;

	/**
	 * Tell the driver that the sound stream has paused
	 */
	virtual void pause() {}

	/**
	 * Reset the sound driver
	 */
	virtual void reset() {}

	/**
	 * Tell the driver that the sound stream has resumed
	 */
	virtual void resume() {}

	/**
	 * Write length bytes of data from the finalWave buffer to the driver output buffer.
	 */
	virtual void write(uint16_t * finalWave, int length) {}

	virtual void setThrottle(unsigned short throttle) {}
};

} /* namespace atlantis */

#endif // __ATLANTIS_SOUND_DRIVER_H__
