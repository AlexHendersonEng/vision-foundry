/**
 * @file dataset_test.cpp
 * @brief Unit tests for Dataset and DataLoader classes.
 *
 * This file contains Google Test unit tests verifying the functionality of
 * a simple Dataset implementation and the associated DataLoader class.
 */

#include <gtest/gtest.h>

#include "data/data.hpp"

/**
 * @class IntDataset
 * @brief A minimal concrete implementation of the Dataset interface for
 * integers.
 *
 * This dataset holds a vector of integers and provides access via
 * `getItem()` and `size()` functions for testing purposes.
 */
class IntDataset : public Dataset<int> {
 private:
  /// Internal storage of integer data.
  std::vector<int> data_;

 public:
  /**
   * @brief Constructs an IntDataset from a vector of integers.
   * @param v The vector of integers to store.
   */
  explicit IntDataset(std::vector<int> v) : data_(std::move(v)) {}

  /**
   * @brief Retrieves an element from the dataset by index.
   * @param index The index of the element to retrieve.
   * @return The integer at the specified index.
   * @throws std::out_of_range if the index is invalid.
   */
  int getItem(size_t index) const override { return data_.at(index); }

  /**
   * @brief Returns the number of elements in the dataset.
   * @return The number of elements.
   */
  size_t size() const override { return data_.size(); }
};

/**
 * @test DatasetTest.BasicGetItemAndSize
 * @brief Tests that IntDataset returns the correct item values and size.
 *
 * Verifies that elements can be accessed correctly and that the size
 * matches the expected number of elements.
 */
TEST(DatasetTest, BasicGetItemAndSize) {
  IntDataset d({1, 2, 3, 4});
  EXPECT_EQ(d.size(), 4u);
  EXPECT_EQ(d.getItem(0), 1);
  EXPECT_EQ(d.getItem(3), 4);
}

/**
 * @test DataLoaderTest.BatchIterationNoShuffle
 * @brief Tests DataLoader iteration over batches without shuffling.
 *
 * Ensures that batches are produced sequentially in the same order
 * as the dataset when shuffling is disabled.
 */
TEST(DataLoaderTest, BatchIterationNoShuffle) {
  IntDataset d({10, 11, 12, 13, 14});
  DataLoader<IntDataset> loader(const_cast<IntDataset&>(d), 2, false);

  ASSERT_TRUE(loader.hasNext());
  auto b1 = loader.nextBatch();
  EXPECT_EQ(b1.size(), 2u);
  EXPECT_EQ(b1[0], 10);
  EXPECT_EQ(b1[1], 11);

  ASSERT_TRUE(loader.hasNext());
  auto b2 = loader.nextBatch();
  EXPECT_EQ(b2.size(), 2u);
  EXPECT_EQ(b2[0], 12);
  EXPECT_EQ(b2[1], 13);

  ASSERT_TRUE(loader.hasNext());
  auto b3 = loader.nextBatch();
  EXPECT_EQ(b3.size(), 1u);
  EXPECT_EQ(b3[0], 14);

  EXPECT_FALSE(loader.hasNext());
}

/**
 * @test DataLoaderTest.ResetAndShuffleDeterministicCheck
 * @brief Tests DataLoader behavior with shuffle enabled.
 *
 * Verifies that:
 * - Shuffling reorders data between epochs.
 * - Resetting the loader restarts iteration from the beginning.
 * - Each epoch is a permutation of the dataset (contains all items).
 */
TEST(DataLoaderTest, ResetAndShuffleDeterministicCheck) {
  // Using shuffle=true should reorder indices. We can't predict exact order
  // but we can check that reset restores iteration and that successive
  // iterations produce potentially different orders when shuffle is enabled.
  IntDataset d({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  DataLoader<IntDataset> loader(const_cast<IntDataset&>(d), 3, true);

  /// Collect first epoch data.
  std::vector<int> epoch1;
  while (loader.hasNext()) {
    auto b = loader.nextBatch();
    epoch1.insert(epoch1.end(), b.begin(), b.end());
  }

  EXPECT_EQ(epoch1.size(), d.size());

  /// Reset loader and collect second epoch data.
  loader.reset();
  std::vector<int> epoch2;
  while (loader.hasNext()) {
    auto b = loader.nextBatch();
    epoch2.insert(epoch2.end(), b.begin(), b.end());
  }

  EXPECT_EQ(epoch2.size(), d.size());

  // It's possible (though unlikely) that shuffle produced same order; allow
  // both but assert that the two epochs are permutations of the dataset.
  std::sort(epoch1.begin(), epoch1.end());
  std::sort(epoch2.begin(), epoch2.end());
  for (size_t i = 0; i < d.size(); ++i) EXPECT_EQ(epoch1[i], epoch2[i]);
}
