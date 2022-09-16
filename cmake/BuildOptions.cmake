########################################################################################################################

# function that sets the default CMake variables with general compilation features
#
function (set_general_compile_features)
    set(CMAKE_CXX_STANDARD "20" CACHE INTERNAL "")
    set(CMAKE_CXX_STANDARD_REQUIRED "ON" CACHE INTERNAL "")
    set(CMAKE_CXX_EXTENSIONS "OFF" CACHE INTERNAL "")

    # TODO: fix these, make RPATH setting work on both Linux/MacOS for shared lib artefacts; low prio for now
    #
    # set(CMAKE_SKIP_RPATH "FALSE" CACHE INTERNAL "")
    # set(CMAKE_BUILD_WITH_INSTALL_RPATH "TRUE" CACHE INTERNAL "")
    # set(CMAKE_INSTALL_RPATH "@loader_path/../lib" CACHE INTERNAL "")
endfunction()

########################################################################################################################

# function that sets the default CMake variables with build output directories
#
function (set_build_output_directories)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_LIB_DIRECTORY}" CACHE INTERNAL "")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_LIB_DIRECTORY}" CACHE INTERNAL "")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_BIN_DIRECTORY}" CACHE INTERNAL "")
endfunction()

########################################################################################################################

# function that returns the list of general compile features to be used when configuring a target
#
function (get_compile_features RESULT)
    set(${RESULT} "cxx_std_20" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of defines to be injected at compile time
#
function (get_compile_definitions RESULT)
    set(${RESULT} "" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of specific compilation options to be used when configuring a target
#
function (get_compile_options RESULT)
    set(${RESULT} "-Werror"
                  $<$<CONFIG:Debug>:-g>
                  $<$<CONFIG:Debug>:-ggdb>
                  $<$<CONFIG:Debug>:-O0>
                  $<$<CONFIG:Release>:-O2>
        PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of compilation warnings to be used when configuring a target
#
function (get_compile_warnings RESULT)
    set(LOCAL_RESULT "-Wall"
                  "-Wextra"
                  "-Wpedantic"
                  "-Wfloat-equal"
                  "-Wctor-dtor-privacy"
                  "-Winit-self"
                  "-Wmissing-declarations"
                  "-Wnon-virtual-dtor"
                  "-Wold-style-cast"
                  "-Wno-sign-compare"
                  "-Woverloaded-virtual"
                  "-Wredundant-decls"
                  "-Wshadow"
                  "-Wsign-promo"
                  "-Wswitch-default"
                  "-Wundef")

    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        list(APPEND LOCAL_RESULT "-Wnoexcept")
    endif()

    set("${RESULT}" "${LOCAL_RESULT}" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of additional include directories to be provided when configuring a target
#
function (get_include_directories RESULT)
    set(${RESULT} "${SOURCE_DIRECTORY}" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of additional include directories to be provided when configuring a test target
#
function (get_test_include_directories RESULT)
    set(${RESULT} "${ROOT_DIRECTORY}" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of linking options to be used when configuring a target
#
function (get_link_options RESULT)
    set(${RESULT} $<$<CONFIG:Release>:-flto>
        PARENT_SCOPE)
endfunction()

########################################################################################################################
