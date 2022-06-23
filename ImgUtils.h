/*
 * You shouldn't need to change any of the code here. You will
 * NOT be submitting this file as part of your assignment. You
 * might want to look at the getColourAtPixel() function. Do not
 * change anything here as your code will be run with the file as
 * provided in the starter code.
 *
 * CSCB63 Winter 2020 - Assignment 2
 * (c) Mustafa Quraish, Francisco Estrada
 *      (thanks to Paco for some of the code to handle .ppm files!)
 */

#ifndef __IMGUTILS_H
#define __IMGUTILS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <libgen.h>


// Struct we will use for actually storing the image data.
// sx and sy store the dimensions for the image. The image
// data is actually stored in `rgbdata`.
typedef struct image {
  const char *filename;         
  unsigned char *rgbdata; // Actual pixel data
  int sx;
  int sy;
} Image;

// This is used to return the colour of a pixel
typedef struct colour {
  int R;
  int G;
  int B;
} Colour;

Colour getColourAtPixel(Image *im, int pixIdx);
Image *newImage(int sx, int sy);
Image *readPPMimage(const char *filename);
void imageOutput(Image *im, const char *filename);
void outputPath(int path[], Image *img);
void freeImage(Image *im);

#endif
