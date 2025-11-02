# Variables
set(TARGET_NAME "cuda_utils")

# Add library
add_library("${TARGET_NAME}" STATIC "cuda_utils.cu")

# Include directories
target_include_directories("${TARGET_NAME}" PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Set C++ standard
set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)

# Enable separable compilation (useful for split kernels)
set_target_properties("${TARGET_NAME}" PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

# Install
install(TARGETS "${TARGET_NAME}" DESTINATION libs)
