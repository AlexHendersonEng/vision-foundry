# Variables
set(TARGET_NAME "test_utils")

# Add executable
add_executable("${TARGET_NAME}" "test_utils.cpp")

# Link libraries
target_link_libraries("${TARGET_NAME}" PRIVATE GTest::gtest_main utils)

# Add include directories
target_include_directories("${TARGET_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Set C++ standard
set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)

# Add executable as test
include(GoogleTest)
gtest_discover_tests("${TARGET_NAME}")
