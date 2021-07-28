//=== vec_add.c - Vector Addition using Accessor Example ----*- C -*-===//
//
// Part of the libompx Project, under the MIT License.
// See libompx/LICENSE.txt for license information
//
//===-------------------------------------------------------------------===//
///
/// \file
/// This file is an example vector addition application
/// using libompx accessor-c Accessor header
///
//===------------------------------------------------------------------===//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
// include header file
#include "Accessor.h"
#include "utils.h"

int main() {

  // Allocate three int vectors of size 10

  int *x = (int *)malloc(sizeof(int) * 10);
  int *y = (int *)malloc(sizeof(int) * 10);
  int *z = (int *)malloc(sizeof(int) * 10);

  // populate x
  generateIntMatrix(x, 10);

  // print x
  printf("x: ");
  printIntVector(x, 0, 10);

  // populate y
  generateIntMatrix(y, 10);

  // print y
  printf("y: ");
  printIntVector(y, 0, 10);

  // declare a struct on the format accessor_<ACCESS_MODE>_<TYPE>
  accessor_read_int ac_x;
  accessor_read_int ac_y;
  accessor_write_int ac_z;

  // set accessor struct data members
  ac_x.data = x;
  ac_x.len = 10;

  ac_y.data = y;
  ac_y.len = 10;

  ac_z.data = z;
  ac_z.len = 10;

#pragma omp target teams distribute parallel for
  for (int i = 0; i < 10; i++) {
    // access the "data" member of the accessor struct
    ac_z.data[i] = ac_x.data[i] + ac_y.data[i];
  }

  // print z
  printf("z: ");
  printIntVector(z, 0, 10);

  // free dynamic data
  free(x);
  free(y);
  free(z);

  return 0;
}
///===--- vim: set ft=c sw=2 ts=2 sts=2 et: ----------------------===///
