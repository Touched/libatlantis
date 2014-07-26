#ifndef ATLANTIS_JOYPAD_H_
#define ATLANTIS_JOYPAD_H_

#include <stdint.h>

namespace atlantis {

class Joypad {
public:
	Joypad();

	// D-Pad
	void down(bool press);
	void up(bool press);
	void left(bool press);
	void right(bool press);

	// Controls
	void start(bool press);
	void select(bool press);
	void a(bool press);
	void b(bool press);
	void l(bool press);
	void r(bool press);

	// Other
	void speed(bool press);
	void capture(bool press);

	uint32_t getState();

	virtual ~Joypad();
private:
	void setBit(int place, bool value);

	uint32_t state;
};

} /* namespace atlantis */

#endif /* ATLANTIS_JOYPAD_H_ */
