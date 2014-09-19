#include <cstdlib>
#include "GPIO.h"
#include "../common/Port.h"

GPIO::GPIO() {
	enabled = true;

	data = READ16LE(((u16 *)&rom[0xC4]));
	direction = READ16LE(((u16 *)&rom[0xC6]));
	control = READ16LE(((u16 *)&rom[0xC8]));
}

GPIO::~GPIO() {
}

bool GPIO::isInAddressRange(u32 address) {
	// 3 16bit IO registers mapped to ROM starting at 0x080000C4
	return (address >= 0x080000C4 && address <= 0x80000C9);
}

bool GPIO::isEnabled() {
	return enabled;
}

int GPIO::write(u32 address, u32 value) {
	// TODO: Unimplemented
	onWrite();
	return 1;
}

int GPIO::write(u32 address, u16 value) {
	switch (address) {
	case 0x080000C4:
		data = value;
		break;
	case 0x080000C6:
		direction = value;
		break;
	case 0x080000C8:
		control = value;
		break;
	default:
		return 1;
	}
	onWrite();
	return 0;
}

int GPIO::write(u32 address, u8 value) {
	/*
	 * STRB is ignored for ROMX. Silently fail
	 */
	onWrite();
	return 0;
}

/*
 * These just wrap the overloaded reads to avoid code repetition
 */

u32 GPIO::read_word(u32 address) {
	u32 value = 0;
	read(address, &value);
	return value;
}

u16 GPIO::read_hword(u32 address) {
	u16 value = 0;
	read(address, &value);
	return value;
}

u8 GPIO::read_byte(u32 address) {
	u8 value = 0;
	read(address, &value);
	return value;
}

int GPIO::read(u32 address, u32* out) {
	// Force aligned read
	address &= 0x1FFFFFC;

	if (!(control & 1)) {
		// Write-only. Read data that's located at the address in the ROM
		*out = READ32LE(((u32 *)&rom[address]));
		return 0;
	}

	// TODO: Implement this
	onRead();
	return 1;
}

int GPIO::read(u32 address, u16* out) {
	// Force aligned read
	address &= 0x1FFFFFE;

	if (!(control & 1)) {
		// Write-only. Read data that's located at the address in the ROM
		*out = READ16LE(((u16 *)&rom[address]));
		return 0;
	}

	switch (address - 0x080000C4) {
	case 0:
		*out = data;
		break;
	case 2:
		*out = direction;
		break;
	case 4:
		*out = control;
		break;
	default:
		return 1;
	}
	onRead();
	return 0;
}

int GPIO::read(u32 address, u8* out) {
	if (!(control & 1)) {
		// Write-only. Read data that's located at the address in the ROM
		*out = rom[address];
		return 0;
	}

	switch (address) {
	case 0x080000C4:
		*out = data & 0xFF;
		break;
	case 0x080000C5:
		*out = data & 0xFF00;
		break;
	case 0x080000C6:
		*out = direction & 0xFF;
		break;
	case 0x080000C7:
		*out = direction & 0xFF00;
		break;
	case 0x080000C8:
		*out = control & 0xFF;
		break;
	case 0x080000C9:
		*out = control & 0xFF00;
		break;
	default:
		/* Read failed */
		return 1;
	}
	onRead();
	return 0;
}

void GPIO::enable() {
	enabled = true;
}

void GPIO::onRead() {
}

void GPIO::onWrite() {
}

void GPIO::disable() {
	enabled = false;
}
