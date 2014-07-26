#include "joypad.h"

namespace atlantis {

Joypad::Joypad() : state(0) {
}

void Joypad::setBit(int place, bool value) {
	uint32_t mask = ~(1 << place);
	state = (state & mask) | (value << place);
}

void Joypad::down(bool press) {
	setBit(7, press);

	// Disable up
	setBit(6, 0);
}

void Joypad::up(bool press) {
	setBit(6, press);

	// Disable down
	setBit(7, 0);
}

void Joypad::left(bool press) {
	setBit(5, press);

	// Disable right
	setBit(4, 0);
}

void Joypad::right(bool press) {
	setBit(4, press);

	// Disable left
	setBit(5, 0);
}

void Joypad::start(bool press) {
	setBit(3, press);
}

void Joypad::select(bool press) {
	setBit(2, press);
}

void Joypad::a(bool press) {
	setBit(0, press);
}

void Joypad::b(bool press) {
	setBit(1, press);
}

void Joypad::l(bool press) {
	setBit(9, press);
}

void Joypad::r(bool press) {
	setBit(8, press);
}

void Joypad::speed(bool press) {
	setBit(10, press);
}

void Joypad::capture(bool press) {
	setBit(11, press);
}

uint32_t Joypad::getState() {
	return state;
}

Joypad::~Joypad() {
}

} /* namespace atlantis */
