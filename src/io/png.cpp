// maptiles
#include <io/png.h>

// C++ STL
#include <cstring>

// PNG
#include <png.h>

using namespace maptiles;
using namespace io;

uint8_t* png::load(const char* fname, int& width, int& height) {

	FILE *fp = fopen(fname, "rb");

	if (!fp) {
		printf("fopen");
		return nullptr;
	}

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

	if(!png) {
		printf("png");
		return nullptr;
	}

	png_infop info = png_create_info_struct(png);

	if(!info)  {
		printf("info");
		png_destroy_read_struct(&png, nullptr, nullptr);
		fclose(fp);
		return nullptr;
	}

	if(setjmp(png_jmpbuf(png))) {
		printf("jmp");
		png_destroy_read_struct(&png, &info, nullptr);
		fclose(fp);
		return nullptr;
	}

	png_init_io(png, fp);

	png_read_info(png, info);

	width               = png_get_image_width(png, info);
	height              = png_get_image_height(png, info);
	png_byte color_type = png_get_color_type(png, info);
	png_byte bit_depth  = png_get_bit_depth(png, info);

	// Read any color_type into 8bit depth, RGBA format.
	// See http://www.libpng.org/pub/png/libpng-manual.txt

	if(bit_depth == 16)
		png_set_strip_16(png);

	if(color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if(png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	// These color_type don't have an alpha channel then fill it with 0xff.
	if(color_type == PNG_COLOR_TYPE_RGB ||
			color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if(color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);

	png_bytep* row_pointers = new png_bytep[sizeof(png_bytep) * height];

	if (!row_pointers) {
		printf("row_pointers");
		png_destroy_read_struct(&png, &info, nullptr);
		fclose(fp);
		return nullptr;
	}

	size_t row_bytes = png_get_rowbytes(png,info);

	for(int y = 0; y < height; y++) {

		row_pointers[y] = new png_byte[row_bytes];

		if (!row_pointers[y]) {

			for (int k = 0; k < y; k++)  {
				delete[] row_pointers[k];
			}

			delete[] row_pointers;

			printf("alloc");
			png_destroy_read_struct(&png, &info, nullptr);
			fclose(fp);

			return nullptr;

		}

	}

	png_read_image(png, row_pointers);

	fclose(fp);


	// Flatten image to unique buffer
	uint8_t* ret = new uint8_t[height * row_bytes];


	for (int y = 0; y < height; y++) {

		memcpy(&(ret[y * row_bytes]), row_pointers[y], row_bytes);
		delete[] row_pointers[y];

	}

	png_destroy_read_struct(&png, &info, nullptr);

	delete[] row_pointers;

	return ret;

}

bool png::save(const char* fname, const uint8_t* buffer, int width, int height) {

	int y;

	FILE *fp = fopen(fname, "wb");
	if(!fp) {
		return false;
	}

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!png) {
		fclose(fp);
		return false;
	}

	png_infop info = png_create_info_struct(png);
	if (!info) {
		png_destroy_write_struct(&png, nullptr);
		fclose(fp);
		return false;
	}

	if (setjmp(png_jmpbuf(png))) {
		png_destroy_write_struct(&png, &info);
		fclose(fp);
		return false;
	}

	png_init_io(png, fp);

	// Output is 8bit depth, RGBA format.
	png_set_IHDR(
			png,
			info,
			width, height,
			8,
			PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT
			);
	png_write_info(png, info);

	// To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
	// Use png_set_filler().
	// png_set_filler(png, 0, PNG_FILLER_AFTER);
	

	// Alloc bidimensional row pointer
	png_bytep* row_pointers = new png_bytep[sizeof(png_bytep) * height];

	if (!row_pointers) {
		png_destroy_write_struct(&png, &info);
		fclose(fp);
		return false;
	}

	size_t row_bytes = png_get_rowbytes(png,info);

	for(int y = 0; y < height; y++) {

		row_pointers[y] = new png_byte[row_bytes];

		if (!row_pointers[y]) {

			for (int k = 0; k < y; k++)  {
				delete[] row_pointers[k];
			}

			delete[] row_pointers;

			png_destroy_write_struct(&png, &info);
			fclose(fp);

			return false;

		}

		// Copy input pointer row to aux pointer
		memcpy(row_pointers[y], &(buffer[y * row_bytes]), row_bytes);	

	}

	png_write_image(png, row_pointers);
	png_write_end(png, nullptr);

	fclose(fp);
	png_destroy_write_struct(&png, &info);

	for (int y = 0; y < height; y++) {
		delete[] row_pointers[y];
	}
	delete[] row_pointers;

	// Everything OK
	return true;

}

