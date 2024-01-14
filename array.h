#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include "utils.h"

void genRndFloatArray(float*, int);
void arrayMerge(float*, int, int, int);
void arrayMergeSort(float*, int, int);
int arrayBinarySearch(float*, int, int, float);

#endif  // ARRAY_H