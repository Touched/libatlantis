#ifndef SOLAR_H_
#define SOLAR_H_

/*
 * Solar sensor, as used in Botkai
 */

#include "GPIO.h"

class Solar: public GPIO {
public:
	Solar();

	/* Define in your implementation with a macro. Return the sunlight level
	 * as a value between 5 (brightest) and 0xE8 (darkest) */
	int sunlight();
	void onWrite();
	virtual ~Solar();
private:
	int counter;
};

#endif /* SOLAR_H_ */
