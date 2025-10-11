# Add all subdirectories of a given base directory to the build
function(add_all_subdirectories base_dir)
    # Get absolute path of the base directory
    get_filename_component(abs_base_dir "${base_dir}" ABSOLUTE)

    # Get list of all subdirectories
    file(GLOB sub_directories true "${abs_base_dir}" "${abs_base_dir}/*")

    # Loop over subdirectories and add them to the build
    foreach(sub_directory ${sub_directories})
        if(IS_DIRECTORY "${sub_directory}" AND EXISTS "${sub_directory}/CMakeLists.txt")
            message(STATUS "Adding subdirectory: ${sub_directory}")
            add_subdirectory("${sub_directory}")
        endif()
    endforeach()
endfunction()