#include <cstddef>
#include "Input.h"

namespace test {

Input::Input() {
	defaultPad = 0;
}

Input::~Input() {
}

atlantis::Joypad* Input::getDefault() {
	return &pads[defaultPad];
}

atlantis::Joypad* Input::getPad(int which) {
	if (which < 0 || which > 3) return NULL;
	return &pads[which];
}

bool Input::canRead() {
	return true;
}

} /* namespace test */
