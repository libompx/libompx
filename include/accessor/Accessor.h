//=== Accessor.h - Accessor class definition ----*- C++ -*-===//
//
// Part of the libompx Project, under the MIT License.
// See libompx/LICENSE.txt for license information
//
//===-------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Accessor class, which is
/// used to wrap dynamically allocated regions pointers to provide
/// transparent data movement through OpenMP declare mapper
///
//===-------------------------------------------------------------===//


/// \file 
/// # libompx::Accessor
/// User-friendly Data Movement for OpenMP target offloading
///
/// ## About
/// `Accessor` is a header that augments OpenMP target offloading directives, that eliminates the need for the user to write `map` clauses
/// Instead, users can directly create an `Accessor` object around their data pointer, and specify the desired access mode as follows:
///
///     double * data = new data[N];
///     // initialize data here as needed
///     Accessor<READ, double> data_Acc(data, N);
///
/// In the previous example, an `Accessor` object around `data` is instaniated, with the `READ` access mode.
/// Now, the user can use OpenMP target directive without needing to write a map clause for `data` or `data_Acc` as follows:
///     
///     #pragma omp target teams distribute parallel for
///     // device region code that reads from data_Acc 
///
/// ## How it works?
/// `Accessor` header provides an abstraction layer around raw pointers to dynamically allocated memory, which also takes data region size as a constructor parameter
/// It allows the user to specify a template parameter defining one of the following access modes: `READ`, `WRITE`, `READ_WRITE`, or `ALLOC`. 
/// Then, the header provides a set of pre-defined mappers (using `#pragma omp declare mapper`) for different access modes and data types.
///
/// ## How to use?
/// In order to use `Accessor`, you need an OpenMP offloading-capable compiler (i.e. `clang`). In your application, include both `<omp.h>` and the header file `"Accessor.h"`
/// The `Accessor` class takes two template parameters `libompx::Accessor<access_mode A, typename T>` and two constructor arguments `(T* data, size_t len)`. Full examples are
/// available in libompx/examples

#ifndef LIBOMPX_ACCESSOR_H
#define LIBOMPX_ACCESSOR_H

namespace libompx {

/// enum to hold different access modes
enum access_mode {
  READ, /// Read-only(data moved from host to device before
        /// the start of target region)

  WRITE, /// Write(data moved from device to host at the end
         /// of target region)

  READ_WRITE, /// Read and Write(data moved from host to device
              /// initially and then back from device to host
              /// at the end of the target region)

  TEMPORARY /// Allocate data at device only (no movement)
};

/// Base Accessor Class Declaration, not intended for direct use by user
template <access_mode AccessMode, typename Ty>
class AccessorBase {
protected:
  /// Constructor to be used only by child classes
  AccessorBase(Ty *data, size_t len) : _data(data), _len(len){};

public:
  // _data and _len need to be public to be used in declare mapper
  // pointer to the data

  /// Pointer to the original data allocated by user
  Ty *_data;

  /// Length of user-allocated data region
  size_t _len;

  /// Returns the length of the user-specified data region
  size_t size() const { return _len; };

  /// Returns a pointer the start of data region
  const Ty *begin() const { return _data; };

  /// Returns a pointer to the end of data region
  const Ty *end() const { return _data + _len; };
};

/// Accessor Class for all  access modes except for READ
template <access_mode AccessMode, typename Ty>
class Accessor : public AccessorBase<AccessMode, Ty> {
public:
  /// Accessor constructor
  Accessor(Ty *data, size_t len) : AccessorBase<AccessMode, Ty>(data, len){};

  /// Returns a pointer to the user-specified data region
  Ty *data() const { return this->_data; };

  /// [] operator overloading returns a reference to a data element
  /// to allow data maniuplation in WRITE/READ_WRITE modes
  Ty &operator[](const int idx) const { return this->_data[idx]; };
};

/// Accessor class with access_mode specialized for READ
template <typename Ty>
class Accessor<READ, Ty> : public AccessorBase<READ, Ty> {
public:
  /// Accessor constructor
  Accessor(Ty *data, size_t len) : AccessorBase<READ, Ty>(data, len){};

  /// Returns a const pointer to the user-specified data region
  /// to prevent modification of data elements (since access_mode is READ)
  const Ty *data() const { return this->_data; };

  /// [] operator overloading  returns a const reference to prevent
  /// modification of data elements (since access_mode is READ)
  const Ty &operator[](const int idx) const { return this->_data[idx]; };
};
} // namespace libompx

// different mappers based on access mode
#pragma omp declare mapper(libompx::Accessor <libompx::READ, double> a)        \
    map(to                                                                     \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::WRITE, double> a)       \
    map(from                                                                   \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::READ_WRITE, double> a)  \
    map(tofrom                                                                 \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::TEMPORARY, double> a)   \
    map(alloc                                                                  \
        : a._data [0:a._len])

#pragma omp declare mapper(libompx::Accessor <libompx::READ, float> a)         \
    map(to                                                                     \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::WRITE, float> a)        \
    map(from                                                                   \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::READ_WRITE, float> a)   \
    map(tofrom                                                                 \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::TEMPORARY, float> a)    \
    map(alloc                                                                  \
        : a._data [0:a._len])

#pragma omp declare mapper(libompx::Accessor <libompx::READ, int> a)           \
    map(to                                                                     \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::WRITE, int> a)          \
    map(from                                                                   \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::READ_WRITE, int> a)     \
    map(tofrom                                                                 \
        : a._data [0:a._len])
#pragma omp declare mapper(libompx::Accessor <libompx::TEMPORARY, int> a)      \
    map(alloc                                                                  \
        : a._data [0:a._len])

#endif
/// @example vec_add.cpp
/// Simple Integer Vector Addition example that uses the Accessor header 

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------===///
