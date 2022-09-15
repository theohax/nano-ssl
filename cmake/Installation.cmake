########################################################################################################################

# private function that copies public header files and directories
# from the source tree to the build directory within the "generated" files
#
function (_installation_copy_headers_to_generated PUBLIC_HEADER_FILES_AND_DIRECTORIES)
    foreach (HEADER_FILE_OR_DIRECTORY IN LISTS PUBLIC_HEADER_FILES_AND_DIRECTORIES)
        utils_is_directory("${HEADER_FILE_OR_DIRECTORY}" IS_DIRECTORY_RESULT)
        if (IS_DIRECTORY_RESULT STREQUAL "1")
            message(STATUS "DIR ${FILES_UNDER_DIRECTORY}, moving all underneath")
            file(COPY "${HEADER_FILE_OR_DIRECTORY}/"
                 DESTINATION "${BUILD_GENERATED_PUBLIC_DIRECTORY}"
                 FILES_MATCHING PATTERN "*.hpp")
        else()
            message(STATUS "FILE ${HEADER_FILE_OR_DIRECTORY}, moving just it")
            file(COPY "${HEADER_FILE_OR_DIRECTORY}" DESTINATION "${BUILD_GENERATED_PUBLIC_DIRECTORY}")
        endif()
    endforeach()
endfunction()

########################################################################################################################

# private function that tweaks the include paths of the "generated" public header files
#
function (_installation_tweak_generated_headers_include_paths)
    file(GLOB_RECURSE GENERATED_PUBLIC_HEADER_FILES CONFIGURE_DEPENDS "${BUILD_GENERATED_PUBLIC_DIRECTORY}/*.hpp")
    foreach (HEADER_FILE IN LISTS GENERATED_PUBLIC_HEADER_FILES)
        file(READ "${HEADER_FILE}" HEADER_CONTENT)
        string(REPLACE "#include \"public" "#include \"nanossl" TWEAKED_INCLUDES_HEADER_CONTENT "${HEADER_CONTENT}")
        file(WRITE "${HEADER_FILE}" "${TWEAKED_INCLUDES_HEADER_CONTENT}")
    endforeach()
endfunction()

########################################################################################################################

# function that given a target name (and optionally a list of its public API headers, or directories there of),
# it instructs the generated build system to install its artefacts (in locations relative to "${CMAKE_INSTALL_PREFIX}")
#
function (installation_do_target TARGET_NAME PUBLIC_HEADER_FILES_AND_DIRECTORIES)
    _private_check_target_exists("${TARGET_NAME}")

    _installation_copy_headers_to_generated("${PUBLIC_HEADER_FILES_AND_DIRECTORIES}")
    _installation_tweak_generated_headers_include_paths()

    install(DIRECTORY "${BUILD_GENERATED_PUBLIC_DIRECTORY}/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${TARGET_NAME}")
    install(TARGETS "${TARGET_NAME}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endfunction()

########################################################################################################################
