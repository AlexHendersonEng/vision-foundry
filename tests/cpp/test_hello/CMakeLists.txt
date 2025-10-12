# Variables
set(TARGET_NAME "test_hello")

# Get packages
find_package(GTest REQUIRED)

# Add executable
add_executable("${TARGET_NAME}" "test_hello.cpp")

# Link to library
target_link_libraries("${TARGET_NAME}" PRIVATE hello GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# Set C++ standard
if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)
endif()

# Add executable as test
add_test(NAME "${TARGET_NAME}" COMMAND "${TARGET_NAME}")
