# Variables
set(TARGET_NAME "data")

# Find packages
find_package(pybind11 CONFIG REQUIRED)

# Add module
pybind11_add_module("${TARGET_NAME}" data.cpp)

# Add include directories
target_include_directories("${TARGET_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Set C++ standard
set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)

# Install
install(TARGETS "${TARGET_NAME}" DESTINATION vision_foundry_core)
