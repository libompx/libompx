//=== accessor-c/Accessor.h - Accessor header definition ----*- C -*-===//
//
// Part of the libompx Project, under the MIT License.
// See libompx/LICENSE.txt for license information
//
//===-------------------------------------------------------------===//
///
/// \file
/// This file contains the C implementation of the Accessor header,
/// which is used to wrap dynamically allocated regions pointers to
/// provide transparent data movent through OpenMp declare mapper
///
//===-------------------------------------------------------------===//

#ifndef LIBOMPX_ACCESSOR_H
#define LIBOMPX_ACCESSOR_H

/// Macros required to concatenate type and access mode as needed
#define concat(x, y) x##y
#define doconcat(x, y) concat(x, y)
#define NAME(g) doconcat(doconcat(g, ACCESS_MODE), TYPE)

/// Macro for the accessor logic to generate the accessor struct  and declare
/// mapper
#define ACC_LOGIC                                                              \
  typedef struct NAME(acc_) {                                                  \
    TYPE *data;                                                                \
    size_t len;                                                                \
  } NAME(accessor_);                                                           \
  _Pragma("omp declare mapper(NAME(accessor_) a) map(K: a.data[0:a.len])")

// Expand accessor logic macro for different data types and access modes

//  for read access mode
#define ACCESS_MODE read_
#define K to

// read, int
#define TYPE int
ACC_LOGIC
#undef TYPE

// read, float
#define TYPE float
ACC_LOGIC
#undef TYPE

// read, double
#define TYPE double
ACC_LOGIC
#undef TYPE

#undef K
#undef ACCESS_MODE

// for write access mode
#define ACCESS_MODE write_
#define K from

// write, int
#define TYPE int
ACC_LOGIC
#undef TYPE

// write, float
#define TYPE float
ACC_LOGIC
#undef TYPE

// write, double
#define TYPE double
ACC_LOGIC
#undef TYPE

#undef K
#undef ACCESS_MODE

// for read-write access mode
#define ACCESS_MODE read_write_
#define K tofrom

// read-write, int
#define TYPE int
ACC_LOGIC
#undef TYPE

// read-write, float
#define TYPE float
ACC_LOGIC
#undef TYPE

// read-write, double
#define TYPE double
ACC_LOGIC
#undef TYPE

#undef K
#undef ACCESS_MODE

// for temporary access mode
#define ACCESS_MODE temporary_
#define K alloc

// temporary, int
#define TYPE int
ACC_LOGIC
#undef TYPE

// temporary, float
#define TYPE float
ACC_LOGIC
#undef TYPE

// temporary, double
#define TYPE double
ACC_LOGIC
#undef TYPE

#undef K
#undef ACCESS_MODE

#endif

/// @example vec_add.c
/// Simple Integer Vector Addition example that uses the Accessor-c header

///===--- vim: set ft=c sw=2 ts=2 sts=2 et: ----------------------===///
