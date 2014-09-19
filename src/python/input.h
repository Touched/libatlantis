#ifndef INPUT_H_
#define INPUT_H_

#include <Python.h>
#include <stdint.h>
#include "../atlantis/input.h"

extern "C" {
PyObject *input_button_release(PyObject *self, PyObject *args);
PyObject *input_button_press(PyObject *self, PyObject *args);
}

#endif /* INPUT_H_ */
