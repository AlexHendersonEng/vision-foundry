#include "data/data.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// Trampoline class to allow Python to override virtual methods
template <typename SampleType>
class PyDataset : public Dataset<SampleType> {
 public:
  using Dataset<SampleType>::Dataset;  // Inherit constructors

  SampleType getItem(size_t index) const override {
    PYBIND11_OVERRIDE_PURE(SampleType,           // Return type
                           Dataset<SampleType>,  // Parent class
                           getItem,              // Name of function in C++
                           index                 // Argument(s)
    );
  }

  size_t size() const override {
    PYBIND11_OVERRIDE_PURE(size_t,               // Return type
                           Dataset<SampleType>,  // Parent class
                           size,                 // Name of function in C++
    );
  }
};

PYBIND11_MODULE(data, m) {
  pybind11::class_<Dataset<float>, PyDataset<float>>(m, "DatasetFloat")
      .def(pybind11::init<>())
      .def("getItem", &Dataset<float>::getItem)
      .def("size", &Dataset<float>::size);
}
