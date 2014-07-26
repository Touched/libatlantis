#include "Video.h"

#include <cstdio>
#include <ctime>
#include <png.h>

namespace test {

Video::Video() {
}

Video::~Video() {
}

void Video::resize(unsigned int width, unsigned int height) {
}

void Video::write(uint32_t* pixels, int width, int height) {
	//return;
	static time_t last_time = time(NULL);

	if (difftime(time(NULL), last_time) < 1)
		return;

	last_time = time(NULL);


	FILE * fp;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	size_t x, y;
	png_byte ** row_pointers = NULL;
	int status = -1;
	/* The following number is set by trial and error only. I cannot
	 see where it it is documented in the libpng manual.
	 */
	int pixel_size = 3;
	int depth = 8;

	char buffer[2048];
	static int counter = 0;
	sprintf(buffer, "img/image-%03d.png", counter++);

	fp = fopen(buffer, "wb");

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	info_ptr = png_create_info_struct(png_ptr);

	/* Set up error handling. */


	/* Set image attributes. */

	png_set_IHDR(png_ptr, info_ptr, width, height, depth,
	PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
	PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	/* Initialize rows of PNG. */

	uint32_t *ptr = pixels;// + 32;

	uint8_t color = 0x00;

	row_pointers = (png_byte **) png_malloc(png_ptr,
			height * sizeof(png_byte *));
	for (y = 0; y < height; ++y) {
		png_byte *row = (png_byte *) png_malloc(png_ptr,
				sizeof(uint8_t) * width * pixel_size);
		row_pointers[y] = row;

		for (x = 0; x < width; ++x) {
			uint32_t pixel = *ptr++;

			//RGB

			*row++ = (pixel >> 8) & 0xFF;
			*row++ = (pixel >> 16) & 0xFF;
			*row++ = (pixel >> 24) & 0xFF;
		}

		color++;
	}

	/* Write the image data to "fp". */

	png_init_io(png_ptr, fp);
	png_set_rows(png_ptr, info_ptr, row_pointers);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	/* The routine has successfully written the file, so we set
	 "status" to a value which indicates success. */

	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);

	status = 0;

	for (y = 0; y < height; y++) {
		png_free(png_ptr, row_pointers[y]);
	}
	png_free(png_ptr, row_pointers);
	fclose(fp);
}

} /* namespace test */
