#ifndef ATLANTIS_INPUT_H_
#define ATLANTIS_INPUT_H_

#include "joypad.h"

namespace atlantis {

class Input {
public:
	virtual Joypad *getDefault() = 0;
	virtual Joypad *getPad(int which) = 0;
	virtual bool canRead() = 0;
};

} /* namespace atlantis */

#endif /* ATLANTIS_INPUT_H_ */
