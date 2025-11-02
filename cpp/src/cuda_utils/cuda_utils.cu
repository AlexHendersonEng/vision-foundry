#include "cuda_utils/cuda_utils.h"
#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>

/**
 * @brief Checks the result of a CUDA API call and aborts if an error occurred.
 *
 * This helper function verifies whether a CUDA operation succeeded.
 * If the given CUDA error code indicates failure, it prints an error message
 * and terminates the program.
 *
 * @param err The CUDA error code returned by a CUDA API call.
 * @param msg A descriptive message indicating the context of the CUDA operation.
 */
static inline void checkCuda(cudaError_t err, const char* msg) {
    if (err != cudaSuccess) {
        std::fprintf(stderr, "CUDA error (%s): %s\n", msg, cudaGetErrorString(err));
        std::abort();
    }
}

/**
 * @brief CUDA kernel that performs element-wise addition of two arrays.
 *
 * Each thread computes one element of the output array by summing the corresponding
 * elements from the two input arrays.
 *
 * @param a Pointer to the first input array in device memory.
 * @param b Pointer to the second input array in device memory.
 * @param out Pointer to the output array in device memory.
 * @param n Total number of elements in each array.
 */
__global__ void add_kernel(const double* a, const double* b, double* out, std::size_t n) {
    std::size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) out[i] = a[i] + b[i];
}

/**
 * @brief Performs element-wise addition of two double-precision arrays using CUDA.
 *
 * This function allocates device memory, copies input data to the GPU, launches
 * a CUDA kernel to add the arrays element-wise, and copies the result back to the host.
 * It automatically handles CUDA memory management and error checking.
 *
 * @param a Pointer to the first input array in host memory.
 * @param b Pointer to the second input array in host memory.
 * @param out Pointer to the output array in host memory where results are stored.
 * @param n Number of elements in each array.
 *
 * @note All host arrays must have at least @p n elements allocated.
 * @warning The function aborts the program if any CUDA call fails.
 */
void cuda_add(const double* a, const double* b, double* out, std::size_t n) {
    if (n == 0) return;

    const std::size_t bytes = n * sizeof(double);

    double *d_a = nullptr, *d_b = nullptr, *d_out = nullptr;
    checkCuda(cudaMalloc(&d_a, bytes), "cudaMalloc d_a");
    checkCuda(cudaMalloc(&d_b, bytes), "cudaMalloc d_b");
    checkCuda(cudaMalloc(&d_out, bytes), "cudaMalloc d_out");

    checkCuda(cudaMemcpy(d_a, a, bytes, cudaMemcpyHostToDevice), "cudaMemcpy H2D a");
    checkCuda(cudaMemcpy(d_b, b, bytes, cudaMemcpyHostToDevice), "cudaMemcpy H2D b");

    const int blockSize = 256;
    const int gridSize = static_cast<int>((n + blockSize - 1) / blockSize);

    add_kernel<<<gridSize, blockSize>>>(d_a, d_b, d_out, n);

    // Check for kernel launch errors and synchronize
    checkCuda(cudaGetLastError(), "launch add_kernel");
    checkCuda(cudaDeviceSynchronize(), "cudaDeviceSynchronize");

    checkCuda(cudaMemcpy(out, d_out, bytes, cudaMemcpyDeviceToHost), "cudaMemcpy D2H out");

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_out);
}
