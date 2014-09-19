#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor {
public:
	Sensor();

	/*
	 * Return true if address is in the range of addresses that
	 * are mapped to this device/sensor.
	 */
	virtual bool isInAddressRange(u32 address);

	/*
	 * Return true of this sensor is enabled and will respond to read/write
	 * requests.
	 */
	virtual bool isEnabled();

	/*
	 * Write to the given address. Should only work if the address
	 * is isInAddressRange(address) returns true. Return 0 on success.
	 */
	virtual int write(u32 address, u32 value);
	virtual int write(u32 address, u16 value);
	virtual int write(u32 address, u8 value);

	/*
	 * Read functions with return
	 */
	virtual u32 read_word(u32 address);
	virtual u16 read_hword(u32 address);
	virtual u16 read_byte(u32 address);

	/*
	 * Overloaded read functions. Return 0 on success. Should only work if the address
	 * is isInAddressRange(address)
	 */
	virtual int read(u32 address, u32 *out);
	virtual int read(u32 address, u16 *out);
	virtual int read(u32 address, u8 *out);

	virtual ~Sensor();
};

#endif /* SENSOR_H_ */
