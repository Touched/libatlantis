#ifndef EMULATOR_H_
#define EMULATOR_H_

#include "audio.h"
#include "video.h"
#include "input.h"

namespace atlantis {

/*
 * Abstract base class
 */

class Emulator {
public:

	/*
	 * Return a new video driver
	 */

	//virtual Video *video_driver() = 0;

	/*
	 * Return a new sound driver
	 */

	virtual Audio *sound_driver() = 0;

	/*
	 * Return a new input driver
	 */

	virtual Input *input_driver() = 0;

};

} /* namespace atlantis */

#endif /* EMULATOR_H_ */
