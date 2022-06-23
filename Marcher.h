/*
 * You shouldn't change any of the code here. You will
 * NOT be submitting this file as part of your assignment.
 * You don't need to declare any helper functions here since
 * they are not going to be exposed to any of the other files.
 *
 * CSCB63 Winter 2020 - Assignment 2
 * (c) Mustafa Quraish
 */

#ifndef __MARCHER_H
#define __MARCHER_H

#include "ImgUtils.h"

// You don't need to understand this syntax, but it essentially 
// defines `WeightFunc` to be a function which expects an Image
// pointer and two pixel coordinates, and returns a double.
typedef double (*WeightFunc)(Image *im, int a, int b);

double findPath(Image *im, WeightFunc weight, int path[]);
double allColourWeight(Image *im, int a, int b);

#endif
