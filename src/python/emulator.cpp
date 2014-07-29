#include <Python.h>
#include "../atlantis/atlantis.h"

extern "C" {

PyObject *emulator_load(PyObject *self, PyObject *args) {
	char *name;

	if (!PyArg_ParseTuple(args, "s", &name)) {
		return NULL;
	}

	atlantis_load((const char*)name);

	Py_RETURN_NONE;
}

PyObject *emulator_init(PyObject *self, PyObject *args) {
	atlantis_init();

	Py_RETURN_NONE;
}

PyObject *emulator_finalize(PyObject *self, PyObject *args) {
	atlantis_finalize();

	Py_RETURN_NONE;
}

PyObject *emulator_iteration(PyObject *self, PyObject *args) {
	return PyLong_FromLong(atlantis_iteration());
}

}
