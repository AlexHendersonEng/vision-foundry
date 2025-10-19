# Variables
set(TARGET_NAME "vision_foundry")

# Find packages
find_package(pybind11 CONFIG REQUIRED)

# Add module
pybind11_add_module("${TARGET_NAME}" bindings.cpp)

# Add include directories
target_include_directories("${TARGET_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Set C++ standard
set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)

# Install
install(TARGETS "${TARGET_NAME}" DESTINATION bindings)
