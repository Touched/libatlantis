#include <Python.h>

extern int disThumb(uint32_t offset, char *dest, int flags);
extern int disArm(uint32_t offset, char *dest, int flags);

PyObject *disassemble_thumb(PyObject *self, PyObject *args) {
	char dest[100];
	uint32_t offset;
	int flags = 2;

	if (!PyArg_ParseTuple(args, "I|i", &offset, &flags)) {
		return NULL;
	}

	disThumb(offset, dest, flags);

	return PyUnicode_FromString(dest);
}

PyObject *disassemble_arm(PyObject *self, PyObject *args) {
	char dest[100];
	uint32_t offset;
	int flags = 2;

	if (!PyArg_ParseTuple(args, "I|i", &offset, &flags)) {
		return NULL;
	}

	disArm(offset, dest, flags);

	return PyUnicode_FromString(dest);
}
