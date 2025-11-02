#pragma once
#include <cstddef>

extern "C" {

/**
 * @brief Performs element-wise addition of two double-precision arrays on the
 * GPU.
 *
 * This function adds two input arrays of double-precision floating-point
 * numbers element by element using CUDA, and stores the result in the output
 * array.
 *
 * @param a Pointer to the first input array (device memory).
 * @param b Pointer to the second input array (device memory).
 * @param out Pointer to the output array where the results will be stored
 * (device memory).
 * @param n Number of elements in each array.
 *
 * @note All array pointers must point to valid CUDA device memory regions.
 */
void cuda_add(const double* a, const double* b, double* out, std::size_t n);

}  // extern "C"
