#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "../atlantis/emulator.h"

namespace test {

class System: public atlantis::Emulator {
public:
	System();
	virtual ~System();

	atlantis::Video *video_driver();


	atlantis::Audio *sound_driver();


	atlantis::Input *input_driver();


private:
	atlantis::Video *video;
	atlantis::Audio *sound;
	atlantis::Input *input;

};

} /* namespace test */

#endif /* SYSTEM_H_ */
