#include <stdint.h>
#include <py3cairo.h>
#include "../atlantis/callback.h"
#include <cstdio>

cairo_surface_t *surface;

void surface_draw(uint32_t* frame, int width, int height) {
	unsigned char *data;
	int stride;
	int x, y;

	data = cairo_image_surface_get_data(surface);

	stride = cairo_image_surface_get_stride(surface);

	//uint8_t *pixels = (uint8_t*)frame;

	for (y = 0; y < height; ++y) {
		for (x = 0; x < width; ++x) {
			uint32_t pixel = *frame++;

			uint8_t r = ((pixel >> 24) & 0xff);
			uint8_t g = ((pixel >> 16) & 0xff);
			uint8_t b = ((pixel >> 8) & 0xff);

			*data++ = r;
			*data++ = g;
			*data++ = b;
			*data++ = 0;
		}
	}
	cairo_surface_mark_dirty(surface);
}

PyObject *get_cairo_surface(PyObject *self, PyObject *dummy) {
	return PycairoSurface_FromSurface(cairo_surface_reference(surface), NULL);
}

PyObject *pass_cairo_context(PyObject *self, PyObject *args) {
	PyObject *context, *w;

	PyArg_ParseTuple(args, "OO", &w, &context);

	//PyObject_Print(PyObject_GetAttrString(w, "queue_draw"), stdout, 0);
	PyObject_CallMethodObjArgs(w, PyUnicode_InternFromString("queue_draw"), NULL);

	cairo_t *cr = PycairoContext_GET(context);

	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	//cairo_set_source_surface(cr, surface, 0, 0);
	cairo_pattern_t *pattern = cairo_pattern_create_for_surface(surface);
	cairo_pattern_set_filter(pattern, CAIRO_FILTER_FAST);
	cairo_matrix_t matrix = {0};
	cairo_matrix_init_scale(&matrix, 0.5, 0.5);
	cairo_pattern_set_matrix(pattern, &matrix);
	cairo_set_source(cr, pattern);
	cairo_paint(cr);

	Py_RETURN_NONE;
}

void surface_init(int width, int height) {
	if (import_cairo() < 0) {
		return;
	}

	atlantisVideoOnFrame(surface_draw);

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
}
