#ifndef RUMBLE_H_
#define RUMBLE_H_

/*
 * Rumble sensor, for Warioware: Twisted. Maybe Drill Dozer, too
 */

#include "GPIO.h"

class Rumble: public GPIO {
public:
	Rumble();
	void onWrite();
	virtual ~Rumble();
};

#endif /* RUMBLE_H_ */
