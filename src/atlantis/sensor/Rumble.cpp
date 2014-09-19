#include "Rumble.h"

Rumble::Rumble() {
}

void Rumble::onWrite() {
	// Pin 0 is HIGH and Direction for pin 0 is OUT
	if ((data & 1) && (direction & 1)) {
		// TODO: Rumble on
	} else {
		// TODO: Rumble off
	}
}

Rumble::~Rumble() {
	// TODO Auto-generated destructor stub
}

