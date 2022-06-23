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

#include "ImgUtils.h"

// Given (a pointer to) an image, and the pixel index, returns 
// the colour at the corresponding pixel. Assumes that
// pixel index is valid. Note that the return value is
// is *not* a pointer.
Colour getColourAtPixel(Image *im, int pixIdx) {
  Colour col;
  col.R = im->rgbdata[3*pixIdx + 0];   //
  col.G = im->rgbdata[3*pixIdx + 1];   // Each pixel has 3 values
  col.B = im->rgbdata[3*pixIdx + 2];   //
  return col;
}

// Generates a new image. You don't need to look a this code if
// you don't want to. It's not relevant to what you have to implement.
Image *newImage(int sx, int sy) {
  Image *im;

  im = (Image *)calloc(1, sizeof(Image));
  if (im != NULL) {
    im->sx = sx;
    im->sy = sy;
    im->rgbdata =
        (unsigned char *)calloc(sx * sy * 3, sizeof(unsigned char));
    if (im->rgbdata != NULL) return (im);
  }
  fprintf(stderr, "Unable to allocate memory for new image\n");
  return (NULL);
}

// Read in an image from the given filename
Image *readPPMimage(const char *filename) {
  FILE *f;
  Image *im;
  char line[1024];
  int sizx, sizy;
  int i;
  unsigned char *tmp;

  int x;
  char *y;

  im = (Image *)calloc(1, sizeof(Image));
  if (im != NULL) {
    im->rgbdata = NULL;
    f = fopen(filename, "rb+");
    if (f == NULL) {
      fprintf(
          stderr,
          "Unable to open file %s, please check name and path\n",
          filename);
      free(im);
      return (NULL);
    }
    im->filename = basename((char *)filename);
    y = fgets(&line[0], 1000, f);
    if (strcmp(&line[0], "P6\n") != 0) {
      fprintf(stderr,
              "Wrong file format, not a .ppm file or header end-of-line "
              "characters missing\n");
      free(im);
      fclose(f);
      return (NULL);
    }
    // Skip over comments
    y = fgets(&line[0], 511, f);
    while (line[0] == '#') {
      y = fgets(&line[0], 511, f);
    }
    sscanf(&line[0], "%d %d\n", &sizx, &sizy);  // Read file size
    im->sx = sizx;
    im->sy = sizy;

    y = fgets(&line[0], 9, f);  // Read the remaining header line
    tmp = (unsigned char *)calloc(sizx * sizy * 3, sizeof(unsigned char));
    if (tmp == NULL) {
      fprintf(stderr, "Out of memory allocating space for image\n");
      free(im);
      fclose(f);
      return (NULL);
    }

    x = fread(tmp, sizx * sizy * 3 * sizeof(unsigned char), 1, f);
    fclose(f);

    im->rgbdata = tmp;

    return (im);
  }

  fprintf(stderr, "Unable to allocate memory for image structure\n");
  return (NULL);
}

// Output an image at the given filename
void imageOutput(Image *im, const char *filename) {
  FILE *f;
  unsigned char *bits24;

  if (im != NULL)
    if (im->rgbdata != NULL) {
      bits24 = im->rgbdata;
      f = fopen(filename, "wb+");
      if (f == NULL) {
        fprintf(stderr, "Unable to open file %s. No output written\n", filename);
        return;
      }
      fprintf(f, "P6\n");
      fprintf(f, "# Output from Marcher.c\n");
      fprintf(f, "%d %d\n", im->sx, im->sy);
      fprintf(f, "255\n");
      fwrite(bits24, im->sx * im->sy * 3 * sizeof(unsigned char), 1, f);
      fclose(f);
      free(bits24);
      return;
    }
  fprintf(stderr, "imageOutput(): Specified image is empty. Nothing output\n");
  return;
}

// Output the path onto the image. Colour changes from light
// green to dark green based on when the pixel along the
// path was visited
void outputPath(int path[], Image *img) {
  // Get length of path:
  int n = 0;
  while (path[n] >= 0) {
    n++;
  }

  
  Image *pathIm = newImage(img->sx, img->sy);
  memcpy(pathIm->rgbdata, img->rgbdata,
         sizeof(unsigned char) * img->sx * img->sy * 3);

  double l = 120.0 / n;
  for (int p = 0; p < n; p++) {
    pathIm->rgbdata[path[p] * 3 + 0] = 0;
    pathIm->rgbdata[path[p] * 3 + 1] = (unsigned char)(255 - (p * l));
    pathIm->rgbdata[path[p] * 3 + 2] = 0;
  }

  char outName[1024];
  mkdir("output", 0700);
  strcpy(outName, "output/Path-");
  strcat(outName, img->filename);

  imageOutput(pathIm, outName);
  return;
}

void freeImage(Image *im) {
  if (im != NULL) {
    if (im->rgbdata != NULL) {
      free(im->rgbdata);
    }
    free(im);
  }
  return;
}
