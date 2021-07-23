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


#ifndef LIBOMPX_ACCESSOR_H
#define LIBOMPX_ACCESSOR_H

namespace libompx {
    
    /// enum to hold different access modes
    enum access_mode{
        READ,       /// Read-only(data moved from host to device before
                    /// the start of target region)

        WRITE,      /// Write(data moved from device to host at the end
                    /// of target region)

        READ_WRITE, /// Read and Write(data moved from host to device
                    /// initially and then back from device to host 
                    /// at the end of the target region) 

        TEMPORARY   /// Allocate data at device only (no movement)
    };

    /// Base Accessor Class Declaration, not intended for direct use by
    /// user
    template <access_mode AccessMode, typename Ty>
    class AccessorBase {
    protected:
        /// Constructor to be used only by child classes
        AccessorBase(Ty* data, size_t len):_data(data), _len(len) {};
    public:

        // _data and _len need to be public to be used in declare mapper
        // pointer to the data
        
        /// Pointer to the original data allocated by user 
        Ty* _data;   

        /// Length of user-allocated data region
        size_t _len;
        
        /// Returns the length of the user-specified data region
        size_t size() const{ return _len; };
        
        /// Return a pointer the start of data region
        const Ty* begin() const { return _data; };

        /// Returns a pointer to the end of data region
        const Ty* end() const { return _data+_len; };
    };

    /// Child Accessor 1: All access modes except for READ
    template <access_mode AccessMode, typename Ty>
    class Accessor: public AccessorBase<AccessMode, Ty>{
    public:

        /// Accessor constructor
        Accessor(Ty* data, size_t len): AccessorBase<AccessMode, Ty>(data, len){ };

        /// Returns a pointer to the user-specified data region
        Ty* data() const{ return this->_data; };

        /// [] operator overloading returns a reference to a data element
        /// to allow data maniuplation in WRITE/READ_WRITE modes
        Ty& operator[](const int idx) const { return this->_data[idx]; };
    };

    /// Child Accessor 2: access_mode specialized for READ
    template <typename Ty>
    class Accessor<READ, Ty>: public AccessorBase<READ, Ty>{
    public:
        /// Accessor constructor 
        Accessor(Ty* data, size_t len): AccessorBase<READ, Ty>(data, len) {};
        
        /// Returns a const pointer to the user-specified data region
        /// to prevent modification of data elements (since access_mode is READ)
        const Ty* data() const { return this->_data; };

        /// [] operator overloading  returns a const reference to prevent 
        /// modification of data elements (since access_mode is READ)
        const Ty& operator[](const int idx) const { return this->_data[idx]; };
    };
}

/// different mappers based on access mode
#pragma omp declare mapper(libompx::Accessor<libompx::READ, double> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, double> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, double> a) map(tofrom: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::TEMPORARY, double> a) map(alloc: a._data[0:a._len])

#pragma omp declare mapper(libompx::Accessor<libompx::READ, float> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, float> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, float> a) map(tofrom: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::TEMPORARY, float> a) map(alloc: a._data[0:a._len])

#pragma omp declare mapper(libompx::Accessor<libompx::READ, int> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, int> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, int> a) map(tofrom: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::TEMPORARY, int> a) map(alloc: a._data[0:a._len])


#endif

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------===///
