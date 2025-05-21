#pragma once

#include <stdint.h>
#include <glad/glad.h>  // For GLuint

#define TEXTURE_DIR "../assets/textures/"
#define TEXTURE_PATH "../assets/textures/bricks.bmp"

/* HEADER STRUCTS ALLIGNED WITH BMP DATA */

#pragma pack(push, 1) // Set no padding so can read directly from BMP into structs

typedef struct {
  uint16_t signature;        // 0x0000 :: 'BM'
  uint32_t file_size;        // 0x0002 :: file size in bytes
  uint32_t reserved;         // 0x0006 :: unused(=0)
  uint32_t data_offset;      // 0x000A :: offset from beginning of file to beginning of bmp data
} bmp_file_header_t;

typedef struct {
  uint32_t size;             // 0x000E :: size of info header = 40
  uint32_t width;            // 0x0012 :: horizontal width of bmp in pixels
  uint32_t height;           // 0x0016 :: vertical height of bmp in pixels
  uint16_t planes;           // 0x001A :: number of planes (=1)
  uint16_t bits_per_pixel;   // 0x001C :: bits per pixel				  
  uint32_t compression;      // 0x001E :: type of compression				  
  uint32_t image_size;       // 0x0022 :: (compressed) size of image, 0 if no compression 
  uint32_t x_pixels_per_m;   // 0x0026 :: horizontal resolution pixels/meter		  
  uint32_t y_pixels_per_m;   // 0x002A :: vertical resolution pixels/meter		  
  uint32_t colors_used;      // 0x002E :: number of actually used colors                  
  uint32_t important_colors; // 0x0032 :: number of all important colors, 0 = all
} bmp_info_header_t;

#pragma pack(pop)

typedef struct {
  GLuint id;
} texture_t;

texture_t texture_load_bmp(const char* filename);
void texture_destroy_bmp(texture_t* texture);

