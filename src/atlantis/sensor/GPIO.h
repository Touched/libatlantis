#ifndef GPIO_H_
#define GPIO_H_

#include "Sensor.h"

/*
 * Base class for implementation of sensors that utilise the 4bit GPIO port in
 * the ROM chip. Some cartidges use this interface to implement an RTC or
 * or game-specific sensors.
 */

class GPIO: public Sensor {
public:
	GPIO();
	virtual ~GPIO();

	bool isInAddressRange(u32 address);

	bool isEnabled();

	int write(u32 address, u32 value);
	int write(u32 address, u16 value);
	int write(u32 address, u8 value);

	u32 read_word(u32 address);
	u16 read_hword(u32 address);
	u8 read_byte(u32 address);
	int read(u32 address, u32 *out);
	int read(u32 address, u16 *out);
	int read(u32 address, u8 *out);

	void enable();
	void disable();
private:
	bool enabled;
	u16 data;
	u16 direction;
	u16 control;
};

#endif /* GPIO_H_ */
