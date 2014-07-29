#ifndef SURFACE_H_
#define SURFACE_H_

#include <Python.h>

void surface_init(int width, int height);
void surface_draw(uint32_t* frame, int width, int height);
PyObject *get_cairo_surface(PyObject *self, PyObject*);
PyObject *pass_cairo_context(PyObject *self, PyObject*);


#endif /* SURFACE_H_ */
