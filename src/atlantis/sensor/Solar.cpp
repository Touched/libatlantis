#include "Solar.h"

Solar::Solar() {
	counter = 0;
}

int Solar::sunlight() {
	return 0xE8;
}

void Solar::onWrite() {
	if (data & 1) {
		// CLK is HIGH
		counter++;
	} else if (data & 2) {
		// Reset
		counter = 0;
	} else {
		// During CLK LOW
		// If the counter has reached the level of sunlight, set the flag
		if (counter == sunlight()) {
			data = 8;
		}
	}
}

Solar::~Solar() {
}

