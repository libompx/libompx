//=== vec_add.cpp - Vector Addition using Accessor Example ----*- C++ -*-===//
//
// Part of the libompx Project, under the MIT License.
// See libompx/LICENSE.txt for license information
//
//===-------------------------------------------------------------------===//
///
/// \file
/// This file is an example vector addition application
/// using libompx::Accessor header
///
//===------------------------------------------------------------------===//

#include <iostream>
#include <omp.h>

/// Utlities for populating and printing vectors
#include "utils.h"

/// Accessor header
#include "Accessor.h"

constexpr int NROWS = 1;
constexpr int NCOLS = 10;

using namespace libompx;

int main(){
   
    /// Allocate the three vectors
    /// c = a + b 
    int* a = new int[NROWS * NCOLS];
    int* b = new int[NROWS * NCOLS];
    int* c = new int[NROWS * NCOLS];

    // Populate a
    generateIntMatrix(a, NROWS, NCOLS, 0.7);

    // Print a
    std::cout << "A: " ;
    printVector(a, 0, NROWS*NCOLS);

    // Populate b
    generateIntMatrix(b, NROWS, NCOLS, 0.5);

    // Print b 
    std::cout << "B: " ;
    printVector(b, 0, NROWS*NCOLS);

    /// Create three accessors around a,b, and c
    /// Both a and b should use READ access mode
    /// Since the addition result is stored in c,
    /// use WRITE mode for its accessor 
    Accessor<READ, int> acc_a(a, NROWS*NCOLS); 
    Accessor<READ, int> acc_b(b, NROWS*NCOLS);
    Accessor<WRITE, int> acc_c(c, NROWS*NCOLS);

    // Offload the addition to target device
#pragma omp target teams distribute parallel for 
    for (int i = 0; i < NROWS*NCOLS; i++){
        // operate on previously defined accessors
        acc_c[i] = acc_a[i] + acc_b[i];
    } 

    // Print c to ensure results are correct after computing
    std::cout << "After device:" << std::endl;
    std::cout << "C: ";
    printVector(c, 0, NROWS*NCOLS);
    
    // free dynamically allocated memory regions
    delete [] a;
    delete [] b;
    delete [] c;

    return 0;
}

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------===///
