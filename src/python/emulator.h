#ifndef EMULATOR_H_
#define EMULATOR_H_

extern "C" {
static PyObject *emulator_load(PyObject *self, PyObject *args);
static PyObject *emulator_init(PyObject *self, PyObject *args);
static PyObject *emulator_finalize(PyObject *self, PyObject *args);
static PyObject *emulator_iteration(PyObject *self, PyObject *args);
}

#endif /* EMULATOR_H_ */
