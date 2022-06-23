/*
 * The code here simply provides an interface to be able to run 
 * your solution on individual input files with certain weight
 * functions. You will not NOT be submitting this file as part 
 * of your assignment. You can change this file to better suit your
 * needs if you wish to do so, but it is only provided for aid in 
 * debugging.
 *
 * You can compile this file using `make` or `make driver` in the
 * directory where it is located. Alternatively, use the command in 
 * the Makefile to do it manually.
 *
 * CSCB63 Winter 2020 - Assignment 2
 * (c) Mustafa Quraish
 */

#include "Marcher.h"  // Includes ImgUtils.h

/*************************************************************/
/******************* WEIGHT FUNCTIONS ************************/
/*************************************************************/

// Weight function (1)
//  The weight between two pixels is the euclidean distance between
//  the (R,G,B) values of the 2 pixels. (If we think of them as vectors)
double similarColour(struct image *im, int a, int b) {
  Colour col1 = getColourAtPixel(im, a);
  Colour col2 = getColourAtPixel(im, b);
  double a1 = (col1.R - col2.R);
  double b1 = (col1.G - col2.G);
  double c1 = (col1.B - col2.B);
  double sumSq = (a1 * a1) + (b1 * b1) + (c1 * c1);
  return sqrt(sumSq) + 0.01;
}

// Weight function (2)
//   The weight between two pixels is simply how close the 2nd pixel is 
//   from the colour white (255, 255, 255).
double howWhite(struct image *im, int a, int b) {
  // Don't even use the current pixel's colur here... the weight
  // functions are arbitrary :)
  Colour col2 = getColourAtPixel(im, b);
  double a1 = (255 - col2.R);
  double b1 = (255 - col2.G);
  double c1 = (255 - col2.B);
  double sumSq = (a1 * a1) + (b1 * b1) + (c1 * c1);
  return sqrt(sumSq / 100.0) + 0.01;
}

/*************************************************************/
/************************ MAIN DRIVER ************************/
/*************************************************************/

void usageAndExit() {
  fprintf(stderr, "Usage: ./Marcher image mode\n");
  fprintf(stderr, "    mode: 1 - Weight function (1) similarColour\n");
  fprintf(stderr, "          2 - Weight function (2) howWhite\n");
  fprintf(stderr, "          3 - Weight function (3) allColourWeight\n");
  exit(1);
}

int main(int argc, char *argv[]) {
  // Handle command line args
  if (argc != 3) usageAndExit();
  int mode = atoi(argv[2]);
  if (mode < 1 || mode > 3) usageAndExit();

  Image *im = readPPMimage(argv[1]);
  if (im == NULL) exit(1);

  // Make space for output path
  int *pth = calloc(sizeof(int), im->sx * im->sy);
  if (pth == NULL) {
    fprintf(stderr, "Could not allocate space for path.\n");
    exit(1);
  }

  // Call findPath with right weight function
  if (mode == 1) {
    findPath(im, similarColour, pth);
  } else if (mode == 2) {
    findPath(im, howWhite, pth);
  } else if (mode == 3) {
    findPath(im, allColourWeight, pth);
  }

  // Output the image. 
  outputPath(pth, im);

  return 0;
}
