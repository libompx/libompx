//=== utils.h - Helper Functions for Accessor-C Examples ----*- C -*-===//
//
// Part of the libompx Project, under the MIT License.
// See libompx/LICENSE.txt for license information
//
//===-------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the helper functions
/// used in the examples for accessor-c/Accessor.h header
///
//===-------------------------------------------------------------===//

#ifndef LIBOMPX_EXAMPLES_UTILS
#define LIBOMPX_EXAMPLES_UTILS
#include <stdlib.h>
#include <time.h>

// populate an array with random numbers between 0 and 9999
void generateIntMatrix(int *vals, int n) {

  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    vals[i] = rand() % 9999;
  }
}

// print an array as a one-line vector
void printIntVector(int *ptr, int start, int end) {

  printf("{\t");
  for (int i = start; i < end; i++) {

    printf("%d\t", ptr[i]);
  }
  printf("}\n");
}

#endif
///===--- vim: set ft=c sw=2 ts=2 sts=2 et: ----------------------===///
