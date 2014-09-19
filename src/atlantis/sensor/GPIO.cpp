#include <cstdlib>
#include "GPIO.h"

GPIO::GPIO() {
	enabled = true;
	data = NULL;
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
	return 1;
}

int GPIO::write(u32 address, u16 value) {
	switch (address - 0x080000C4) {
	case 0:
		data->registers.short1 = value;
		break;
	case 2:
		data->registers.short2 = value;
		break;
	case 4:
		data->registers.short3 = value;
		break;
	default:
		return 1;
	}
	return 0;
}

int GPIO::write(u32 address, u8 value) {
	if(!isInAddressRange(address))
		return 1;

	u32 offset = address - 0x080000C4;

	data->elements[offset] = value;
	return 0;
}

u32 GPIO::read_word(u32 address) {
	return 0;
}

u16 GPIO::read_hword(u32 address) {
	switch (address - 0x080000C4) {
	case 0:
		return data->registers.short1;
	case 2:
		return data->registers.short2;
	case 4:
		return data->registers.short3;
	}
	return 0;
}

u16 GPIO::read_byte(u32 address) {
	if(!isInAddressRange(address))
		return 0;

	u32 offset = address - 0x080000C4;

	return data->elements[offset];
}

int GPIO::read(u32 address, u32* out) {
	return 1;
}

int GPIO::read(u32 address, u16* out) {
	switch (address - 0x080000C4) {
	case 0:
		*out = data->registers.short1;
		// no break
	case 2:
		*out = data->registers.short2;
		// no break
	case 4:
		*out = data->registers.short3;
		return 0;
	}
	return 1;
}

int GPIO::read(u32 address, u8* out) {
	if(!isInAddressRange(address))
		return 1;

	u32 offset = address - 0x080000C4;

	*out = data->elements[offset];
	return 0;
}

void GPIO::enable() {
	enabled = true;
}

void GPIO::disable() {
	enabled = false;
}
