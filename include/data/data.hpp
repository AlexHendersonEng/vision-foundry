#pragma once
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

/**
 * @brief Abstract base class representing a dataset interface.
 *
 * This class defines the basic interface for datasets, allowing access
 * to individual items and querying the dataset size. It is designed
 * to be subclassed with concrete dataset implementations.
 *
 * @tparam SampleType The type of elements stored in the dataset.
 */
template <typename SampleType>
class Dataset {
 public:
  using type_t = SampleType; /**< Alias for the dataset element type */

 public:
  /**
   * @brief Virtual destructor.
   *
   * Ensures derived classes can clean up properly when deleted
   * through a pointer to this base class.
   */
  virtual ~Dataset() = default;

  /**
   * @brief Retrieve an item from the dataset by index.
   *
   * This is a pure virtual function that must be implemented by derived
   * classes.
   *
   * @param index The zero-based index of the item to retrieve.
   * @return The dataset item at the specified index.
   */
  virtual SampleType getItem(size_t index) const = 0;

  /**
   * @brief Get the total number of items in the dataset.
   *
   * This is a pure virtual function that must be implemented by derived
   * classes.
   *
   * @return The number of items in the dataset.
   */
  virtual size_t size() const = 0;
};

/**
 * @brief Class for iterating over a dataset in batches.
 *
 * Provides functionality to iterate through a Dataset in batches, with
 * optional shuffling of data. The batch size and shuffle behavior are
 * configurable.
 *
 * @tparam DatasetType The type of the dataset being loaded.
 */
template <typename DatasetType>
class DataLoader {
 private:
  const DatasetType& dataset_;  /**< Reference to the dataset */
  size_t batch_size_;           /**< Number of samples per batch */
  bool shuffle_;                /**< Whether to shuffle data between epochs */
  std::vector<size_t> indices_; /**< Indices used for batching */
  size_t current_index_;        /**< Current index in the dataset */

 public:
  /**
   * @brief Construct a new DataLoader object.
   *
   * Initializes the DataLoader with a dataset, batch size, and shuffle option.
   * If shuffle is true, the data order will be randomized.
   *
   * @param dataset Reference to the dataset.
   * @param batch_size Number of samples per batch.
   * @param shuffle Whether to shuffle the dataset before iteration.
   */
  DataLoader(DatasetType& dataset, size_t batch_size, bool shuffle = true)
      : dataset_(dataset),
        batch_size_(batch_size),
        shuffle_(shuffle),
        current_index_(0) {
    // Initialize indices
    indices_.resize(dataset_.size());
    std::iota(indices_.begin(), indices_.end(), 0);
    if (shuffle_)
      std::shuffle(indices_.begin(), indices_.end(),
                   std::mt19937(std::random_device()()));
  }

  /**
   * @brief Check if there are more batches to retrieve.
   *
   * @return true if there are remaining batches, false otherwise.
   */
  bool hasNext() const { return current_index_ < indices_.size(); }

  /**
   * @brief Retrieve the next batch of samples from the dataset.
   *
   * Advances the internal pointer by the batch size and returns a vector
   * containing the next batch of samples.
   *
   * @return std::vector<typename DatasetType::type_t> Vector of dataset
   * samples.
   */
  std::vector<typename DatasetType::type_t> nextBatch() {
    std::vector<typename DatasetType::type_t> batch;
    size_t end_index = std::min(current_index_ + batch_size_, indices_.size());
    for (size_t i = current_index_; i < end_index; ++i) {
      batch.push_back(dataset_.getItem(indices_[i]));
    }
    current_index_ = end_index;
    return batch;
  }

  /**
   * @brief Reset the DataLoader to start from the beginning.
   *
   * Resets the internal index and optionally reshuffles the dataset if
   * shuffle is enabled.
   */
  void reset() {
    current_index_ = 0;
    if (shuffle_) {
      std::shuffle(indices_.begin(), indices_.end(),
                   std::mt19937{std::random_device{}()});
    }
  }
};
