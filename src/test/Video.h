#ifndef VIDEOS_H_
#define VIDEOS_H_

#include <stdint.h>
#include "../atlantis/video.h"
#include "../gba/GBA.h"

namespace test {

class Video: public atlantis::Video {
public:
	Video();
	virtual ~Video();

	void resize(unsigned int width, unsigned int height);
	void write(uint32_t *pixels, int width, int height);
private:
	int m_width;
	int m_height;
};

} /* namespace test */

#endif /* VIDEOS_H_ */
