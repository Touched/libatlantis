#include <Python.h>
#include "surface.h"
#include "emulator.h"

extern "C" {

static PyMethodDef AtlantisMethods[] = {
    {"surface", get_cairo_surface, METH_NOARGS, "Get the Cairo surface for the emulator."},
    {"draw", pass_cairo_context, METH_VARARGS, ""},
    {"init", emulator_init, METH_NOARGS, "Load a ROM."},
    {"finalize", emulator_finalize, METH_NOARGS, "Load a ROM."},
    {"iteration", emulator_iteration, METH_NOARGS, "Load a ROM."},
    {"load", emulator_load, METH_VARARGS, "Load a ROM."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef atlantis_module = {
   PyModuleDef_HEAD_INIT,
   "spam",
   "Atlantis GBA emulator.",
   -1,
   AtlantisMethods
};

PyMODINIT_FUNC PyInit_atlantis(void)
{
	PyObject *module;

	module = PyModule_Create(&atlantis_module);

	if (module == NULL) {
		return NULL;
	}

	surface_init(240, 160);

	return module;
}

}
