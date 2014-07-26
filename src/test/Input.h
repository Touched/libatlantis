#ifndef INPUT_H_
#define INPUT_H_

#include "../atlantis/input.h"
#include "../atlantis/joypad.h"

namespace test {

class Input: public atlantis::Input {
public:
	Input();
	virtual ~Input();
	atlantis::Joypad *getDefault();
	atlantis::Joypad *getPad(int which);
	bool canRead();
private:
	atlantis::Joypad pads[4];
	int defaultPad;
};

} /* namespace test */

#endif /* INPUT_H_ */
