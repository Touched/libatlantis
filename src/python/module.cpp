#include <Python.h>
#include "surface.h"
#include "emulator.h"
#include "debugger.h"
#include "input.h"
#include "../gba/Globals.h"

extern "C" {

PyObject *memory_bios(PyObject *self, PyObject *args) {
	return PyMemoryView_FromMemory((char*)bios, 0x4000, PyBUF_READ);
}
PyObject *memory_rom(PyObject *self, PyObject *args) {
	return PyMemoryView_FromMemory((char*)rom, 0x2000000, PyBUF_WRITE);
}
PyObject *memory_iram(PyObject *self, PyObject *args) {
	return PyMemoryView_FromMemory((char*)internalRAM, 0x8000, PyBUF_WRITE);
}
PyObject *memory_wram(PyObject *self, PyObject *args) {
	return PyMemoryView_FromMemory((char*)workRAM, 0x40000, PyBUF_WRITE);
}
PyObject *memory_pal(PyObject *self, PyObject *args) {
	PyMemoryView_FromMemory((char*)paletteRAM, 0x400, PyBUF_WRITE);
}
PyObject *memory_vram(PyObject *self, PyObject *args) {
	PyMemoryView_FromMemory((char*)vram, 0x20000, PyBUF_WRITE);
}
PyObject *memory_oam(PyObject *self, PyObject *args) {
	PyMemoryView_FromMemory((char*)oam, 0x400, PyBUF_WRITE);
}
PyObject *memory_io(PyObject *self, PyObject *args) {
	PyMemoryView_FromMemory((char*)ioMem, 0x400, PyBUF_WRITE);
}

static PyMethodDef AtlantisMethods[] = {
    {"surface", get_cairo_surface, METH_NOARGS, "Get the Cairo surface for the emulator."},
    {"draw", pass_cairo_context, METH_VARARGS, ""},
    {"init", emulator_init, METH_NOARGS, "Load a ROM."},
    {"finalize", emulator_finalize, METH_NOARGS, "Load a ROM."},
    {"iteration", emulator_iteration, METH_NOARGS, "Load a ROM."},
    {"load", emulator_load, METH_VARARGS, "Load a ROM."},
    {"press", input_button_press, METH_VARARGS, "Press a button."},
    {"release", input_button_release, METH_VARARGS, "Release a button."},

    {"bios", memory_bios, METH_NOARGS, "Return a memory view."},
    {"rom", memory_rom, METH_NOARGS, "Return a memory view."},
    {"iram", memory_iram, METH_NOARGS, "Return a memory view."},
    {"wram", memory_wram, METH_NOARGS, "Return a memory view."},
    {"pal", memory_pal, METH_NOARGS, "Return a memory view."},
    {"vram", memory_vram, METH_NOARGS, "Return a memory view."},
    {"oam", memory_oam, METH_NOARGS, "Return a memory view."},
    {"io", memory_io, METH_NOARGS, "Return a memory view."},

    {"disassemble_thumb", disassemble_thumb, METH_VARARGS, "Disassemble offset to Thumb."},
    {"disassemble_arm", disassemble_arm, METH_VARARGS, "Disassemble offset to Arm."},
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
