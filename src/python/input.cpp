#include "input.h"

extern "C" {

PyObject *input_button_press(PyObject *self, PyObject *args) {

	int player = -1;
	uint32_t button = 0;

	if (!PyArg_ParseTuple(args, "I|i", &button, &player)) {
		return NULL;
	}

	uint32_t state = atlantis_input_read_state(player);
	state = atlantis_input_button(state, button, 1);
	atlantis_input_write_state(player, state);

	Py_RETURN_NONE;
}

PyObject *input_button_release(PyObject *self, PyObject *args) {

	int player = -1;
	uint32_t button = 0;

	if (!PyArg_ParseTuple(args, "I|i", &button, &player)) {
		return NULL;
	}

	uint32_t state = atlantis_input_read_state(player);
	state = atlantis_input_button(state, button, 0);
	atlantis_input_write_state(player, state);

	Py_RETURN_NONE;
}
}
