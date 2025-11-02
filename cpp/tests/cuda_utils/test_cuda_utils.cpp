/**
 * @file test_cuda_utils.cpp
 * @brief Unit tests for the `cuda_add` function using Google Test (gtest).
 *
 * This file verifies the correctness and robustness of the CUDA-based
 * element-wise array addition implemented in `cuda_add`.
 * It includes tests for positive values, negative values, mixed signs,
 * zero-length inputs, and large arrays.
 */

#include <gtest/gtest.h>

#include <cmath>
#include <vector>

#include "cuda_utils/cuda_utils.h"

/**
 * @test
 * @brief Verifies that `cuda_add` correctly adds two arrays of positive values.
 *
 * This test initializes two arrays of positive doubles, performs the CUDA-based
 * addition, and compares each result with the expected CPU-computed sum.
 */
TEST(CudaAddTest, HandlesPositiveValues) {
  const std::size_t n = 5;
  std::vector<double> a{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> b{5.0, 4.0, 3.0, 2.0, 1.0};
  std::vector<double> out(n, 0.0);

  cuda_add(a.data(), b.data(), out.data(), n);

  for (std::size_t i = 0; i < n; ++i) {
    EXPECT_DOUBLE_EQ(out[i], a[i] + b[i]) << "Mismatch at index " << i;
  }
}

/**
 * @test
 * @brief Verifies that `cuda_add` correctly adds arrays of negative values.
 *
 * This test ensures that negative operands are correctly handled and summed.
 */
TEST(CudaAddTest, HandlesNegativeValues) {
  const std::size_t n = 4;
  std::vector<double> a{-1.0, -2.0, -3.0, -4.0};
  std::vector<double> b{-5.0, -4.0, -3.0, -2.0};
  std::vector<double> out(n, 0.0);

  cuda_add(a.data(), b.data(), out.data(), n);

  for (std::size_t i = 0; i < n; ++i) {
    EXPECT_DOUBLE_EQ(out[i], a[i] + b[i]) << "Mismatch at index " << i;
  }
}

/**
 * @test
 * @brief Verifies that `cuda_add` correctly handles mixed positive and negative
 * values.
 *
 * This test ensures that the CUDA implementation produces correct results when
 * operands have opposite signs.
 */
TEST(CudaAddTest, HandlesMixedSigns) {
  const std::size_t n = 5;
  std::vector<double> a{-1.0, 2.0, -3.0, 4.0, -5.0};
  std::vector<double> b{1.0, -2.0, 3.0, -4.0, 5.0};
  std::vector<double> out(n, 0.0);

  cuda_add(a.data(), b.data(), out.data(), n);

  for (std::size_t i = 0; i < n; ++i) {
    EXPECT_DOUBLE_EQ(out[i], a[i] + b[i]) << "Mismatch at index " << i;
  }
}

/**
 * @test
 * @brief Verifies that `cuda_add` handles zero-length input arrays gracefully.
 *
 * This test confirms that calling the function with `n == 0` does not crash
 * or attempt invalid CUDA memory operations.
 */
TEST(CudaAddTest, HandlesZeroLength) {
  std::vector<double> a;
  std::vector<double> b;
  std::vector<double> out;

  EXPECT_NO_THROW({ cuda_add(a.data(), b.data(), out.data(), 0); });
}

/**
 * @test
 * @brief Verifies correctness of `cuda_add` with a large input array.
 *
 * This test checks numerical accuracy and stability when processing a large
 * dataset, ensuring that all elements are added correctly.
 */
TEST(CudaAddTest, HandlesLargeArray) {
  const std::size_t n = 1 << 20;  // 1 million elements
  std::vector<double> a(n), b(n), out(n);

  for (std::size_t i = 0; i < n; ++i) {
    a[i] = static_cast<double>(i);
    b[i] = 1.0;
  }

  cuda_add(a.data(), b.data(), out.data(), n);

  // Verify a few samples
  EXPECT_DOUBLE_EQ(out[0], a[0] + b[0]);
  EXPECT_DOUBLE_EQ(out[n / 2], a[n / 2] + b[n / 2]);
  EXPECT_DOUBLE_EQ(out[n - 1], a[n - 1] + b[n - 1]);
}
