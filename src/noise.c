#include "noise.h"

#include <math.h>
#include <stdint.h>
#include <time.h>

// The original permutation array from Ken Perlin's reference implementation. 256 elements
static int permutation[] =
{
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,
    69,142,8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,
    252,219,203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,
    168, 68,175,74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,
    60,211,133,230,220,105,92,41,55,46,245,40,244,102,143,54, 65,25,63,161,
    1,216,80,73,209,76,132,187,208,89,18,169,200,196,135,130,116,188,159,
    86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,5,202,38,147,
    118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,223,183,
    170,213,119,248,152, 2,44,154,163,70,221,153,101,155,167,43,172,9,
    129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,
    97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,
    249,14,239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,
    121,50,45,127,  4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,
    128,195,78,66,215,61,156,180
};

// 'p' is the permutation array repeated twice (512 elements)
static int32_t p[512];

// Initializes 'p' by copying permutation list twice
static void init_perlin()
{
  for (int i = 0; i < 256; i++) {
    p[i] = p[256 + i] = permutation[i];
  }
}

// Smoothing input values
static float fade(float t)
{
  return t * t * t * (t * (t * 6 - 15) + 10);
}

// Linear interpolation between a and b by t
static float lerp(float a, float b, float t)
{
  return a + t * (b - a);
}

// Gradient function maps hash val to pseudorandom gradient direction
// then returns dot product between gradient and distance vector
static float grad(int hash, float x, float y)
{
  int h = hash & 7;  // Take the lower 3 bits of the hash (0–7)
  float u = h < 4 ? x : y;
  float v = h < 4 ? y : x;

  // Depending on the bits, flip signs to get 8 different directions.
  return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

// The main 2D Perlin noise function.
// Input coordinates can be any floating point value.
// Output will be in the range [0, 1].
float perlin2d(float x, float y)
{

  init_perlin();
  
  // Find the unit grid cell containing the point
  int X = (int)floorf(x) & 255;
  int Y = (int)floorf(y) & 255;

  // Relative x, y in cell
  x -= floorf(x);
  y -= floorf(y);

  // Compute fade curves for x and y
  float u = fade(x);
  float v = fade(y);

  // Hash coordinates of the four square corners
  int A = p[X] + Y;
  int B = p[X + 1] + Y;

  // Blend results from the four corners of the square
  float res = lerp(
		   lerp(grad(p[A],     x,     y),
			grad(p[B],     x - 1, y),     u),
		   lerp(grad(p[A + 1], x,     y - 1),
			grad(p[B + 1], x - 1, y - 1), u),
		   v
		   );

  // Scale to [0, 1] range
  return (res + 1.0f) / 2.0f;
}
