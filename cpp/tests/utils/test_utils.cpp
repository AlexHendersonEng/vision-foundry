/**
 * @file addition_test.cpp
 * @brief Unit tests for the `add` function using Google Test (gtest).
 *
 * This file contains a series of test cases that verify the behavior
 * of the `add` function declared in `utils/utils.h`. It ensures correct
 * results when adding positive numbers, negative numbers, mixed signs,
 * and zero.
 */

#include <gtest/gtest.h>

#include "utils/utils.h"

/**
 * @test
 * @brief Verifies that `add` correctly sums two positive numbers.
 *
 * This test ensures that adding two positive floating-point numbers
 * yields the correct result.
 */
TEST(AdditionTest, HandlesPositiveNumbers) {
  /// Expect that 2.0 + 3.0 equals 5.0
  EXPECT_DOUBLE_EQ(add(2.0, 3.0), 5.0);
}

/**
 * @test
 * @brief Verifies that `add` correctly sums two negative numbers.
 *
 * This test ensures that adding two negative floating-point numbers
 * produces the correct negative result.
 */
TEST(AdditionTest, HandlesNegativeNumbers) {
  /// Expect that -2.5 + -3.5 equals -6.0
  EXPECT_DOUBLE_EQ(add(-2.5, -3.5), -6.0);
}

/**
 * @test
 * @brief Verifies that `add` correctly handles mixed sign operands.
 *
 * This test ensures that when adding a negative and a positive number,
 * the result is computed correctly.
 */
TEST(AdditionTest, HandlesMixedSigns) {
  /// Expect that -2.0 + 5.0 equals 3.0
  EXPECT_DOUBLE_EQ(add(-2.0, 5.0), 3.0);
}

/**
 * @test
 * @brief Verifies that `add` correctly handles zero values.
 *
 * This test checks that adding zero to another number (or to itself)
 * yields the correct result without altering the operand.
 */
TEST(AdditionTest, HandlesZero) {
  /// Expect that 0.0 + 0.0 equals 0.0
  EXPECT_DOUBLE_EQ(add(0.0, 0.0), 0.0);

  /// Expect that 0.0 + 4.2 equals 4.2
  EXPECT_DOUBLE_EQ(add(0.0, 4.2), 4.2);
}
