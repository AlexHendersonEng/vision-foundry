# Variables
set(TARGET_NAME "test_data")

# Add executable
add_executable("${TARGET_NAME}" "test_data.cpp")

# Link libraries
target_link_libraries("${TARGET_NAME}" PRIVATE GTest::gtest_main)

# Add include directories
target_include_directories("${TARGET_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Set C++ standard
set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)

# Add executable as test
add_test(NAME "${TARGET_NAME}" COMMAND "${TARGET_NAME}")
