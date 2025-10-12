# Variables
set(TARGET_NAME "say_hello")

# Add executable
add_executable("${TARGET_NAME}" "say_hello.cpp")

# Link to library
target_link_libraries("${TARGET_NAME}" "hello")

# Set C++ standard
if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)
endif()