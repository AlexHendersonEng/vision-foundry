# Variables
set(TARGET_NAME "utils")

# Add library
add_library("${TARGET_NAME}" STATIC "utils.cpp")

# Include directories
target_include_directories("${TARGET_NAME}" PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Set C++ standard
if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)
endif()

# Install
install(TARGETS "${TARGET_NAME}" DESTINATION libs)
