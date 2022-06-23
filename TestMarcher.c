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

#include<assert.h>
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

// Check if two doubles are equal to reasonable precision
void assertAlmostEq(double a, double b) {
  if (fabs(a - b) >= 10e-4) {
    printf("  Solution did not match expected answer.\n");
    exit(0);
  }
}

// This macro runs the test for us, given the details
#define run_test(fname,wf,expec)            \
  im = readPPMimage(fname);                 \
  printf("Running test %d...\n", testNum++);\
  cost = findPath(im,wf,path);              \
  printf("%f\n", cost);                     \
  printf("%f\n", expec);                    \
  assertAlmostEq(cost, expec);              \
  outputPath(path, im);                     \
  freeImage(im);

int main(int argc, char *argv[]) {
  int testNum = 1;
  Image *im = NULL;
  double cost;
  int path[1024*1024]; // Big enough for all tests here
  
  run_test("images/water.ppm", similarColour, 1280.81526);
  run_test("images/spiral.ppm", similarColour, 991.25540719);
  run_test("images/maze.ppm", howWhite, 12.4);
  run_test("images/bigmaze.ppm", howWhite, 8.62);
  run_test("images/grad.ppm", similarColour, 278.7514937);
  run_test("images/small.ppm", similarColour, 552.305342);
    
    for (int i=0; i<40; i++){
        printf("p[%d] = %d\n",i, path[i]);
    }


  printf("\nYou have passed all the test cases, your solution\n");
  printf("is on the right track. It is left up to you, however,\n");
  printf("to verify that your path is built correctly, and that\n");
  printf("allColourWeight() works as intended...\n");

  return 0;
}
