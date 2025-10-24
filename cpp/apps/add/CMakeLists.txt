# Variables
set(TARGET_NAME "add")

# Add executable
add_executable("${TARGET_NAME}" "add.cpp")

# Link to library
target_link_libraries("${TARGET_NAME}" PRIVATE utils)

# Set C++ standard
if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET "${TARGET_NAME}" PROPERTY CXX_STANDARD 20)
endif()

# Install
install(TARGETS "${TARGET_NAME}" DESTINATION bin)
