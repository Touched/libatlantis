#include "input.h"

extern "C" {

Input atlantis_joypads = { {0}, 0 };

uint32_t atlantis_input_button(uint32_t state, uint32_t button, bool value) {
	switch (button) {
	case ATLANTIS_BUTTON_DPAD_UP:
		// no break
	case ATLANTIS_BUTTON_DPAD_DOWN:
		state &= ~(ATLANTIS_BUTTON_DPAD_UP | ATLANTIS_BUTTON_DPAD_DOWN);
		break;
	case ATLANTIS_BUTTON_DPAD_LEFT:
		// no break
	case ATLANTIS_BUTTON_DPAD_RIGHT:
		state &= ~(ATLANTIS_BUTTON_DPAD_LEFT | ATLANTIS_BUTTON_DPAD_RIGHT);
		break;
	default:
		state &= ~button;
	}

	// Set the button
	if (value) state |= button;

	return state;
}

uint32_t atlantis_input_read_state(int player) {
	if (player == -1)
		return atlantis_joypads.states[atlantis_joypads.default_player];
	else if (player >= 0 && player < ATLANTIS_MAX_PLAYERS)
		return atlantis_joypads.states[player];
	else
		return 0;
}

void atlantis_input_write_state(int player, uint32_t state) {
	if (player == -1)
		atlantis_joypads.states[atlantis_joypads.default_player] = state;
	else if (player >= 0 && player < ATLANTIS_MAX_PLAYERS)
		atlantis_joypads.states[player] = state;
}

}
