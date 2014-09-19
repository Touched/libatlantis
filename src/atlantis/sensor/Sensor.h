#ifndef SENSOR_H_
#define SENSOR_H_

/*
 * Abstract base class for sensors and devices that have been added onto the
 * GBA.
 */

class Sensor {
public:
	Sensor();

	/*
	 * Return true if address is in the range of addresses that
	 * are mapped to this device/sensor.
	 */
	virtual bool isInAddressRange(u32 address) = 0;

	/*
	 * Return true of this sensor is enabled and will respond to read/write
	 * requests.
	 */
	virtual bool isEnabled() = 0;

	/*
	 * Write to the given address. Should only work if the address
	 * is isInAddressRange(address) returns true. Return 0 on success.
	 */
	virtual int write(u32 address, u32 value) = 0;
	virtual int write(u32 address, u16 value) = 0;
	virtual int write(u32 address, u8 value) = 0;

	/*
	 * Read functions with return
	 */
	virtual u32 read_word(u32 address) = 0;
	virtual u16 read_hword(u32 address) = 0;
	virtual u16 read_byte(u32 address) = 0;

	/*
	 * Overloaded read functions. Return 0 on success. Should only work if the address
	 * is isInAddressRange(address)
	 */
	virtual int read(u32 address, u32 *out) = 0;
	virtual int read(u32 address, u16 *out) = 0;
	virtual int read(u32 address, u8 *out) = 0;

	virtual ~Sensor();
};

#endif /* SENSOR_H_ */
