#ifndef ATLANTIS_VIDEO_H_
#define ATLANTIS_VIDEO_H_

#include <stdint.h>

namespace atlantis {

/*
 * Abstract base class for implementing a video driver. Subclass this to
 * implement your own.
 */

class Video {
public:
	/*
	 * The output area has requested a resize
	 */

	virtual void resize(unsigned int width, unsigned int height) = 0;

	/*
	 * Writes an array of pixels (RGBA), with width * height elements
	 */

	virtual void write(uint32_t *pixels, int width, int height) = 0;
};

} /* namespace atlantis */

#endif /* ATLANTIS_VIDEO_H_ */
