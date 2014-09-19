#ifndef ATLANTIS_INPUT_H_
#define ATLANTIS_INPUT_H_

#include <stdint.h>

extern "C" {

#define ATLANTIS_BUTTON_A (1)
#define ATLANTIS_BUTTON_B (1 << 1)
#define ATLANTIS_BUTTON_START (1 << 3)
#define ATLANTIS_BUTTON_SELECT (1 << 2)
#define ATLANTIS_BUTTON_L (1 << 9)
#define ATLANTIS_BUTTON_R (1 << 8)
#define ATLANTIS_BUTTON_DPAD_UP (1 << 6)
#define ATLANTIS_BUTTON_DPAD_DOWN (1 << 7)
#define ATLANTIS_BUTTON_DPAD_LEFT (1 << 5)
#define ATLANTIS_BUTTON_DPAD_RIGHT (1 << 4)
#define ATLANTIS_BUTTON_SPEED (1 << 10)
#define ATLANTIS_BUTTON_SCREENSHOT (1 << 11)

#define ATLANTIS_MAX_PLAYERS 4

typedef struct {
	uint32_t states[ATLANTIS_MAX_PLAYERS];
	int default_player;
} Input;

extern Input atlantis_joypads;
	uint32_t atlantis_input_button(uint32_t state, uint32_t button, bool value);
	void atlantis_input_write_state(int player, uint32_t state);
	uint32_t atlantis_input_read_state(int player);
}


#endif /* ATLANTIS_INPUT_H_ */
