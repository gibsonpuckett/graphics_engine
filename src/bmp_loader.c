#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>

#include "image_loader.h"

#define BMP_MAGIC 0x4D42

// Load a bitmap texture file as an OpenGL texture
texture_t texture_load_bmp(const char* filename) {
  texture_t texture;
  
  FILE* file = fopen(filename, "rb");
  if (!file) {
    fprintf(stderr, "Failed to open BMP file.\n");
    return texture;
  }

  bmp_file_header_t bmp_header;
  fread(&bmp_header, sizeof(bmp_header), 1, file);
  if (bmp_header.signature != BMP_MAGIC) {
    fprintf(stderr, "Not a BMP file.\n");
    fclose(file);
    return texture;
  }

  bmp_info_header_t dib_header;
  fread(&dib_header, sizeof(dib_header), 1, file);

  if (dib_header.bits_per_pixel != 24 || dib_header.compression != 0) {
    fprintf(stderr, "Only 24-bit uncompressed BMP's are currently supported.\n");
    fclose(file);
    return texture;
  }

  uint32_t width = dib_header.width;
  uint32_t height = dib_header.height;
  size_t row_size = (width * 3 + 3) & ~3; // Allign to 4-byte boundary
  // width * 3    --> 3 bytes per pixel (24-bit BMP = RGB)
  // + 3          --> ensures round UP to next multiple of 4
  // & ~3         --> bitmask clear lowest 2 bits (rounding down to multiple of 4)
  // ie width = 5 --> 5 x 3 = 15 --> 15 + 3 = 18 --> 17 & ~3 = 16
  // ie width = 3 --> 3 x 3 = 9  --> 9 + 3  = 12 --> 12 & ~3 = 12
  size_t data_size = row_size * height;

  unsigned char* data = malloc(data_size);
  if (!data) {
    fclose(file);
    return texture;
  }

  fseek(file, bmp_header.data_offset, SEEK_SET);
  fread(data, 1, data_size, file);
  fclose(file);

  // Flips rows (BMP stores them bottom-up)
  unsigned char* flipped = malloc(width * height * 3);
  if (!flipped) {
    free(data);
    return texture;
  }
  
  for (uint32_t y = 0; y < height; y++) {
    for (uint32_t x = 0; x < width; x++) {
	size_t src_index = y * row_size + x * 3;
	size_t dst_index = (height - 1 - y) * width * 3 + x * 3;

	flipped[dst_index + 0] = data[src_index + 2]; // R
	flipped[dst_index + 1] = data[src_index + 1]; // G
	flipped[dst_index + 2] = data[src_index + 0]; // B
    }
  }

  free(data);

  glGenTextures(1, &texture.id);
  glBindTexture(GL_TEXTURE_2D, texture.id);
  // set the texture wrapping/filtering options (on currently bound texture)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, flipped);
  glGenerateMipmap(GL_TEXTURE_2D);
 

  free(flipped);

  if (texture.id == 0) {
    fprintf(stderr, "Failed to create texture.\n");
    return texture;
  }

  return texture;

}

void texture_destroy_bmp(texture_t* texture)
{
  if (texture && texture->id != 0) {
    glDeleteTextures(1, &texture->id);
    texture->id = 0;
  }
}


// Ignore for now, eventually will add functionality for more BMP types
static uint8_t bpp_switch(uint8_t bpp) {
  switch (bpp) {
  case 1:  // Monochrome
    printf("Case 1\n");
    return 1;
  case 4:  // maximum 16 colors
    printf("Case 4\n");
    break;
  case 8:  // maximum 256 colors
    printf("Case 8\n");
    return 8;
  case 16: // maximum 2^16 colors
    // Check compression field
    // each word represents single pixel
    // 5 bits per color component, blue is least significant 5 bits, followed by green then red. most significant bit unused
    printf("Case 16\n");
    return 16;
  case 24:  // maximum 2^24 colors
    // Palette field no entries
    // each 3 byte triplet in bmp array repr. relative intensities of blue green read per pixel
    printf("Case 24\n");
    return 24;
  default:  // catch-all
    printf("Default\n");
    return 0;
  }
}
  
